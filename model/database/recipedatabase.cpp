#include "recipedatabase.h"

RecipeDatabase::RecipeDatabase(string filename) : Database(filename){
	this->ensureTablesExist();
}

bool RecipeDatabase::storeRecipe(Recipe recipe){
	///TODO: Implement this in a smart way using transaction.
	ResultTable t = this->executeSQL("SELECT * FROM recipe WHERE name='"+recipe.getName()+"';");
	if (!t.isEmpty()){
		fprintf(stderr, "Error storing recipe: Recipe with name %s already exists.\n", recipe.getName().c_str());
		return false;
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
			//If successful, proceed to insert instructions, image, and ingredients.
			int recipeId = this->getLastInsertedRowId();
			for (unsigned int i = 0; i < recipe.getIngredients().size(); i++){
				if (!this->storeRecipeIngredient(recipe.getIngredients()[i], recipeId)){
					return false;
				}
			}
			if (!this->storeInstruction(recipe.getInstruction(), recipeId)){
				return false;
			}
			if (!this->storeImage(recipe.getImage(), recipeId)){
				return false;
			}
			return true;
		} else {
			return false;
		}
	}
}

bool RecipeDatabase::storeRecipeIngredient(RecipeIngredient ri, int recipeId){
	//First check if the base ingredient has been added to the database. This is done within storeIngredient().
	ResultTable t = this->executeSQL("SELECT ingredientId FROM ingredient WHERE name='"+ri.getName()+"';");
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
	ResultTable t = this->executeSQL("SELECT * FROM ingredient WHERE name='"+ingredient.getName()+"';");
	if (t.isEmpty()){
		this->insertInto("ingredient", vector<string>({"foodGroup", "name"}), vector<string>({ingredient.getFoodGroup(), ingredient.getName()}));
	}
}

bool RecipeDatabase::storeInstruction(Instruction instruction, int recipeId){
	bool success = FileUtils::saveInstruction(recipeId, instruction);
	return success;
}

bool RecipeDatabase::storeImage(QImage image, int recipeId){
	return FileUtils::saveImage(recipeId, image);
}

void RecipeDatabase::ensureTablesExist(){
	//Make sure that foreign keys are enabled.
	this->executeSQL("PRAGMA foreign_keys = ON;");
	//Ingredients table.
	this->executeSQL("CREATE TABLE IF NOT EXISTS ingredient("
					 "ingredientId INTEGER PRIMARY KEY,"
					 "foodGroup varchar,"
					 "name varchar);");
	//Recipe table. Each recipe can have at most one instruction, and one image.
	this->executeSQL("CREATE TABLE IF NOT EXISTS recipe("
					 "recipeId INTEGER PRIMARY KEY,"
					 "createdDate date,"
					 "name varchar,"
					 "cookTime time,"
					 "prepTime time,"
					 "servingCount real);");
	//Recipe tags table.
	this->executeSQL("CREATE TABLE IF NOT EXISTS recipeTag("
					 "recipeId INTEGER PRIMARY KEY,"
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
}
