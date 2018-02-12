#include "model/database/database.h"

Database::Database(string filename){
    this->filename = filename;
    openConnection();
    if (tableExists("ingredients")){
        printf("Ingredients table already exists.\n");
    } else {
        printf("Couldn't find the ingredients table.\n");
    }
}

Database::~Database(){
    closeConnection();
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
    if (this->dbIsOpen){
        this->sql = "SELECT name FROM sqlite_master WHERE type='table' AND name='"+tableName+"';";
        const char* str = this->sql.c_str();
        this->returnCode = sqlite3_exec(this->db, str, NULL, 0, &this->errorMsg);
        if (this->returnCode == SQLITE_ERROR){
            fprintf(stderr, "Unable to select name from master table list: %s\n", this->errorMsg);
            return false;
        } else {
            return true;
        }
    }
    return false;
}
