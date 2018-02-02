#include "model/database/database.h"

Database::Database(){

}

void Database::openConnection(){
    this->returnCode = sqlite3_open(this->filename.c_str(), &this->db);
    if (this->returnCode){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(EXIT_FAILURE);
    }
}
