/*
 Created by mjh438 on 11/26/2018.

 Web resources used:

 https://www.sqlite.org/cintro.html
 https://www.tutorialspoint.com/sqlite/index.htm

 */

#ifndef FINALPROJECTX_SQLINK_H
#define FINALPROJECTX_SQLINK_H

#include <string>
#include "sqlite3.h"
#include <iostream>
#include <vector>
//#include <Rcpp.h>

using namespace std;

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    for(i = 0; i<argc; i++) {
        cout<<azColName[i]<<"="<<(argv[i]?argv[i]:"NULL")<<"\n";
    }
    cout<<"\n";
    return 0;
}


// From: https://stackoverflow.com/questions/15836253/c-populate-vector-from-sqlite3-callback-function
typedef vector<vector<string> > table_type;
static int callbackExtract(void *ptr, int argc, char* argv[], char* cols[])
{
    table_type* table = static_cast<table_type*>(ptr);
    vector<string> row;
    for (int i = 0; i < argc; i++)
        row.push_back(argv[i] ? argv[i] : "(NULL)");
    table->push_back(row);
    return 0;
}

class Sqlink {

public:
    Sqlink(); //generates an Sqlink object with an example database
    Sqlink(char dbfile[]); // opens a database file

    void print(); // Print database information to console
    void command(char cmd[]); // run a custom sqlite command
    void makeExample(); // Generate the example database
    void createTable(string tableName, vector<string> columnNames, vector<string> columnTypes);

    vector<string> listTables(); //Makes a vector of the names of tables inside the database

    table_type extract(const char* query); //Select data in this->db and extract it
    table_type extractTable(string tableName); //Select table in this->db and extract it


    void deleteEntry(string Table, char Criteria[]); //Delete data in this->db
    void update(string Table, char Criteria[], char newContent[]); //update data in this->db
    void insert(string Table, char Criteria[], char newContent[]); //insert data in this->db



    void open(const char *filename); //opens sqlite connection to a file
    bool isOpen = false;

    void close(); //closes the connection for db in this object


    void update(char cmd[]); // update a table




private:
    sqlite3 *db;


};


#endif //FINALPROJECTX_SQLINK_H
