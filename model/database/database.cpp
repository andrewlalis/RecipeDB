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
	ResultTable t;
	if (this->returnCode != SQLITE_OK){
		fprintf(stderr, "Unable to successfully prepare SQL statement. Error code: %d\nError Message: %s\n", this->returnCode, sqlite3_errmsg(this->db));
		return t;
	}

	t.extractData(stmt);

	this->returnCode = sqlite3_finalize(stmt);

	return t;
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

bool Database::tableExists(string tableName){
	if (tableName.empty() || this->db == NULL || !this->dbIsOpen){
		return false;
	}
	ResultTable t = executeSQL("SELECT name FROM sqlite_master WHERE type='table' AND name='"+tableName+"';");
	return !t.isEmpty();
}
