#ifndef RESULTTABLE_H
#define RESULTTABLE_H

#include <vector>
#include <string>

#include "SQLite/sqlite3.h"

using namespace std;

/**
 * @brief The ResultTable class is an object that contains the results of an SQL query, in string form.
 */

typedef vector<string> TableRow;

class ResultTable
{
	public:
		//Constructs an empty table.
		ResultTable();
		//Constructs a table with the original query saved.
		ResultTable(string query);
		//Constructs an empty table with a result code.
		ResultTable(int resultCode);

		//Gets all the data from the result set and stores it internally as strings.
		void extractData(sqlite3_stmt* stmt);
		//Stores the information from one row of a result set.
		void processRow(sqlite3_stmt* stmt);
		//Displays the data somewhat legibly.
		void printData();

		bool isEmpty();
		string at(unsigned int row, unsigned int col);
		int getReturnCode();
		string getOriginalQuery();
		unsigned int columnCount();
		unsigned int rowCount();
		vector<vector<string>> rows();
	private:
		vector<vector<string>> values;
		int queryCode;
		string originalQuery;

		//Utility methods.
		string convertToString(sqlite3_value* val);
		bool isIndexValid(unsigned int row, unsigned int col);
};

#endif // RESULTTABLE_H
