#ifndef RECIPEDATABASE_H
#define RECIPEDATABASE_H

#include <map>

#include "database.h"
#include "model/recipe/recipe.h"
#include "utils/fileutils.h"

using namespace std;

/**
 * @brief The RecipeDatabase class represents the precise database used for the recipe storage, and is specialized.
 */

class RecipeDatabase : public Database
{
	public:
		RecipeDatabase(string filename);

		//Stores a full recipe in the database.
		bool storeRecipe(Recipe recipe);

		//SQL Helper methods.
		//Storage.
		bool storeRecipeIngredient(RecipeIngredient ri, int recipeId);
		int storeIngredient(Ingredient ingredient);
		bool storeUnitOfMeasure(UnitOfMeasure u);

		//Retrieval.
		Recipe retrieveRecipe(string name);
		Recipe retrieveRandomRecipe();
		vector<Recipe> retrieveAllRecipes();
		vector<Recipe> retrieveRecipesWithIngredients(vector<Ingredient> ingredients);
		vector<Recipe> retrieveRecipesWithTags(vector<RecipeTag> tags);
		vector<Recipe> retrieveRecipesWithSubstring(string s);
		vector<Recipe> retrieveRecipesWithFoodGroups(vector<string> groups);
		vector<string> retrieveAllFoodGroups();
		vector<Ingredient> retrieveAllIngredients();
		vector<UnitOfMeasure> retrieveAllUnitsOfMeasure();
		vector<RecipeTag> retrieveAllTags();

		//Deletion.
		bool deleteRecipe(string name);
		bool deleteRecipe(int recipeId);
		bool deleteIngredient(string name);
		bool deleteUnitOfMeasure(string name);
		bool deleteTag(RecipeTag tag);

		//Updating.
		bool updateRecipe(Recipe recipe, string originalName);

		//Adding basic information at start.
		bool addBasicUnits();
		bool addBasicIngredients();
	private:

		//Utility methods.
		void ensureTablesExist();
		//Read a recipe from a row of a result table.
		Recipe readFromResultTable(ResultTable t, int row=0);
		vector<Recipe> readRecipesFromTable(ResultTable t);

		//Storage
		bool storeInstruction(Instruction instruction, int recipeId);
		bool storeImage(QImage image, int recipeId);
		bool storeTags(vector<RecipeTag> tags, int recipeId);

		//Retrieval
		vector<RecipeTag> retrieveTags(int recipeId);
		vector<RecipeIngredient> retrieveRecipeIngredients(int recipeId);
		int retrieveIngredientId(string ingredientName);

		//Deletion
		bool deleteRecipeTags(int recipeId);
		bool deleteRecipeIngredients(int recipeId);
};

#endif // RECIPEDATABASE_H
