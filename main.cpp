/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : Vinci Velasco
// St.# : 301430456
// Email: vvv@sfu.ca
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough
// detail so that someone can see the exact source and extent of the
// borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have
// not seen solutions from other students, tutors, websites, books,
// etc.
//
/////////////////////////////////////////////////////////////////////////

// 1. https://www.cplusplus.com/reference/string/string/find/
// used to understand how to use stl for finding substrings in strings




#include "database.h"
#include "record.h"
#include "menu.h"
#include <iostream>
#include <string>
#include <limits>

using namespace std;

int main()
{
    Video_Game_tests();
    Database_tests();

    Menu menus;
    menus.main_menu();

    // main program loop
    while (true) {
        string input = "";
        getline(cin, input);
        if (input == "1") {
            menus.add_menu();
            menus.main_menu();
            
        }
        else if (input == "2") {
            menus.find_menu();
            menus.main_menu();
        }
        else if (input == "3") {
            menus.delete_menu();
            menus.main_menu();
        }
        else if (input == "4") {
            menus.list_menu();
            menus.main_menu();
        }

        else if (input == "5") {
            exit(EXIT_SUCCESS);
        }
        else {
            cout << "Please enter a valid number: ";
        }
        
    }
}