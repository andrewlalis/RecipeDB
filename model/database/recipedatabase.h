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
		bool storeRecipeIngredient(RecipeIngredient ri, int recipeId);
		void storeIngredient(Ingredient ingredient);
		bool storeInstruction(Instruction instruction, int recipeId);
		bool storeImage(QImage image, int recipeId);

		vector<Recipe> retrieveRecipe(string name);
	private:

		//Utility methods.
		void ensureTablesExist();
};

#endif // RECIPEDATABASE_H
