#include "menu.h"
#include "record.h"
#include "database.h"
#include <iostream>
#include <string>
#include <limits>
#include <iomanip>

using namespace std;

Menu:: Menu()
: WIDTH(30), database("database.txt")
{}

void Menu::main_menu()
{
    cout << "\nWelcome to the Video Game Database\n";
    cout << "----------------------------------\n\n";
    cout << "(1) Add a game\n";
    cout << "(2) Find games\n";
    cout << "(3) Delete games\n";
    cout << "(4) List all games\n";
    cout << "(5) Quit\n\n";
    cout << "Enter the number of your choice: ";

}

void Menu::add_menu()
{
    cout << "\nAdd a Video Game\n";
    cout << "----------------\n\n";
    cout << "(1) Proceed\n";
    cout << "(2) Go back to main menu\n\n";
    cout << "Enter the number of your choice: ";

    string input = "";
    getline(cin, input);
    while (input != "2") {
        if (input == "1") {

            cout << "Please enter the title of the game: ";
            string title = "";
            getline(cin, title);

            cout << "Please enter the genre of the game: ";
            string genre = "";
            getline(cin, genre);

            cout << "Please enter the creator (or company) of the game: ";
            string creator = "";
            getline(cin, creator);

            cout << "Please enter the year the game was published: ";
            int year_published = 0;
            string year_inputted = "";
            bool invalid_input = true;

            // try catch block that's under a loop. this is done to make sure wrong data types
            // are not given
            while (invalid_input) {
                
                getline(cin, year_inputted);

                try {
                    year_published = stoi(year_inputted);
                    while (year_published < 0 || year_published > 2021) { // redo for current year
                        cout << "Please enter a valid year for the year published: ";
                        getline(cin, year_inputted);
                        year_published = stoi(year_inputted);
                    }
                    invalid_input = false;
                }
                catch (...) {
                    cout << "Please enter a valid year for the year published: ";
                }   
            }

            cout << "Please enter the metacritic score of the game (put 0 if none): ";
            double metacritic_score = 0;
            while (!(cin >> metacritic_score) || metacritic_score < 0 || metacritic_score > 100) { 
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Please enter a valid metacritic score: ";
            }

            
        

            Video_Game new_record(title, genre, creator, year_published, metacritic_score);
            bool is_duplicate = false;

            cout << database.get_all_records().size();
            for (int i = 0; i < database.get_all_records().size(); i++) {
                if (database.get_all_records().at(i) == new_record) {
                    is_duplicate = true;
                }
            }
            
            if (is_duplicate) {
                cout << "\nThe game you're trying to add is already in the database!\n\n";
            }
            else {
                database.add_record(new_record);
                cout << "\nThe game has now been added!\n\n";
            }
            cin.ignore(); // needed so future getline() calls are not skipped
            break;
        }
        else {
            cout << "Please type a valid number: ";
            getline(cin, input);
        }
        
    }
}


void Menu::display_game(Video_Game game) {

    cout << setw(WIDTH+10) << game.get_title() << setw(WIDTH) << game.get_genre() << setw(WIDTH)
        << game.get_creator() << setw(WIDTH) << game.get_year_published() 
        << setw(WIDTH) << game.get_metacritic_score() << "\n";
}

void Menu::display_games(vector<Video_Game> games) {

    cout << setw(WIDTH+10) << "TITLE" << setw(WIDTH) << "GENRE" << setw(WIDTH)
        << "CREATOR" << setw(WIDTH) << "YEAR" 
        << setw(WIDTH) << "METACRITIC"
        << "\n";

    cout << setw(WIDTH+10) << "-----" << setw(WIDTH) << "-----" << setw(WIDTH)
        << "-------" << setw(WIDTH) << "----" 
        << setw(WIDTH) << "----------"
        << "\n\n";

    for (Video_Game game : games) {
        display_game(game);
    }

    cout << "\n";
}

void Menu::find_menu()
{
    // loop so user can return to this if they decide to go back from tbhe sub menus
    while (true) {
        cout << "\nFind a Video Game\n";
        cout << "-----------------\n\n";
        cout << "(1) Find by title\n";
        cout << "(2) Find by genre\n";
        cout << "(3) Find by creator\n";
        cout << "(4) Find by year published\n";
        cout << "(5) Find by Metacritic score\n";
        cout << "(6) Go back to the main menu\n\n";
        cout << "Enter the number of your choice: ";    
        string input = "";
        getline(cin, input);

        while (input != "6") {


            if (input == "1") {
                find_by_title();
                break;
            }
            else if (input == "2") {
                find_by_genre();
                break;
            }
            else if (input == "3") {
                find_by_creator();
                break;
            }
            else if (input == "4") {
                find_by_year_published();
                break;
            }
            else if (input == "5") {
                find_by_metacritic_score();
                break;
            }
            else {
                cout << "Please enter a valid number: ";
                getline(cin, input);
            }   
        }
        // since every input from 1 -5 has a break, they will go here
        // since they don't equal six, they will go back to the find menu loop
        // if input == 6, loop will be exited and will head back to the main menu
        if (input == "6") {
            break;
        }
        
    }
}

void Menu::find_by_title()
{
    cout << "\nFind by Title\n";
    cout << "-------------\n\n";
    cout << "(1) Find all by exact string\n";
    cout << "(2) Find all by substring\n";
    cout << "(3) Go back\n\n";
    cout << "Enter the number of your choice: ";

    string input  = "";
    getline(cin, input);

    while (input != "3") {

        if (input == "1" || input == "2") {

            string title = "";
            cout << "Enter title: ";
            getline(cin, title);
            cout << "\n";

            vector<Video_Game> games_found = database.find_by_title(input, title);

            if (games_found.size() == 0) {
                cout << "No games matched your title.\n\n";
            }
            else {
                display_games(games_found);
            }
            break;
        }
    
        else {
            cout << "Please enter a valid number: ";
            getline(cin, input);
        }
    }
}

void Menu::find_by_genre()
{
    cout << "\nFind by Genre\n";
    cout << "-------------\n\n";
    cout << "(1) Find all by exact string\n";
    cout << "(2) Find all by substring\n";
    cout << "(3) Go back\n\n";
    cout << "Enter the number of your choice: ";

    string input  = "";
    getline(cin, input);

    while (input != "3") {

        if (input == "1" || input == "2") {

            string genre = "";
            cout << "Enter genre: ";
            getline(cin, genre);
            cout << "\n";

            vector<Video_Game> games_found = database.find_by_genre(input, genre);

            if (games_found.size() == 0) {
                cout << "No games matched the genre.\n\n";
            }
            else {
                display_games(games_found);
            }
            break;
        }
    
        else {
            cout << "Please enter a valid number: ";
            getline(cin, input);
        }
    }
}

void Menu::find_by_creator()
{
    cout << "\nFind by Creator\n";
    cout << "-------------\n\n";
    cout << "(1) Find all by exact string\n";
    cout << "(2) Find all by substring\n";
    cout << "(3) Go back\n\n";
    cout << "Enter the number of your choice: ";

    
    string input  = "";
    getline(cin, input);

    while (input != "3") {

        if (input == "1" || input == "2") {

            string creator = "";
            cout << "Enter creator: ";
            getline(cin, creator);
            cout << "\n";

            vector<Video_Game> games_found = database.find_by_creator(input, creator);

            if (games_found.size() == 0) {
                cout << "No games matched with the creator.\n\n";
            }
            else {
                display_games(games_found);
            }
            break;
        }
    
        else {
            cout << "Please enter a valid number: ";
            getline(cin, input);
        }
    }
}

void Menu::find_by_year_published()
{
    cout << "\nFind by Year published\n";
    cout << "-------------\n\n";
    cout << "(1) Find all by exact year\n";
    cout << "(2) Find all by range of years\n";
    cout << "(3) Go back\n\n";
    cout << "Enter the number of your choice: ";

    string input  = "";
    getline(cin, input);

    while (input != "3") {

        if (input == "1") {

            cout << "Please enter the year the game was published: ";
            int year_published = 0;
            string year_inputted = "";
            bool invalid_input = true;

            // try catch block that's under a loop. this is done to make sure wrong data types
            // are not given
            while (invalid_input) {
                
                getline(cin, year_inputted);

                try {
                    year_published = stoi(year_inputted);
                    while (year_published < 0 || year_published > 2021) { // redo for current year
                        cout << "Please enter a valid year for the year published: ";
                        getline(cin, year_inputted);
                        year_published = stoi(year_inputted);
                    }
                    invalid_input = false;
                }
                catch (...) {
                    cout << "Please enter a valid year for the year published: ";
                }   
            }
            cout << "\n";

            vector<Video_Game> games_found = database.find_by_year_published
            (year_published, year_published);

            if (games_found.size() == 0) {
                cout << "No games matched the year given.\n\n";
            }
            else {
                display_games(games_found);
            }

            break;
        }

        else if (input == "2") {

            cout << "Please enter the year you want to start the search: ";
            int starting_year = 0;
            string starting_year_inputted = "";
            bool invalid_input = true;

            while (invalid_input) {
                
                getline(cin, starting_year_inputted);

                try {
                    starting_year = stoi(starting_year_inputted);
                    while (starting_year < 0 || starting_year > 2021) { // redo for current year
                        cout << "Please enter a valid year for the year published: ";
                        getline(cin, starting_year_inputted);
                        starting_year = stoi(starting_year_inputted);        
                    }

                    invalid_input = false;
                }
                catch (...) {
                    cout << "Please enter a valid year for the year published: ";
                }   
            }
            
            cout << "Please enter the year you want to end the search: ";
            int ending_year = 0;
            string ending_year_inputted = "";
            invalid_input = true;

            while (invalid_input) {
                
                getline(cin, ending_year_inputted);

                try {
                    ending_year = stoi(ending_year_inputted);
                    while (ending_year < 0 || ending_year > 2021) { // redo for current year
                        cout << "Please enter a valid year for the year published: ";
                        getline(cin, ending_year_inputted);
                        ending_year = stoi(ending_year_inputted);        
                    }

                    invalid_input = false;
                }
                catch (...) {
                    cout << "Please enter a valid year for the year published: ";
                }   
            }

            cout << "\n";

            vector<Video_Game> games_found = database.find_by_year_published(starting_year, ending_year );

            if (games_found.size() == 0) {
                cout << "No games matched the year given.\n\n";
            }
            else {
                display_games(games_found);
            }
        
            break;
        }
    
        else {
            cout << "Please enter a valid number: ";
            getline(cin, input);
        }
    }
}

void Menu::find_by_metacritic_score()
{
    cout << "\nFind by Metacritic Score\n";
    cout << "-------------\n\n";
    cout << "(1) Find all by exact score\n";
    cout << "(2) Find all within a range of scores\n";
    cout << "(3) Go back\n\n";
    cout << "Enter the number of your choice: ";

    string input  = "";
    getline(cin, input);

    while (input != "3") {

        if (input == "1") {

            cout << "Please enter the Metacritic score of the game: ";
            double metacritic_score = 0;
            string score_inputted = "";
            bool invalid_input = true;

            // try catch block that's under a loop. this is done to make sure wrong data types
            // are not given
            while (invalid_input) {
                
                getline(cin, score_inputted);

                try {
                    metacritic_score = stod(score_inputted);
                    while (metacritic_score < 0 || metacritic_score > 100) { 
                        cout << "Please enter a valid score: ";
                        getline(cin, score_inputted);
                        metacritic_score = stoi(score_inputted);
                    }
                    invalid_input = false;
                }
                catch (...) {
                    cout << "Please enter a valid score: ";
                }   
            }
            cout << "\n";

            vector<Video_Game> games_found = database.find_by_metacritic_score(
                metacritic_score , metacritic_score);

            if (games_found.size() == 0) {
                cout << "No games matched the score given.\n\n";
            }
            else {
                display_games(games_found);
            }

            break;
        }

        else if (input == "2") {

            cout << "Please enter the minimum score: ";
            double initial_score = 0;
            string initial_score_inputted = "";
            bool invalid_input = true;

            // try catch block that's under a loop. this is done to make sure wrong data types
            // are not given
            while (invalid_input) {
                
                getline(cin, initial_score_inputted);

                try {
                    initial_score = stod(initial_score_inputted);
                    while (initial_score < 0 || initial_score > 100) { 
                        cout << "Please enter a valid score: ";
                        getline(cin, initial_score_inputted);
                        initial_score = stoi(initial_score_inputted);
                    }
                    invalid_input = false;
                }
                catch (...) {
                    cout << "Please enter a valid score: ";
                }   
            }

            cout << "Please enter the maximum score: ";
            double maximum_score = 0;
            string max_score_inputted = "";
            invalid_input = true;

            // try catch block that's under a loop. this is done to make sure wrong data types
            // are not given
            while (invalid_input) {
                
                getline(cin, max_score_inputted);

                try {
                    maximum_score = stod(max_score_inputted);
                    while (maximum_score < 0 || maximum_score > 100) { 
                        cout << "Please enter a valid score: ";
                        getline(cin, max_score_inputted);
                        maximum_score = stoi(max_score_inputted);
                    }
                    invalid_input = false;
                }
                catch (...) {
                    cout << "Please enter a valid score: ";
                }   
            }
            cout << "\n";

            vector<Video_Game> games_found = database.find_by_metacritic_score(
                initial_score, maximum_score);

            if (games_found.size() == 0) {
                cout << "No games matched the score given.\n\n";
            }
            else {
                display_games(games_found);
            }
           
            break;
        }
    
        else {
            cout << "Please enter a valid number: ";
            getline(cin, input);
        }
    }
}

void Menu::delete_menu()
{
    while (true) {
        cout << "\nDelete Video Games\n";
        cout << "-----------------\n\n";
        cout << "(1) Delete by title\n";
        cout << "(2) Delete by genre\n";
        cout << "(3) Delete by creator\n";
        cout << "(4) Delete by year published\n";
        cout << "(5) Delete by Metacritic score\n";
        cout << "(6) Go back to the main menu\n\n";
        cout << "Enter the number of your choice: ";    
        string input = "";
        getline(cin, input);

        while (input != "6") {


            if (input == "1") {
                delete_by_title();
                break;
            }
            else if (input == "2") {
                delete_by_genre();
                break;
            }
            else if (input == "3") {
                delete_by_creator();
                break;
            }
            else if (input == "4") {
                delete_by_year_published();
                break;
            }
            else if (input == "5") {
                delete_by_metacritic_score();
                break;
            }
            else {
                cout << "Please enter a valid number: ";
                getline(cin, input);
            }   
        }
        // since every input from 1 -5 has a break, they will go here
        // since they don't equal six, they will go back to the delete menu loop
        // if input == 6, loop will be exited and will head back to the main menu
        if (input == "6") {
            break;
        }
        
    }
}

void Menu::delete_by_title()
{
    cout << "\n\nDelete by Title\n";
    cout << "-------------\n\n";
    cout << "(1) Delete all by exact string\n";
    cout << "(2) Delete all by substring\n";
    cout << "(3) Go back\n\n";
    cout << "Enter the number of your choice: ";

    string input  = "";
    getline(cin, input);

    while (input != "3") {

        if (input == "1" || input == "2") {

            string title = "";
            cout << "Enter title: ";
            getline(cin, title);
            cout << "\n";

            vector<Video_Game> games_found = database.find_by_title(input, title);

            if (games_found.size() == 0) {
                cout << "No games matched your title.\n\n";
            }

            else {

                display_games(games_found);
                cout <<"\n(1) Delete these games\n";
                cout <<"(2) Cancel\n\n";
                cout << "Enter the number of your choice: ";

                string more_input = "";
                getline(cin, more_input);
                while (more_input != "2") {
                    if (more_input == "1") {
                        database.delete_list_of_records(games_found);
                        cout << "\nSelected games have been deleted.\n\n";
                        break;
                    }
                    else {
                        cout << "Please enter a valid number: ";
                        getline(cin, more_input);
                    }
                }
            }

            break;
        }

        else {
            cout << "Please enter a valid number: ";
            getline(cin, input);
        }
    }
}

void Menu::delete_by_genre()
{
    cout << "\n\nDelete by Genre\n";
    cout << "-------------\n\n";
    cout << "(1) Delete all by exact string\n";
    cout << "(2) Delete all by substring\n";
    cout << "(3) Go back\n\n";
    cout << "Enter the number of your choice: ";

    string input  = "";
    getline(cin, input);

    while (input != "3") {

        if (input == "1" || input == "2") {

            string genre = "";
            cout << "Enter genre: ";
            getline(cin, genre);
            cout << "\n";

            vector<Video_Game> games_found = database.find_by_genre(input, genre);

            if (games_found.size() == 0) {
                cout << "No games matched your genre.\n\n";
            }

            else {

                display_games(games_found);
                cout <<"\n(1) Delete these games\n";
                cout <<"(2) Cancel\n\n";
                cout << "Enter the number of your choice: ";

                string more_input = "";
                getline(cin, more_input);
                while (more_input != "2") {
                    if (more_input == "1") {
                        database.delete_list_of_records(games_found);
                        cout << "\nSelected games have been deleted.\n\n";
                        break;
                    }
                    else {
                        cout << "Please enter a valid number: ";
                        getline(cin, more_input);
                    }
                }
            }

            break;
        }

        else {
            cout << "Please enter a valid number: ";
            getline(cin, input);
        }
    }
}

void Menu::delete_by_creator()
{
    cout << "\n\nDelete by Creator\n";
    cout << "-------------\n\n";
    cout << "(1) Delete all by exact string\n";
    cout << "(2) Delete all by substring\n";
    cout << "(3) Go back\n\n";
    cout << "Enter the number of your choice: ";

    string input  = "";
    getline(cin, input);

    while (input != "3") {

        if (input == "1" || input == "2") {

            string creator = "";
            cout << "Enter creator: ";
            getline(cin, creator);
            cout << "\n";

            vector<Video_Game> games_found = database.find_by_creator(input, creator);

            if (games_found.size() == 0) {
                cout << "No games matched your creator.\n\n";
            }

            else {

                display_games(games_found);
                cout <<"\n(1) Delete these games\n";
                cout <<"(2) Cancel\n\n";
                cout << "Enter the number of your choice: ";

                string more_input = "";
                getline(cin, more_input);
                while (more_input != "2") {
                    if (more_input == "1") {
                        database.delete_list_of_records(games_found);
                        cout << "\nSelected games have been deleted.\n\n";
                        break;
                    }
                    else {
                        cout << "Please enter a valid number: ";
                        getline(cin, more_input);
                    }
                }
            }

            break;
        }

        else {
            cout << "Please enter a valid number: ";
            getline(cin, input);
        }
    }
}

void Menu::delete_by_year_published()
{
    cout << "\n\nnDelete by Year Published\n";
    cout << "------------------------\n\n";
    cout << "(1) Delete all by exact year\n";
    cout << "(2) Delete all by range of years\n";
    cout << "(3) Go back\n\n";
    cout << "Enter the number of your choice: ";

    string input  = "";
    getline(cin, input);

    while (input != "3") {

        if (input == "1") {

            cout << "Please enter the year the game was published: ";
            int year_published = 0;
            string year_inputted = "";
            bool invalid_input = true;

            // try catch block that's under a loop. this is done to make sure wrong data types
            // are not given
            while (invalid_input) {
                
                getline(cin, year_inputted);

                try {
                    year_published = stoi(year_inputted);
                    while (year_published < 0 || year_published > 2021) { // redo for current year
                        cout << "Please enter a valid year for the year published: ";
                        getline(cin, year_inputted);
                        year_published = stoi(year_inputted);
                    }
                    invalid_input = false;
                }
                catch (...) {
                    cout << "Please enter a valid year for the year published: ";
                }   
            }
            cout << "\n";

            vector<Video_Game> games_found = database.find_by_year_published(
                year_published, year_published);

            if (games_found.size() == 0) {
                cout << "No games matched the year given.\n\n";
            }
            else {
                display_games(games_found);
                cout <<"\n(1) Delete these games\n";
                cout <<"(2) Cancel\n\n";
                cout << "Enter the number of your choice: ";

                string more_input = "";
                getline(cin, more_input);
                while (more_input != "2") {
                    if (more_input == "1") {
                        database.delete_list_of_records(games_found);
                        cout << "\nSelected games have been deleted.\n\n";
                        break;
                    }
                    else {
                        cout << "Please enter a valid number: ";
                        getline(cin, more_input);
                    }
                }
            }

            break;
        }

        else if (input == "2") {

            cout << "Please enter the year you want to start the search: ";
            int starting_year = 0;
            string starting_year_inputted = "";
            bool invalid_input = true;

            while (invalid_input) {
                
                getline(cin, starting_year_inputted);

                try {
                    starting_year = stoi(starting_year_inputted);
                    while (starting_year < 0 || starting_year > 2021) { // redo for current year
                        cout << "Please enter a valid year for the year published: ";
                        getline(cin, starting_year_inputted);
                        starting_year = stoi(starting_year_inputted);        
                    }

                    invalid_input = false;
                }
                catch (...) {
                    cout << "Please enter a valid year for the year published: ";
                }   
            }
            
            cout << "Please enter the year you want to end the search: ";
            int ending_year = 0;
            string ending_year_inputted = "";
            invalid_input = true;

            while (invalid_input) {
                
                getline(cin, ending_year_inputted);

                try {
                    ending_year = stoi(ending_year_inputted);
                    while (ending_year < 0 || ending_year > 2021) { // redo for current year
                        cout << "Please enter a valid year for the year published: ";
                        getline(cin, ending_year_inputted);
                        ending_year = stoi(ending_year_inputted);        
                    }

                    invalid_input = false;
                }
                catch (...) {
                    cout << "Please enter a valid year for the year published: ";
                }   
            }

            cout << "\n";

            vector<Video_Game> games_found = database.find_by_year_published(starting_year, ending_year );

            if (games_found.size() == 0) {
                cout << "No games matched the year given.\n\n";
            }
            else {
                display_games(games_found);
                cout <<"\n(1) Delete these games\n";
                cout <<"(2) Cancel\n\n";
                cout << "Enter the number of your choice: ";

                string more_input = "";
                getline(cin, more_input);
                while (more_input != "2") {
                    if (more_input == "1") {
                        database.delete_list_of_records(games_found);
                        cout << "\nSelected games have been deleted.\n\n";
                        break;
                    }
                    else {
                        cout << "Please enter a valid number: ";
                        getline(cin, more_input);
                    }
                }
            }
        
            break;
        }
    
        else {
            cout << "Please enter a valid number: ";
            getline(cin, input);
        }
    }
}

void Menu::delete_by_metacritic_score()
{
    cout << "\nDelete by Metacritic Score\n";
    cout << "--------------------------\n\n";
    cout << "(1) Delete all by exact score\n";
    cout << "(2) Delete all by range of scores\n";
    cout << "(3) Go back\n\n";
    cout << "Enter the number of your choice: ";

    string input  = "";
    getline(cin, input);

    while (input != "3") {

        if (input == "1") {

            cout << "Please enter the Metacritic score of the game: ";
            double metacritic_score = 0;
            string score_inputted = "";
            bool invalid_input = true;

            // try catch block that's under a loop. this is done to make sure wrong data types
            // are not given
            while (invalid_input) {
                
                getline(cin, score_inputted);

                try {
                    metacritic_score = stod(score_inputted);
                    while (metacritic_score < 0 || metacritic_score > 100) { 
                        cout << "Please enter a valid score: ";
                        getline(cin, score_inputted);
                        metacritic_score = stoi(score_inputted);
                    }
                    invalid_input = false;
                }
                catch (...) {
                    cout << "Please enter a valid score: ";
                }   
            }
            cout << "\n";

            vector<Video_Game> games_found = database.find_by_metacritic_score(
                metacritic_score , metacritic_score);

            if (games_found.size() == 0) {
                cout << "No games matched the score given.\n\n";
            }
            else {
                display_games(games_found);
                cout <<"\n(1) Delete these games\n";
                cout <<"(2) Cancel\n\n";
                cout << "Enter the number of your choice: ";

                string more_input = "";
                getline(cin, more_input);
                while (more_input != "2") {
                    if (more_input == "1") {
                        database.delete_list_of_records(games_found);
                        cout << "\nSelected games have been deleted.\n\n";
                        break;
                    }
                    else {
                        cout << "Please enter a valid number: ";
                        getline(cin, more_input);
                    }
                }
            }

            break;
        }

        else if (input == "2") {

            cout << "Please enter the minimum score: ";
            double initial_score = 0;
            string initial_score_inputted = "";
            bool invalid_input = true;

            // try catch block that's under a loop. this is done to make sure wrong data types
            // are not given
            while (invalid_input) {
                
                getline(cin, initial_score_inputted);

                try {
                    initial_score = stod(initial_score_inputted);
                    while (initial_score < 0 || initial_score > 100) { 
                        cout << "Please enter a valid score: ";
                        getline(cin, initial_score_inputted);
                        initial_score = stoi(initial_score_inputted);
                    }
                    invalid_input = false;
                }
                catch (...) {
                    cout << "Please enter a valid score: ";
                }   
            }

            cout << "Please enter the maximum score: ";
            double maximum_score = 0;
            string max_score_inputted = "";
            invalid_input = true;

            // try catch block that's under a loop. this is done to make sure wrong data types
            // are not given
            while (invalid_input) {
                
                getline(cin, max_score_inputted);

                try {
                    maximum_score = stod(max_score_inputted);
                    while (maximum_score < 0 || maximum_score > 100) { 
                        cout << "Please enter a valid score: ";
                        getline(cin, max_score_inputted);
                        maximum_score = stoi(max_score_inputted);
                    }
                    invalid_input = false;
                }
                catch (...) {
                    cout << "Please enter a valid score: ";
                }   
            }
            cout << "\n";

            vector<Video_Game> games_found = database.find_by_metacritic_score(
                initial_score, maximum_score);

            if (games_found.size() == 0) {
                cout << "No games matched the score given.\n\n";
            }
            else {
                display_games(games_found);
                cout <<"\n(1) Delete these games\n";
                cout <<"(2) Cancel\n\n";
                cout << "Enter the number of your choice: ";

                string more_input = "";
                getline(cin, more_input);
                while (more_input != "2") {
                    if (more_input == "1") {
                        database.delete_list_of_records(games_found);
                        cout << "\nSelected games have been deleted.\n\n";
                        break;
                    }
                    else {
                        cout << "Please enter a valid number: ";
                        getline(cin, more_input);
                    }
                }
            }
           
            break;
        }
    
        else {
            cout << "Please enter a valid number: ";
            getline(cin, input);
        }
    }
}


void Menu::list_menu() 
{
    while (true) {
        cout << "\nList Video Games\n";
        cout << "-----------------\n\n";
        cout << "(1) List by title\n";
        cout << "(2) List by genre\n";
        cout << "(3) List by creator\n";
        cout << "(4) List by year published\n";
        cout << "(5) List by Metacritic score\n";
        cout << "(6) Go back to the main menu\n\n";
        cout << "Enter the number of your choice: ";    
        string input = "";
        getline(cin, input);

        while (input != "6") {


            if (input == "1") {
                list_by_title();
                break;
            }
            else if (input == "2") {
                list_by_genre();
                break;
            }
            else if (input == "3") {
                list_by_creator();
                break;
            }
            else if (input == "4") {
                list_by_year_published();
                break;
            }
            else if (input == "5") {
                list_by_metacritic_score();
                break;
            }
            else {
                cout << "Please enter a valid number: ";
                getline(cin, input);
            }   
        }
        // since every input from 1 -5 has a break, they will go here
        // since they don't equal six, they will go back to the delete menu loop
        // if input == 6, loop will be exited and will head back to the main menu
        if (input == "6") {
            break;
        }
        
    }
}

void Menu::list_by_title()
{
    cout << "\nList by Title\n";
    cout << "-------------\n\n";
    cout << "(1) List all in alphabetical order\n";
    cout << "(2) List all by reverse alphabetical order\n";
    cout << "(3) Go back\n\n";
    cout << "Enter the number of your choice: ";

    string input  = "";
    getline(cin, input);

    while (input != "3") {

        if (input == "1" || input == "2") {

            vector<Video_Game> games_found = database.list_by_title(input);

            if (games_found.size() == 0) {
                cout << "No games in the database currently.\n\n";
            }
            else {
                display_games(games_found);
            }
            break;
        }
    
        else {
            cout << "Please enter a valid number: ";
            getline(cin, input);
        }
    }
}

void Menu::list_by_genre()
{
    cout << "\nList by Genre\n";
    cout << "-------------\n\n";
    cout << "(1) List all in alphabetical order\n";
    cout << "(2) List all by reverse alphabetical order\n";
    cout << "(3) Go back\n\n";
    cout << "Enter the number of your choice: ";

    string input  = "";
    getline(cin, input);

    while (input != "3") {

        if (input == "1" || input == "2") {

            vector<Video_Game> games_found = database.list_by_genre(input);

            if (games_found.size() == 0) {
                cout << "No games in the database currently.\n\n";
            }
            else {
                display_games(games_found);
            }
            break;
        }
    
        else {
            cout << "Please enter a valid number: ";
            getline(cin, input);
        }
    }
}

void Menu::list_by_creator()
{
    cout << "\nList by Creator\n";
    cout << "-------------\n\n";
    cout << "(1) List all in alphabetical order\n";
    cout << "(2) List all by reverse alphabetical order\n";
    cout << "(3) Go back\n\n";
    cout << "Enter the number of your choice: ";

    string input  = "";
    getline(cin, input);

    while (input != "3") {

        if (input == "1" || input == "2") {

            vector<Video_Game> games_found = database.list_by_creator(input);

            if (games_found.size() == 0) {
                cout << "No games in the database currently.\n\n";
            }
            else {
                display_games(games_found);
            }
            break;
        }
    
        else {
            cout << "Please enter a valid number: ";
            getline(cin, input);
        }
    }
}

void Menu::list_by_year_published()
{
    cout << "\nList by Year Published\n";
    cout << "-------------\n\n";
    cout << "(1) List all in ascending order\n";
    cout << "(2) List all by descending order\n";
    cout << "(3) Go back\n\n";
    cout << "Enter the number of your choice: ";

    string input  = "";
    getline(cin, input);

    while (input != "3") {

        if (input == "1" || input == "2") {

            vector<Video_Game> games_found = database.list_by_year_published(input);

            if (games_found.size() == 0) {
                cout << "No games in the database currently.\n\n";
            }
            else {
                display_games(games_found);
            }
            break;
        }
    
        else {
            cout << "Please enter a valid number: ";
            getline(cin, input);
        }
    }
}

void Menu::list_by_metacritic_score()
{
    cout << "\nList by Metacritic Score\n";
    cout << "-------------\n\n";
    cout << "(1) List all in ascending order\n";
    cout << "(2) List all by descending order\n";
    cout << "(3) Go back\n\n";
    cout << "Enter the number of your choice: ";

    string input  = "";
    getline(cin, input);

    while (input != "3") {

        if (input == "1" || input == "2") {

            vector<Video_Game> games_found = database.list_by_metacritic_score(input);

            if (games_found.size() == 0) {
                cout << "No games in the database currently.\n\n";
            }
            else {
                display_games(games_found);
            }
            break;
        }
    
        else {
            cout << "Please enter a valid number: ";
            getline(cin, input);
        }
    }
}