#ifndef RECIPEDATABASE_H
#define RECIPEDATABASE_H



#include "database.h"
#include "model/recipe/recipe.h"

using namespace std;

/**
 * @brief The RecipeDatabase class represents the precise database used for the recipe storage, and is specialized.
 */

class RecipeDatabase : public Database
{
	public:
		RecipeDatabase(string filename);

		//Stores a full recipe in the database.
		void storeRecipe(Recipe recipe);

		//SQL Helper methods.
		void storeInstruction(Instruction instruction);
		void storeImage(QImage image);
		void storeIngredient(Ingredient ingredient);
	private:

		//Utility methods.
		void ensureTablesExist();
};

#endif // RECIPEDATABASE_H
