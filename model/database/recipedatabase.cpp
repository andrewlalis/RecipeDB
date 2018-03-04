#include "recipedatabase.h"

RecipeDatabase::RecipeDatabase(string filename) : Database(filename){
	this->ensureTablesExist();
}

bool RecipeDatabase::storeRecipe(Recipe recipe){
	///TODO: Implement this in a smart way using transaction.
	this->executeSQL("BEGIN;");
	ResultTable t = this->selectFrom("recipe", "*", "name="+surroundString(recipe.getName(), "'"));
	if (!t.isEmpty()){
		fprintf(stderr, "Error storing recipe: Recipe with name %s already exists.\n", recipe.getName().c_str());
	} else {
		bool success = this->insertInto("recipe",
						 vector<string>({
											"name",
											"createdDate",
											"cookTime",
											"prepTime",
											"servingCount"
										}),
						 vector<string>({
											recipe.getName(),
											recipe.getCreatedDate().toString().toStdString(),
											recipe.getCookTime().toString().toStdString(),
											recipe.getPrepTime().toString().toStdString(),
											std::to_string(recipe.getServings())
										}));
		if (success){
			//If successful, proceed to insert instructions, image, and ingredients, and tags.
			int recipeId = this->getLastInsertedRowId();
			bool ingredientSuccess = true;
			for (unsigned int i = 0; i < recipe.getIngredients().size(); i++){
				if (!this->storeRecipeIngredient(recipe.getIngredients()[i], recipeId)){
					ingredientSuccess = false;
					break;
				}
			}
			if (ingredientSuccess &&
					this->storeInstruction(recipe.getInstruction(), recipeId) &&
					this->storeImage(recipe.getImage(), recipeId) &&
					this->storeTags(recipe.getTags(), recipeId)){
				this->executeSQL("COMMIT;");
				return true;
			}
		}
	}
	this->executeSQL("ROLLBACK;");
	return false;
}

bool RecipeDatabase::storeRecipeIngredient(RecipeIngredient ri, int recipeId){
	//First check if the base ingredient has been added to the database. This is done within storeIngredient().
	ResultTable t = this->selectFrom("ingredient", "ingredientId", "name="+surroundString(ri.getName(), "'"));
	int ingId = 0;
	if (t.isEmpty()){
		if (!this->insertInto("ingredient", vector<string>({"foodGroup", "name"}), vector<string>({ri.getFoodGroup(), ri.getName()}))){
			return false;
		}
		ingId = this->getLastInsertedRowId();
	} else {
		ingId = std::stoi(t.valueAt(0, 0));
	}
	return this->insertInto("recipeIngredient",
					 vector<string>({
										"ingredientId",
										"recipeId",
										"quantity",
										"unitName",
										"comment"
									}),
					 vector<string>({
										std::to_string(ingId),
										std::to_string(recipeId),
										std::to_string(ri.getQuantity()),
										ri.getUnit().getName(),
										ri.getComment()
									}));
}

void RecipeDatabase::storeIngredient(Ingredient ingredient){
	ResultTable t = this->selectFrom("ingredient", "*", "name="+surroundString(ingredient.getName(), "'"));
	if (t.isEmpty()){
		this->insertInto("ingredient", vector<string>({"foodGroup", "name"}), vector<string>({ingredient.getFoodGroup(), ingredient.getName()}));
	}
}

bool RecipeDatabase::storeInstruction(Instruction instruction, int recipeId){
	return FileUtils::saveInstruction(recipeId, instruction);
}

bool RecipeDatabase::storeImage(QImage image, int recipeId){
	return FileUtils::saveImage(recipeId, image);
}

bool RecipeDatabase::storeTags(vector<RecipeTag> tags, int recipeId){
	for (vector<RecipeTag>::iterator it = tags.begin(); it != tags.end(); ++it){
		bool s = this->insertInto("recipeTag",
								  vector<string>({
													 "recipeId",
													 "tagName"
												 }),
								  vector<string>({
													 std::to_string(recipeId),
													 (*it).getValue()
												 }));
		if (!s){
			return false;
		}
	}
	return true;
}

Recipe RecipeDatabase::retrieveRecipe(string name){
	ResultTable t = this->selectFrom("recipe", "*", "name="+surroundString(name, "'"));
	if (t.isEmpty()){
		fprintf(stderr, "Error: No recipe with name %s found!\n", name.c_str());
		return Recipe();
	}
	Recipe r;
	int id = std::stoi(t.valueAt(0, 0));
	r.setName(t.valueAt(0, 1));
	r.setCreatedDate(QDate::fromString(QString::fromStdString(t.valueAt(0, 2))));
	r.setPrepTime(QTime::fromString(QString::fromStdString(t.valueAt(0, 3))));
	r.setCookTime(QTime::fromString(QString::fromStdString(t.valueAt(0, 4))));
	r.setServings(std::stof(t.valueAt(0, 5)));
	r.setInstruction(FileUtils::loadInstruction(id));
	r.setImage(FileUtils::loadImage(id));
	r.setIngredients(this->retrieveRecipeIngredients(id));
	return r;
}

vector<RecipeIngredient> RecipeDatabase::retrieveRecipeIngredients(int recipeId){
	ResultTable t = this->executeSQL("SELECT ingredient.name, ingredient.foodGroup, recipeIngredient.quantity, recipeIngredient.unitName, recipeIngredient.comment "
									 "FROM ingredient "
									 "INNER JOIN recipeIngredient "
									 "ON ingredient.ingredientId = recipeIngredient.ingredientId "
									 "AND recipeIngredient.recipeId = "+std::to_string(recipeId)+";");
	vector<RecipeIngredient> ings;
	for (unsigned int row = 0; row < t.rowCount(); row++){
		RecipeIngredient r(t.valueAt(row, 0), t.valueAt(row, 1), std::stof(t.valueAt(row, 2)), UnitOfMeasure(t.valueAt(row, 3)));
		ings.push_back(r);
	}
	return ings;
}

void RecipeDatabase::ensureTablesExist(){
	//Make sure that foreign keys are enabled.
	this->executeSQL("PRAGMA foreign_keys = ON;");

	this->executeSQL("BEGIN;");
	//Ingredients table.
	this->executeSQL("CREATE TABLE IF NOT EXISTS ingredient("
					 "ingredientId INTEGER PRIMARY KEY,"
					 "foodGroup varchar,"
					 "name varchar UNIQUE);");
	//Recipe table. Each recipe can have at most one instruction, and one image.
	this->executeSQL("CREATE TABLE IF NOT EXISTS recipe("
					 "recipeId INTEGER PRIMARY KEY,"
					 "name varchar UNIQUE,"
					 "createdDate date,"
					 "prepTime time,"
					 "cookTime time,"
					 "servingCount real);");
	//Recipe tags table.
	this->executeSQL("CREATE TABLE IF NOT EXISTS recipeTag("
					 "recipeId int,"
					 "tagName varchar,"
					 "FOREIGN KEY (recipeId) REFERENCES recipe(recipeId));");
	//RecipeIngredient table.
	this->executeSQL("CREATE TABLE IF NOT EXISTS recipeIngredient("
					 "ingredientId int,"
					 "recipeId int,"
					 "quantity real,"
					 "unitName varchar,"
					 "comment varchar,"
					 "FOREIGN KEY (ingredientId) REFERENCES ingredient(ingredientId),"
					 "FOREIGN KEY (recipeId) REFERENCES recipe(recipeId));");
	this->executeSQL("COMMIT;");
}
