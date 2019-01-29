/*
 Final project, Group:

 Esuvat Kimberly Bomani, I <ekb72@cornell.edu>
 Boyu Cheng <bc652@cornell.edu>
 Vadim Dumov <vd238@cornell.edu>
 Maximilian Helf <mjh438@cornell.edu>
 Guofeng Shi <gs522@cornell.edu>
 Jiahe Wang <jw828@cornell.edu>


 Web resources used:

 https://www.sqlite.org/cintro.html
 https://www.tutorialspoint.com/sqlite/index.htm

 */

#include <stdio.h>
#include <c++/cstring>
#include "Sqlink.h"




int main(int argc, char* argv[]) {

    if(argc == 1){

        cout << endl << "List of command line options (use in this order):" << endl;

        cout << "-example           Creates an example database (example.db containing Family Guy characters)" << endl;
        cout << "-file FILENAME     select sqlite database file" << endl;
        cout << "-print             Prints a summary of the sqlite database in -file FILENAME" << endl;
        cout << "-sql COMMAND       Performs sqlite commands on the sqlite database in -file FILENAME" << endl;

        cout << endl;
    }

    Sqlink DB;

    for(int i = 1; i<argc; i++) {

        cout << argv[i] << endl;

        string thisArg = argv[i];


        if(thisArg == "-example"){
            DB.makeExample();
            DB.print();
            break;
        };

        if (thisArg == "-file") {

            DB.open(argv[i + 1]); // connects the Sqlink object with the FILENAME
        };

        if(thisArg == "-print"){
            DB.print(); // only works if connection has been opened first
        };

        if(thisArg == "-sql"){
            DB.command(argv[i+1]); // only works if connection has been opened first
        };



    }

    DB.makeExample();
    //DB.open("./chinook.db");
    DB.print();


    table_type results  = DB.extract("PRAGMA table_info(FamilyGuy)");
    table_type results2 = DB.extractTable("FamilyGuy");



    if(DB.isOpen) {
        DB.close();
    }
//    Sqlink test2("familyGuy.db");

  //  test2.print();

    return 0;
}