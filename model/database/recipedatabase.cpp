#include "recipedatabase.h"

RecipeDatabase::RecipeDatabase(string filename) : Database(filename){
	this->ensureTablesExist();
}

void RecipeDatabase::storeRecipe(Recipe recipe){
	///TODO: Implement this in a smart way using transaction.

}

void RecipeDatabase::ensureTablesExist(){
	//Make sure that foreign keys are enabled.
	this->executeSQL("PRAGMA foreign_keys = ON;");
	//Ingredients table.
	this->executeSQL("CREATE TABLE IF NOT EXISTS ingredient("
					 "ingredientId INTEGER PRIMARY KEY,"
					 "foodGroup varchar,"
					 "name varchar);");
	//Images table.
	this->executeSQL("CREATE TABLE IF NOT EXISTS image("
					 "imageNr INTEGER PRIMARY KEY,"
					 "contentURL varchar);");
	//Instructions table.
	this->executeSQL("CREATE TABLE IF NOT EXISTS instruction("
					 "instructionNr INTEGER PRIMARY KEY,"
					 "contentURL varchar);");
	//Recipe table.
	this->executeSQL("CREATE TABLE IF NOT EXISTS recipe("
					 "recipeId INTEGER PRIMARY KEY,"
					 "date date,"
					 "name varchar,"
					 "imageNr int,"
					 "cookTime time,"
					 "prepTime time,"
					 "servingCount real,"
					 "FOREIGN KEY (imageNr) REFERENCES image(imageNr));");
	//Recipe tags table.
	this->executeSQL("CREATE TABLE IF NOT EXISTS recipeTag("
					 "recipeId INTEGER PRIMARY KEY,"
					 "tagName varchar,"
					 "FOREIGN KEY (recipeId) REFERENCES recipe(recipeId));");
	//RecipeIngredient table.
	this->executeSQL("CREATE TABLE IF NOT EXISTS recipeIngredient("
					 "ingredientId int,"
					 "recipeId INTEGER PRIMARY KEY,"
					 "quantity real,"
					 "unitName varchar,"
					 "comment varchar,"
					 "FOREIGN KEY (ingredientId) REFERENCES ingredient(ingredientId),"
					 "FOREIGN KEY (recipeId) REFERENCES recipe(recipeId));");
	//Recipe Instruction mapping table.
	this->executeSQL("CREATE TABLE IF NOT EXISTS recipeInstruction("
					 "instructionNr int,"
					 "recipeId INTEGER PRIMARY KEY,"
					 "FOREIGN KEY (instructionNr) REFERENCES instruction(instructionNr),"
					 "FOREIGN KEY (recipeId) REFERENCES recipe(recipeId));");
}

void RecipeDatabase::storeInstruction(Instruction instruction){

}

void RecipeDatabase::storeImage(QImage image){

}

void RecipeDatabase::storeIngredient(Ingredient ingredient){
	ResultTable t = this->executeSQL("SELECT * FROM ingredient WHERE name='"+ingredient.getName()+"';");
	if (!t.isEmpty()){
		fprintf(stderr, "Error during storeIngredient: ingredient with name %s already exists.\n", ingredient.getName().c_str());
	} else {
		this->executeSQL("INSERT INTO ingredient (foodGroup, name) VALUES ('"+ ingredient.getFoodGroup() +"', '"+ ingredient.getName() +"');");
	}
}
