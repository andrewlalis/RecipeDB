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
    ~Database();

    void insertIngredient(Ingredient);

private:
    //SQL Instance variables.
    string filename;
    sqlite3* db;
    bool dbIsOpen;
    int returnCode;
    string sql;
    char* errorMsg;

    void openConnection();
    void closeConnection();
    //Guarantees that all tables from the schema exist.
    void ensureTablesExist();

    //Utility methods.
    bool tableExists(string tableName);
};

#endif // DATABASE_H
