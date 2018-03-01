#ifndef RECIPEDATABASE_H
#define RECIPEDATABASE_H



#include "database.h"

using namespace std;

/**
 * @brief The RecipeDatabase class represents the precise database used for the recipe storage, and is specialized.
 */

class RecipeDatabase : public Database
{
	public:
		RecipeDatabase(string filename);
	private:

		//Utility methods.
		void ensureTablesExist();
};

#endif // RECIPEDATABASE_H
