#ifndef RESULTTABLE_H
#define RESULTTABLE_H

#include <vector>
#include <string>

#include "SQLite/sqlite3.h"

using namespace std;

/**
 * @brief The ResultTable class is an object that contains the results of an SQL query, in string form.
 */

class ResultTable
{
	public:
		//Constructs an empty table.
		ResultTable();

		//Gets all the data from the result set and stores it internally as strings.
		void extractData(sqlite3_stmt* stmt);
		//Stores the information from one row of a result set.
		void processRow(sqlite3_stmt* stmt);
		//Displays the data somewhat legibly.
		void printData();

		bool isEmpty();
		string valueAt(unsigned int row, unsigned int col);
		unsigned int columnCount();
		unsigned int rowCount();
	private:
		vector<vector<string>> values;

		//Utility methods.
		string convertToString(sqlite3_value* val);
		bool isIndexValid(unsigned int row, unsigned int col);
};

#endif // RESULTTABLE_H
