#include "model/database/database.h"

Database::Database(string filename){
    this->filename = filename;
	this->queryCount = 0;
    openConnection();
}

Database::~Database(){
	closeConnection();
}

ResultTable Database::executeSQL(string statement){
	sqlite3_stmt* stmt;
	this->sql = statement;
	this->returnCode = sqlite3_prepare_v2(this->db, statement.c_str(), -1, &stmt, NULL);
	if (this->returnCode != SQLITE_OK){
		fprintf(stderr, "Unable to successfully prepare SQL statement. Error code: %d\n\tError Message: %s\nSQL Statement: %s\n",
				this->returnCode,
				sqlite3_errmsg(this->db),
				statement.c_str());
		return ResultTable(this->returnCode);
	}
	ResultTable t(statement);
	t.extractData(stmt);

	this->returnCode = sqlite3_finalize(stmt);
	this->queryCount++;

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

bool Database::insertInto(string tableName, string columnName, string value){
	if (columnName.empty() || value.empty() || tableName.empty()){
		return false;
	}
	string query = "INSERT INTO " + tableName + " (" + columnName + ") VALUES (" + value + ");";
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

bool Database::deleteFrom(string tableName, string conditions){
	if (tableName.empty()){
		return false;
	}
	string query = "DELETE FROM " + tableName + " " + conditions + ";";
	ResultTable t = this->executeSQL(query);
	if (t.getReturnCode() != SQLITE_DONE){
		fprintf(stderr, "Can't delete from table %s.Return code: %d\n%s\n", tableName.c_str(), t.getReturnCode(), sqlite3_errmsg(this->db));
		exit(EXIT_FAILURE);
	} else {
		return true;
	}
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

void Database::beginTransaction(){
	this->executeSQL("BEGIN;");
}

void Database::commitTransaction(){
	this->executeSQL("COMMIT;");
}

void Database::rollbackTransaction(){
	this->executeSQL("ROLLBACK;");
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

int Database::getLastInsertedRowId() const{
	return sqlite3_last_insert_rowid(this->db);
}

unsigned long Database::getQueryCount() const{
	return this->queryCount;
}
