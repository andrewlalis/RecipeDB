#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>

#include "SQLite/sqlite3.h"
#include "model/recipe/ingredient.h"

using namespace std;

class Database
{
public:
    Database(string filename);

    void insertIngredient(Ingredient);
    vector<Ingredient> getIngredients();
private:
    string filename;
    sqlite3* db;
    int returnCode;
    string sql;
    char* errorMsg;

    void openConnection();
};

#endif // DATABASE_H
