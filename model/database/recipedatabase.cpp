#include "recipedatabase.h"

RecipeDatabase::RecipeDatabase(string filename) : Database(filename){
	this->ensureTablesExist();
}

bool RecipeDatabase::storeRecipe(Recipe recipe){
	//Some primary checks to avoid garbage in the database.
	if (recipe.getName().empty() ||
			recipe.getInstruction().getHTML().empty() ||
			recipe.getIngredients().empty()){
		return false;
	}
	//Store a recipe, if it doesn't already exist. This first tries to create the recipe entry, then all subsequent supporting table entries.
	this->executeSQL("BEGIN;");
	ResultTable t = this->selectFrom("recipe", "*", "WHERE name="+surroundString(recipe.getName(), "'"));
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
	int ingId = this->storeIngredient(ri);
	if (ingId < 0) return false;

	if (!this->storeUnitOfMeasure(ri.getUnit())) return false;

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

int RecipeDatabase::storeIngredient(Ingredient ingredient){
	ResultTable t = this->selectFrom("ingredient", "*", "WHERE name="+surroundString(ingredient.getName(), "'"));
	if (t.isEmpty()){
		bool success = this->insertInto("ingredient", vector<string>({"foodGroup", "name"}), vector<string>({ingredient.getFoodGroup(), ingredient.getName()}));
		if (success){
			return this->getLastInsertedRowId();
		} else {
			return -1;
		}
	} else {
		return std::stoi(t.valueAt(0, 0));
	}
}

bool RecipeDatabase::storeUnitOfMeasure(UnitOfMeasure u){
	ResultTable t = this->selectFrom("unitOfMeasure", "name", "WHERE name="+surroundString(u.getName(), "'"));
	if (!t.isEmpty()){
		return true;
	}
	bool success = this->insertInto("unitOfMeasure",
									vector<string>({
													   "name",
													   "plural",
													   "abbreviation",
													   "type",
													   "metricCoefficient"
												   }),
									vector<string>({
													   u.getName(),
													   u.getNamePlural(),
													   u.getAbbreviation(),
													   std::to_string(u.getType()),
													   std::to_string(u.getMetricCoefficient())
												   }));
	return success;
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
	ResultTable t = this->selectFrom("recipe", "*", "WHERE name="+surroundString(name, "'"));
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
	r.setTags(this->retrieveTags(id));
	return r;
}

vector<Recipe> RecipeDatabase::retrieveAllRecipes(){
	ResultTable t = this->selectFrom("recipe", "name", "ORDER BY name");
	vector<Recipe> recipes;
	for (unsigned int row = 0; row < t.rowCount(); row++){
		recipes.push_back(this->retrieveRecipe(t.valueAt(row, 0)));
	}
	return recipes;
}

vector<RecipeIngredient> RecipeDatabase::retrieveRecipeIngredients(int recipeId){
	ResultTable t = this->executeSQL("SELECT ingredient.name, ingredient.foodGroup, "//0, 1
									 "recipeIngredient.quantity, recipeIngredient.unitName, recipeIngredient.comment,"//2, 3, 4
									 "unitOfMeasure.name, unitOfMeasure.plural, unitOfMeasure.abbreviation, unitOfMeasure.type, unitOfMeasure.metricCoefficient "//5, 6, 7, 8, 9
									 "FROM ingredient "
									 "INNER JOIN recipeIngredient "
									 "ON ingredient.ingredientId = recipeIngredient.ingredientId "
									 "INNER JOIN unitOfMeasure "
									 "ON recipeIngredient.unitName = unitOfMeasure.name "
									 "WHERE recipeIngredient.recipeId = "+std::to_string(recipeId)+";");
	vector<RecipeIngredient> ings;
	for (unsigned int row = 0; row < t.rowCount(); row++){
		RecipeIngredient r(t.valueAt(row, 0),
						   t.valueAt(row, 1),
						   std::stof(t.valueAt(row, 2)),
						   UnitOfMeasure(t.valueAt(row, 5), t.valueAt(row, 6), t.valueAt(row, 7), std::stoi(t.valueAt(row, 8)), std::stod(t.valueAt(row, 9))),
						   t.valueAt(row, 4));
		ings.push_back(r);
	}
	return ings;
}

vector<Ingredient> RecipeDatabase::retrieveAllIngredients(){
	ResultTable t = this->selectFrom("ingredient", "*", "ORDER BY name");
	vector<Ingredient> ings;
	for (unsigned int row = 0; row < t.rowCount(); row++){
		Ingredient i(t.valueAt(row, 2), t.valueAt(row, 1));
		ings.push_back(i);
	}
	return ings;
}

vector<UnitOfMeasure> RecipeDatabase::retrieveAllUnitsOfMeasure(){
	ResultTable t = this->selectFrom("unitOfMeasure", "*", "ORDER BY name");
	vector<UnitOfMeasure> units;
	if (!t.isEmpty()){
		for (unsigned int row = 0; row < t.rowCount(); row++){
			UnitOfMeasure u(t.valueAt(row, 0), t.valueAt(row, 1), t.valueAt(row, 2), std::stoi(t.valueAt(row, 3)), std::stod(t.valueAt(row, 4)));
			units.push_back(u);
		}
	}
	return units;
}

vector<RecipeTag> RecipeDatabase::retrieveTags(int recipeId){
	ResultTable t = this->selectFrom("recipeTag", "tagName", "WHERE recipeId="+std::to_string(recipeId));
	vector<RecipeTag> tags;
	if (!t.isEmpty()){
		for (unsigned int row = 0; row < t.rowCount(); row++){
			RecipeTag tag(t.valueAt(row, 0));
			tags.push_back(tag);
		}
	}
	return tags;
}

vector<RecipeTag> RecipeDatabase::retrieveAllTags(){
	ResultTable t = this->selectFrom("recipeTag", "tagName", "ORDER BY tagName");
	vector<RecipeTag> tags;
	if (!t.isEmpty()){
		for (unsigned int row = 0; row < t.rowCount(); row++){
			RecipeTag tag(t.valueAt(row, 0));
			tags.push_back(tag);
		}
	}
	return tags;
}

bool RecipeDatabase::deleteRecipe(string name){
	ResultTable t = this->selectFrom("recipe", "recipeId", "WHERE name="+name);
	if (t.rowCount() != 1){
		return false;
	}
	string recipeId = t.valueAt(0, 0);
	return this->deleteRecipe(std::stoi(recipeId));
}

bool RecipeDatabase::deleteRecipe(int recipeId){
	string idString = std::to_string(recipeId);
	if (this->selectFrom("recipe", "recipeId", "WHERE recipeId="+idString).isEmpty()){
		return false;
	}
	this->executeSQL("BEGIN;");
	bool tagsDeleted = this->deleteFrom("recipeTag", "WHERE recipeId="+idString);
	bool recipeIngredientDeleted = this->deleteFrom("recipeIngredient", "WHERE recipeId="+idString);
	bool recipeDeleted = this->deleteFrom("recipe", "WHERE recipeId="+idString);
	if (tagsDeleted && recipeIngredientDeleted && recipeDeleted){
		this->executeSQL("COMMIT;");
		return true;
	} else {
		this->executeSQL("ROLLBACK;");
		return false;
	}
}

bool RecipeDatabase::deleteIngredient(string name){
	ResultTable t = this->selectFrom("recipeIngredient", "recipeId", "WHERE ingredientId=("
																	 "SELECT ingredientId"
																	 "FROM ingredient"
																	 "WHERE name="+name+")");
	if (!t.isEmpty()){
		//There is at least one recipe dependent on the ingredient.
		return false;
	}
	return this->deleteFrom("ingredient", "WHERE name="+name);
}

bool RecipeDatabase::deleteUnitOfMeasure(string name){
	ResultTable t = this->selectFrom("recipeIngredient", "recipeId", "WHERE unitName="+name);
	if (!t.isEmpty()){
		return false;
	}
	return this->deleteFrom("unitOfMeasure", "WHERE name="+name);
}

bool RecipeDatabase::deleteTag(RecipeTag tag){
	return this->deleteFrom("recipeTag", "WHERE tagName="+tag.getValue());
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
	//Unit of Measure table.
	this->executeSQL("CREATE TABLE IF NOT EXISTS unitOfMeasure("
					 "name varchar UNIQUE PRIMARY KEY,"
					 "plural varchar,"
					 "abbreviation varchar,"
					 "type int,"
					 "metricCoefficient real);");
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
					 "FOREIGN KEY (recipeId) REFERENCES recipe(recipeId),"
					 "FOREIGN KEY (unitName) REFERENCES unitOfMeasure(name));");
	this->executeSQL("COMMIT;");
}
