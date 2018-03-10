#include "model/database/database.h"

Database::Database(string filename){
    this->filename = filename;
    openConnection();
}

Database::~Database(){
	closeConnection();
}

ResultTable Database::executeSQL(string statement){
	sqlite3_stmt* stmt;
	this->sql = statement;
	this->returnCode = sqlite3_prepare_v2(this->db, statement.c_str(), -1, &stmt, NULL);
	ResultTable t(statement);
	if (this->returnCode != SQLITE_OK){
		fprintf(stderr, "Unable to successfully prepare SQL statement. Error code: %d\n\tError Message: %s\n", this->returnCode, sqlite3_errmsg(this->db));
		return t;
	}

	t.extractData(stmt);

	this->returnCode = sqlite3_finalize(stmt);

	return t;
}

bool Database::insertInto(string tableName, vector<string> columnNames, vector<string> values){
	if (columnNames.size() != values.size() || columnNames.empty()){
		return false;
	}
	string query = "INSERT INTO "+tableName+" (";
	string cols = combineVector(columnNames, ", ");
	string vals = combineVector(values, ", ");
	query += cols + ") VALUES (" + vals + ");";
	ResultTable t = this->executeSQL(query);
	return (t.getReturnCode() == SQLITE_DONE);
}

ResultTable Database::selectFrom(string tableName, string columnNames, string conditions){
	if (columnNames.size() == 0 || tableName.empty()){
		return ResultTable();
	}
	string query = "SELECT " + columnNames + " FROM " + tableName + " " + conditions + ";";
	return this->executeSQL(query);
}

void Database::openConnection(){
    this->returnCode = sqlite3_open(this->filename.c_str(), &this->db);
    if (this->returnCode || this->db == NULL){
        this->dbIsOpen = false;
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(EXIT_FAILURE);
    } else {
        this->dbIsOpen = true;
    }
}

void Database::closeConnection(){
    this->returnCode = sqlite3_close(this->db);
	this->dbIsOpen = false;
}

string Database::combineVector(std::vector<string> strings, string mid){
	if (strings.empty()){
		return "";
	}
	std::string result = surroundString(strings[0], "'");
	for (std::vector<std::string>::iterator it = strings.begin() + 1; it != strings.end(); ++it){
		result += mid + surroundString((*it), "'");
	}
	return result;
}

string Database::surroundString(string s, string surround){
	return surround+s+surround;
}

bool Database::tableExists(string tableName){
	if (tableName.empty() || this->db == NULL || !this->dbIsOpen){
		return false;
	}
	ResultTable t = this->selectFrom("sqlite_master", "name", "WHERE type='table' AND name='"+tableName+"'");
	return !t.isEmpty();
}

int Database::getLastInsertedRowId(){
	return sqlite3_last_insert_rowid(this->db);
}
