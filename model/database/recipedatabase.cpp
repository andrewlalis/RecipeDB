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
					 "ingredientId int,"
					 "foodGroup varchar,"
					 "name varchar,"
					 "PRIMARY KEY (ingredientId));");
	//Images table.
	this->executeSQL("CREATE TABLE IF NOT EXISTS image("
					 "imageNr int,"
					 "contentURL varchar,"
					 "PRIMARY KEY (imageNr));");
	//Instructions table.
	this->executeSQL("CREATE TABLE IF NOT EXISTS instruction("
					 "instructionNr int,"
					 "contentURL varchar,"
					 "PRIMARY KEY (instructionNr));");
	//Recipe table.
	this->executeSQL("CREATE TABLE IF NOT EXISTS recipe("
					 "recipeId int,"
					 "date date,"
					 "name varchar,"
					 "imageNr int,"
					 "cookTime time,"
					 "prepTime time,"
					 "servingCount real,"
					 "PRIMARY KEY (recipeId),"
					 "FOREIGN KEY (imageNr) REFERENCES image(imageNr));");
	//Recipe tags table.
	this->executeSQL("CREATE TABLE IF NOT EXISTS recipeTag("
					 "recipeId int,"
					 "tagName varchar,"
					 "PRIMARY KEY (recipeId),"
					 "FOREIGN KEY (recipeId) REFERENCES recipe(recipeId));");
	//RecipeIngredient table.
	this->executeSQL("CREATE TABLE IF NOT EXISTS recipeIngredient("
					 "ingredientId int,"
					 "recipeId int,"
					 "quantity real,"
					 "unitName varchar,"
					 "comment varchar,"
					 "PRIMARY KEY (recipeId),"
					 "FOREIGN KEY (ingredientId) REFERENCES ingredient(ingredientId),"
					 "FOREIGN KEY (recipeId) REFERENCES recipe(recipeId));");
	//Recipe Instruction mapping table.
	this->executeSQL("CREATE TABLE IF NOT EXISTS recipeInstruction("
					 "instructionNr int,"
					 "recipeId int,"
					 "PRIMARY KEY (recipeId),"
					 "FOREIGN KEY (instructionNr) REFERENCES instruction(instructionNr),"
					 "FOREIGN KEY (recipeId) REFERENCES recipe(recipeId));");
}
