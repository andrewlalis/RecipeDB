#include "resulttable.h"

ResultTable::ResultTable(){

}

ResultTable::ResultTable(string query){
	this->originalQuery = query;
}

ResultTable::ResultTable(int resultCode){
	this->queryCode = resultCode;
}

void ResultTable::extractData(sqlite3_stmt *stmt){
	this->values.clear();
	int res = sqlite3_step(stmt);
	while (res == SQLITE_ROW){
		processRow(stmt);
		res = sqlite3_step(stmt);
	}
	this->queryCode = res;
}

void ResultTable::processRow(sqlite3_stmt *stmt){
	int colCount = sqlite3_column_count(stmt);
	vector<string> currentRow;

	for (int i = 0; i < colCount; i++){
		currentRow.push_back(convertToString(sqlite3_column_value(stmt, i)));
	}

	this->values.push_back(currentRow);
}

void ResultTable::printData(){
	printf("--> Result Code: [%d] <--\n", this->getReturnCode());
	if (this->isEmpty()){
		printf("Result table is empty.\n");
		return;
	}
	printf("Printing table: [%d x %d]\t%s\n", this->rowCount(), this->columnCount(), this->originalQuery.c_str());
	for (unsigned int row = 0; row < this->rowCount(); row++){
		for (unsigned int col = 0; col < this->columnCount(); col++){
			printf("| %s ", this->values[row][col].c_str());
		}
		printf("\n");
	}
}

bool ResultTable::isEmpty(){
	return this->values.empty();
}

string ResultTable::at(unsigned int row, unsigned int col){
	if (isIndexValid(row, col)){
		return this->values[row][col];
	} else {
		fprintf(stderr, "Out of bounds error while trying to get value in result table at [%d, %d].\n", row, col);
		return "";
	}
}

int ResultTable::getReturnCode(){
	return this->queryCode;
}

string ResultTable::getOriginalQuery(){
	return this->originalQuery;
}

unsigned int ResultTable::columnCount(){
	if (this->isEmpty()){
		return 0;
	}
	return this->values[0].size();
}

unsigned int ResultTable::rowCount(){
	if (this->isEmpty()){
		return 0;
	}
	return this->values.size();
}

vector<vector<string> > ResultTable::rows(){
	return this->values;
}

string ResultTable::convertToString(sqlite3_value *val){
	const unsigned char* raw_text = sqlite3_value_text(val);
	if (raw_text == 0){
		return "";
	}
	string st = (const char*) raw_text;
	return st;
}

bool ResultTable::isIndexValid(unsigned int row, unsigned int col){
	return (row < this->values.size()) && (col < this->values[0].size());
}
