#include "userInterface/mainwindow.h"
#include <QApplication>
#include <iostream>
#include "SQLite/sqlite3.h"

static int callback(void* data, int rows, char** argv, char** azColName){
    int i;
    fprintf(stderr, "%s: ", (const char*)data);
    for(i=0; i<rows; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    sqlite3* db; //Database object.
    char* zErrMsg = 0; //Error message object.
    int rc; //Return code from sqlite3 calls.
    char* sql; //SQL text code is stored here.
    const char* data = "Callback function called";

    rc = sqlite3_open("test.db", &db);

    if (rc){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(0);
    } else {
        fprintf(stdout, "Opened database successfully\n");
    }

    //Create sample SQL statement.
    sql = "DROP TABLE ingredients;"
          "CREATE TABLE ingredients(" \
          "id int PRIMARY KEY NOT NULL," \
          "name varchar NOT NULL," \
          "foodGroup varchar NOT NULL);";

    //Execute statement.
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

    if (rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Table created successfully.\n");
    }

    //Create some fake data.
    sql = "INSERT INTO ingredients (id, name, foodGroup) VALUES (1, 'flour', 'grains');" \
          "INSERT INTO ingredients (id, name, foodGroup) VALUES (2, 'pasta', 'grains');";

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

    if (rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Records created successfully.\n");
    }

    //Select data.
    sql = "SELECT * FROM ingredients;";

    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

    if (rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Select done successfully.\n");
    }

    sqlite3_close(db);

    return a.exec();
}
