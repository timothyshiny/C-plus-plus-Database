/*
// Created by mjh438 on 11/26/2018.

 Web resources used:

 https://www.sqlite.org/cintro.html
 https://www.tutorialspoint.com/sqlite/index.htm

 */

#include "Sqlink.h"
using namespace std;

Sqlink::Sqlink(){}



Sqlink::Sqlink(char dbfile[]){

    this->open(dbfile);

}

void Sqlink::makeExample(){

    const int STATEMENTS = 5;
    char *zErrMsg = 0;
    const char *pSQL[STATEMENTS];

    int rc;
    this->open("example.db");


    pSQL[0] = "create table FamilyGuy (FirstName varchar(30), LastName varchar(30), Age smallint, Hometown varchar(30), Job varchar(30))";

    pSQL[1] = "insert into FamilyGuy (FirstName, LastName, Age, Hometown, Job) values ('Peter', 'Griffin', 41, 'Quahog', 'Brewery')";

    pSQL[2] = "insert into FamilyGuy (FirstName, LastName, Age, Hometown, Job) values ('Lois', 'Griffin', 40, 'Newport', 'Piano Teacher')";

    pSQL[3] = "insert into FamilyGuy (FirstName, LastName, Age, Hometown, Job) values ('Joseph', 'Swanson', 39, 'Quahog', 'Police Officer')";

    pSQL[4] = "insert into FamilyGuy (FirstName, LastName, Age, Hometown, Job) values ('Glenn', 'Quagmire', 41, 'Quahog', 'Pilot')";

    //  pSQL[5] = "select * from myTable";

    for(int i = 0; i < STATEMENTS; i++)
    {
        rc = sqlite3_exec(db, pSQL[i], callback, 0, &zErrMsg);
        if( rc!=SQLITE_OK )
        {
            cout<<"SQL error: "<<sqlite3_errmsg(db)<<"\n";
            sqlite3_free(zErrMsg);
            break;
        }
    }

}

void Sqlink::print(){

    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_exec(this->db, "SELECT * FROM sqlite_master WHERE type='table'", callback, 0, &zErrMsg);
    if( rc!=SQLITE_OK )
    {
        cout<<"SQL error: "<<sqlite3_errmsg(this->db)<<"\n";
        sqlite3_free(zErrMsg);
    }
}

table_type Sqlink::extract(const char* query){

    char *zErrMsg = 0;
    int rc;
    table_type extab;

    rc = sqlite3_exec(this->db, query, callbackExtract, &extab, &zErrMsg);
    if( rc!=SQLITE_OK )
    {
        cout<<"SQL error: "<<sqlite3_errmsg(this->db)<<"\n";
        sqlite3_free(zErrMsg);
    }

    return(extab);
}

vector<string> Sqlink::listTables() {
    // vector<string> results;
    table_type queryResults;

    queryResults = this->extract("SELECT name FROM sqlite_master WHERE type='table'");

    return queryResults[0];

}

void Sqlink::command(char cmd[]){

    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_exec(db, cmd, callback, 0, &zErrMsg);
    if( rc!=SQLITE_OK )
    {
        cout<<"SQL error: "<<sqlite3_errmsg(db)<<"\n";
        sqlite3_free(zErrMsg);
    }
}

void Sqlink::open(const char *filename){
    int rc;

    rc = sqlite3_open(filename, &db);

    if( rc )
    {
        cout<<"Can't open database: "<<sqlite3_errmsg(db)<<"\n";
    }
    else
    {
        cout<<"Database opened successfully\n\n";
    }

    this->isOpen = true;
}

void Sqlink::close(){
    sqlite3_close(db);

    this->isOpen = false;
}

void Sqlink::createTable(string tableName,
                         vector <string> columnNames,
                         vector <string> columnTypes) {
    string command;



    command = "CREATE TABLE " + tableName;



}

table_type Sqlink::extractTable( string tableName) {

    table_type header = this->extract( ( "PRAGMA table_info(" + tableName + ")").c_str() );
    table_type content = this->extract( ( "SELECT * FROM " + tableName).c_str() );
    table_type output;

    vector<string> colNames;

    for(vector<string> i: header){

        colNames.push_back(i[1]);

    }

    output.push_back(colNames);

    for(vector<string> i: content){

        output.push_back(i);

    };

    return (output);

}
