#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>
#include <numeric>

#include "SQLite/sqlite3.h"
#include "model/recipe/ingredients/ingredient.h"
#include "resulttable.h"

using namespace std;

/**
 * @brief The Database class is responsible for generic abstraction of commonly used database features.
 */

class Database
{
public:
	//Creates and opens a database connection to a file of the given name. If not there, this will generate a database.
    Database(string filename);
	~Database();

	//Executes an SQL string statement in a safe way and returns the result.
	ResultTable executeSQL(string statement);
	bool insertInto(string tableName, vector<string> columnNames, vector<string> values);
	ResultTable selectFrom(string tableName, string columnNames, string conditions);
	bool deleteFrom(string tableName, string conditions);

	bool tableExists(string tableName);
	int getLastInsertedRowId();

protected:
	string surroundString(string s, string surround);

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
	std::string combineVector(std::vector<std::string> strings, std::string mid);
};

#endif // DATABASE_H
