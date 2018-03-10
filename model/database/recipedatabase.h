#ifndef RECIPEDATABASE_H
#define RECIPEDATABASE_H



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
		bool storeInstruction(Instruction instruction, int recipeId);
		bool storeImage(QImage image, int recipeId);
		bool storeTags(vector<RecipeTag> tags, int recipeId);

		//Retrieval.
		Recipe retrieveRecipe(string name);
		vector<RecipeIngredient> retrieveRecipeIngredients(int recipeId);
		vector<Ingredient> retrieveAllIngredients();
		vector<UnitOfMeasure> retrieveAllUnitsOfMeasure();
		vector<RecipeTag> retrieveTags(int recipeId);
		vector<RecipeTag> retrieveAllTags();

		//Deletion.
		void deleteTag(RecipeTag tag);
	private:

		//Utility methods.
		void ensureTablesExist();
};

#endif // RECIPEDATABASE_H
