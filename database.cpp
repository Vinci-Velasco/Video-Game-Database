#include "database.h"
#include "record.h"
#include "cmpt_error.h"
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;


Database::Database(string filename)
{
    file = filename;
    ifstream database_file(file);
    if (! database_file) {
        cmpt::error("Cannot open " + file);
    }

    string line_from_file = "";
    while (getline(database_file, line_from_file)) {
        
        string title = "";
        string genre = "";
        string creator = "";
        int year_published = 0;
        double metacritic_score = 0;

        string field = "";
        int counter = 0;
        int END_OF_LINE = line_from_file.size()-1;

        // seperates each part of the line (seperated by comma) to it's corresponding field
        // 1st field is always title, 2nd is genre etc..
        // hence the use of the counter variable and a switch statement
        for (int i = 0; i < line_from_file.size(); i++) {

            if (line_from_file.at(i) == ',' || i == END_OF_LINE) {
                if (i == END_OF_LINE) {
                    field.push_back(line_from_file.at(i));
                }
                // the value of counter determines which field it belongs to
                switch(counter) {
                    case 0:
                        convert_special_chars(field);
                        title = field;
                        field = "";
                        break;
                    case 1:
                        convert_special_chars(field);
                        genre = field;
                        field = "";
                        break;
                    case 2:
                        convert_special_chars(field);
                        creator = field;
                        field = "";
                        break;
                    case 3:
                        year_published = stoi(field);
                        field = "";
                        break;
                    case 4:
                        metacritic_score = stod(field);
                        field = "";
                        break;
                }
                counter++;
            }
            else {
                field.push_back(line_from_file.at(i));
            }
        }

        Video_Game record(title, genre, creator, year_published, metacritic_score);
        all_records.push_back(record);
    }
}

void Database::update_database_file() 
{
    ofstream database_file;
    database_file.open(file);
    if (! database_file) {
        cmpt::error("Cannot open " + file);
    }

    for (int i = 0; i < all_records.size(); i++) {

        Video_Game record = all_records.at(i);
        string title = record.get_title();
        string genre = record.get_genre();
        string creator = record.get_creator();
        int year_published = record.get_year_published();
        double metacritic_score = record.get_metacritic_score();
        convert_commas(title);

        // no new line for last record
        if (i == all_records.size()-1) {
            database_file << title + "," + genre + "," + creator + "," + 
                      to_string(year_published) + "," + to_string(metacritic_score);
        }
        else {
            database_file << title + "," + genre + "," + creator + "," + 
                      to_string(year_published) + "," + to_string(metacritic_score) + "\n";
        }
    }
    database_file.close();
}

/*
since each field is seperated by commas in the text file, this function
converts any commas of a field to a special string of characters
so the commas won't distrupt the text file structure
*/
void Database::convert_commas(string& s)
{
    string convert_to = "***";

    for (int i = 0; i < s.size(); i++) {
        if (s.at(i) == ',') {
            s.replace(i, 1, convert_to);
        }
    }
}

// converts the special chars back to commas when reading from the text file'
void Database::convert_special_chars(string& s)
{
    char special_char = '*';
    int special_char_length = 3;
    string convert_to = ",";

    for (int i = 0; i < s.size(); i++) {
        if (s.at(i) == special_char && s.at(i+1) == special_char && s.at(i+2) == special_char) {
            s.replace(i, special_char_length, convert_to);
        }
    }
}

void Database::add_record(Video_Game v)
{
    all_records.push_back(v);
    update_database_file();
}

vector<Video_Game> Database::get_all_records() const 
{
    return all_records;
}


string convert_to_lower_case(string s)
{
    string converted = "";
    for (char letter : s) {
        converted.push_back(tolower(letter));
    }
    return converted;
}


// find methods :
// they return empty vector if nothing is found

vector<Video_Game> Database::find_by_title(string string_or_substring, string title) const
{   
    vector<Video_Game> matches;
    if (string_or_substring == "1") {
        for (int i = 0; i < all_records.size(); i++) {
            string other_title = convert_to_lower_case(all_records.at(i).get_title());
            if (other_title == convert_to_lower_case(title)) {
                matches.push_back(all_records.at(i));
            }
        }
    }

    else if (string_or_substring == "2") {
        for (int i = 0; i < all_records.size(); i++) {
            // checks if argument title appears as a substring in the title of each record
            string other_title = convert_to_lower_case(all_records.at(i).get_title());
            size_t found = other_title.find(convert_to_lower_case(title));
            if (found != string::npos) {
                matches.push_back(all_records.at(i));
            }
        }
        
    }
    return matches;
}

vector<Video_Game> Database::find_by_genre(string string_or_substring, string genre) const
{
    vector<Video_Game> matches;

    if (string_or_substring == "1") {
        for (int i = 0; i < all_records.size(); i++) {
            string other_genre = convert_to_lower_case(all_records.at(i).get_genre());
            if (other_genre == convert_to_lower_case(genre)) {
                matches.push_back(all_records.at(i));
            }
        }
    }

    else if (string_or_substring == "2") {
        for (int i = 0; i < all_records.size(); i++) {
            // checks if argument genre appears as a substring in the title of each record
            string other_genre = convert_to_lower_case(all_records.at(i).get_genre());
            size_t found = other_genre.find(convert_to_lower_case(genre));
            if (found != string::npos) {
                matches.push_back(all_records.at(i));
            }
        }
        
    }
    return matches;
}

vector<Video_Game> Database::find_by_creator(string string_or_substring, string creator) const
{
    vector<Video_Game> matches;
    if (string_or_substring == "1") {
        for (int i = 0; i < all_records.size(); i++) {
            string other_creator = convert_to_lower_case(all_records.at(i).get_creator());
            if (other_creator == convert_to_lower_case(creator)) {
                matches.push_back(all_records.at(i));
            }
        }
    }

    else if (string_or_substring == "2") {
        for (int i = 0; i < all_records.size(); i++) {
            // checks if argument creator appears as a substring in the title of each record
            string other_creator = convert_to_lower_case(all_records.at(i).get_creator());
            size_t found = other_creator.find(convert_to_lower_case(creator));
            if (found != string::npos) {
                matches.push_back(all_records.at(i));
            }
        }
        
    }
    return matches;
}

// starting year and ending year would be the same if user didn't choose search by range
vector<Video_Game> Database::find_by_year_published(int starting_year, int ending_year) const
{   
    vector<Video_Game> matches;
    for (int i = starting_year; i <= ending_year; i++) {
        for (int j = 0; j < all_records.size(); j++) {
            if (all_records.at(j).get_year_published() == i) {
                matches.push_back(all_records.at(j));
            }
        }
    }
    return matches;
}

vector<Video_Game> Database::find_by_metacritic_score(
    double starting_score, double ending_score) const
{
    vector<Video_Game> matches;
    for (int i = 0; i < all_records.size(); i++) {
        if (all_records.at(i).get_metacritic_score() >= starting_score 
            && all_records.at(i).get_metacritic_score() <= ending_score) {
                matches.push_back(all_records.at(i));
            }
    }
    return matches;
}


// delete methods

void Database::delete_record(Video_Game v)
{
    for (int i = 0; i < all_records.size(); i++) {

        if (all_records.at(i) == v) {
            all_records.erase(all_records.begin()+i);
            break; // stop the loop to save time
        }
    }

    update_database_file();
}

void Database::delete_list_of_records(const vector<Video_Game>& vec)
{
    for (Video_Game v: vec) {
        for (int i = 0; i < all_records.size(); i++) {

            if (all_records.at(i) == v) {
                all_records.erase(all_records.begin()+i);
                break; // stop the loop to save time
            }
        }
    }
    update_database_file();
}


// list methods

vector<Video_Game> Database::list_by_title (string alpha_or_reverse) const
{   
    vector<Video_Game> sorted_games;
    vector<string> titles;

    for (Video_Game game : all_records) {
        // avoid duplicates
        if (find(titles.begin(), titles.end(), game.get_title()) == titles.end()) {
            titles.push_back(game.get_title());
        }
    }

    if (alpha_or_reverse == "1") {
        sort(titles.begin(), titles.end());
    }
    else if (alpha_or_reverse == "2") {
        sort(titles.rbegin(), titles.rend());
    }

    for (string title : titles) {
        // loop needed as some games might have the same titles
        for (Video_Game game : find_by_title("1", title)) {
            sorted_games.push_back(game);
        }   
    }

    return sorted_games;
}

vector<Video_Game> Database::list_by_genre (string alpha_or_reverse) const
{   
    vector<Video_Game> sorted_games;
    vector<string> genres;

    for (Video_Game game : all_records) {
        // avoid duplicates
        if (find(genres.begin(), genres.end(), game.get_genre()) == genres.end()) {
            genres.push_back(game.get_genre());
        }
    }

    if (alpha_or_reverse == "1") {
        sort(genres.begin(), genres.end());
    }
    else if (alpha_or_reverse == "2") {
        sort(genres.rbegin(), genres.rend());
    }

    for (string genre : genres) {
        // loop needed as some games might have the same genres
        for (Video_Game game : find_by_genre("1", genre)) {
            sorted_games.push_back(game);
        }   
    }

    return sorted_games;
}

vector<Video_Game> Database::list_by_creator (string alpha_or_reverse) const
{   
    vector<Video_Game> sorted_games;
    vector<string> creators;

    for (Video_Game game : all_records) {
        // avoid duplicates
        if (find(creators.begin(), creators.end(), game.get_creator()) == creators.end()) {
            creators.push_back(game.get_creator());
        }
    }

    if (alpha_or_reverse == "1") {
        sort(creators.begin(), creators.end());
    }
    else if (alpha_or_reverse == "2") {
        sort(creators.rbegin(), creators.rend());
    }

    for (string creator : creators) {
        // loop needed as some games might have the same creators
        for (Video_Game game : find_by_creator("1", creator)) {
            sorted_games.push_back(game);
        }   
    }

    return sorted_games;
}

vector<Video_Game> Database::list_by_year_published (string ascending_or_descending) const
{   
    vector<Video_Game> sorted_games;
    vector<int> years;

    for (Video_Game game : all_records) {
        // avoid duplicates
        if (find(years.begin(), years.end(), game.get_year_published()) == years.end()) {
            years.push_back(game.get_year_published());
        }
    }

    if (ascending_or_descending == "1") {
        sort(years.begin(), years.end());
    }
    else if (ascending_or_descending == "2") {
        sort(years.rbegin(), years.rend());
    }

    for (int year : years) {
        // loop needed as some games might have the same years
        for (Video_Game game : find_by_year_published(year, year)) {
            sorted_games.push_back(game);
        }   
    }

    return sorted_games;
}

vector<Video_Game> Database::list_by_metacritic_score (string ascending_or_descending) const
{   
    vector<Video_Game> sorted_games;
    vector<double> scores;

    for (Video_Game game : all_records) {
        // avoid duplicates
        if (find(scores.begin(), scores.end(), game.get_metacritic_score()) == scores.end()) {
            scores.push_back(game.get_metacritic_score());
        }
    }

    if (ascending_or_descending == "1") {
        sort(scores.begin(), scores.end());
    }
    else if (ascending_or_descending == "2") {
        sort(scores.rbegin(), scores.rend());
    }

    for (double score : scores) {
        // loop needed as some games might have the same years
        for (Video_Game game : find_by_metacritic_score(score, score)) {
            sorted_games.push_back(game);
        }   
    }

    return sorted_games;
}

// test functions for the class Database
// uses test_database.txt so it doesn't affect actual database

void Database_tests() 
{
    constructor_test();
    add_record_test();
    find_by_title_test();
    find_by_genre_test();
    find_by_creator_test();
    find_by_year_published_test();
    find_by_metacritic_score_test();
    delete_record_test();
    delete_list_of_records_test();
    list_by_title_test();
    list_by_genre_test();
    list_by_creator_test();
    list_by_year_published_test();
    list_by_metacritic_score_test();
}

// only works if test_database.txt is empty (which it should be at all times)
void constructor_test() 
{
    Database database("test_database.txt");
    Video_Game game("Spelunky HD", "Roguelite", "Derek Yu", 2013, 90);
    database.add_record(game);

    vector<Video_Game> all_records = database.get_all_records();
    Video_Game record1 = all_records.at(0);
    assert(record1.get_title() == "Spelunky HD");
    assert(record1.get_genre() == "Roguelite");
    assert(record1.get_creator() == "Derek Yu");
    assert(record1.get_year_published() == 2013);
    assert(record1.get_metacritic_score() == 90);

    database.delete_record(record1);
}

void add_record_test()
{
    Database database("test_database.txt");
    int initial_database_size = database.get_all_records().size();

    Video_Game record1("Test title", "Test genre", "Test creator", 1994, 90);
    database.add_record(record1);
    int current_size = database.get_all_records().size();
    assert(current_size - initial_database_size == 1); // size increased by 1

    Video_Game record2("Spelunky", "Roguelite", "Derek Yu", 2008, 90);
    database.add_record(record2);
    current_size = database.get_all_records().size();
    assert(current_size - initial_database_size == 2); // size increased by 2 from original

    database.delete_record(record1);
    database.delete_record(record2);
}

void find_by_title_test()
{
    // search exact
    Database database("test_database.txt");
    Video_Game record1("Test title", "Test genre", "Test creator", 1994, 90);
    database.add_record(record1);
    assert(database.find_by_title("1", "Test title").size() == 1);

    // search by substring
    Video_Game record2("Another Test title", "Test genre", "Test creator", 1994, 90);
    database.add_record(record2);
    assert(database.find_by_title("2", "title").size() == 2);

    database.delete_record(record1);
    database.delete_record(record2);
}

void find_by_genre_test()
{
    // search exact
    Database database("test_database.txt");
    Video_Game record1("Test title", "Test genre", "Test creator", 1994, 90);
    database.add_record(record1);
    assert(database.find_by_genre("1", "Test genre").size() == 1);

    // search by substring
    Video_Game record2("Test title", "Another Test genre", "Test creator", 1994, 90);
    database.add_record(record2);
    assert(database.find_by_genre("2", "genre").size() == 2);

    database.delete_record(record1);
    database.delete_record(record2);
}

void find_by_creator_test()
{
    // search exact
    Database database("test_database.txt");
    Video_Game record1("Test title", "Test genre", "Test creator", 1994, 90);
    database.add_record(record1);
    assert(database.find_by_creator("1", "Test creator").size() == 1);

    // search by substring
    Video_Game record2("Another Test title", "Test genre", "Another Test creator", 1994, 90);
    database.add_record(record2);
    assert(database.find_by_creator("2", "creator").size() == 2);

    database.delete_record(record1);
    database.delete_record(record2);
}

void find_by_year_published_test()
{
    // search exact
    Database database("test_database.txt");
    Video_Game record1("Test title", "Test genre", "Test creator", 1994, 90);
    database.add_record(record1);
    assert(database.find_by_year_published(1994, 1994).size() == 1);

    // search by range
    Video_Game record2("Another Test title", "Test genre", "Test creator", 2002, 90);
    database.add_record(record2);
    assert(database.find_by_year_published(0, 2021).size() == 2);

    database.delete_record(record1);
    database.delete_record(record2);
}

void find_by_metacritic_score_test()
{
    // search exact
    Database database("test_database.txt");
    Video_Game record1("Test title", "Test genre", "Test creator", 1994, 90);
    database.add_record(record1);
    assert(database.find_by_metacritic_score(90, 90).size() == 1);

    // search by range
    Video_Game record2("Another Test title", "Test genre", "Test creator", 1994, 65.2);
    database.add_record(record2);
    assert(database.find_by_metacritic_score(0, 100).size() == 2);

    database.delete_record(record1);
    database.delete_record(record2);
}

void delete_record_test()
{
    Database database("test_database.txt");
    Video_Game record1("Test title", "Test genre", "Test creator", 1994, 90);
    database.add_record(record1);
    database.delete_record(record1);
    assert(database.get_all_records().size() == 0);

    Video_Game record2("Another Test title", "Another Test genre", "creator", 2002, 40);
    database.add_record(record2);
    database.delete_record(record2);
    assert(database.get_all_records().size() == 0);
}

void delete_list_of_records_test()
{
    Database database("test_database.txt");
    Video_Game record1("Test title", "Test genre", "Test creator", 1994, 90);
    database.add_record(record1);
    assert(database.get_all_records().size() == 1);

    Video_Game record2("Another Test title", "Another Test genre", "creator", 2002, 40);
    database.add_record(record2);
    assert(database.get_all_records().size() == 2);

    vector<Video_Game> v = {record1, record2};
    database.delete_list_of_records(v);
    assert(database.get_all_records().size() == 0);
}

void list_by_title_test()
{
    Database database("test_database.txt");
    Video_Game record1("a", "Test genre", "Test creator", 1994, 90);
    Video_Game record2("d", "Test genre", "Test creator", 1994, 90);
    Video_Game record3("c", "Test genre", "Test creator", 1994, 90);
    database.add_record(record1);
    database.add_record(record2);
    database.add_record(record3);

    vector<string> titles;
    for (Video_Game game : database.list_by_title("1")) {
        titles.push_back(game.get_title());
    }
    vector<string> ordered_titles = {"a", "c", "d"};
    assert(titles == ordered_titles);

    titles.clear();
     for (Video_Game game : database.list_by_title("2")) {
        titles.push_back(game.get_title());
    }
    ordered_titles = {"d", "c", "a"};
    assert(titles == ordered_titles);

    database.delete_record(record1);   
    database.delete_record(record2);  
    database.delete_record(record3);  
}

void list_by_genre_test()
{
    Database database("test_database.txt");
    Video_Game record1("Test title", "a", "Test creator", 1994, 90);
    Video_Game record2("Test title", "d", "Test creator", 1994, 90);
    Video_Game record3("Test title", "c", "Test creator", 1994, 90);
    database.add_record(record1);
    database.add_record(record2);
    database.add_record(record3);

    vector<string> genres;
    for (Video_Game game : database.list_by_genre("1")) {
        genres.push_back(game.get_genre());
    }
    vector<string> ordered_genres = {"a", "c", "d"};
    assert(genres == ordered_genres);

    genres.clear();
     for (Video_Game game : database.list_by_genre("2")) {
        genres.push_back(game.get_genre());
    }
    ordered_genres = {"d", "c", "a"};
    assert(genres == ordered_genres);

    database.delete_record(record1);   
    database.delete_record(record2);  
    database.delete_record(record3);  
}

void list_by_creator_test()
{
    Database database("test_database.txt");
    Video_Game record1("Test title", "Test genre", "a", 1994, 90);
    Video_Game record2("Test title", "Test genre", "d", 1994, 90);
    Video_Game record3("Test title", "Test genre", "c", 1994, 90);
    database.add_record(record1);
    database.add_record(record2);
    database.add_record(record3);

    vector<string> creators;
    for (Video_Game game : database.list_by_creator("1")) {
        creators.push_back(game.get_creator());
    }
    vector<string> ordered_creators = {"a", "c", "d"};
    assert(creators == ordered_creators);

    creators.clear();
     for (Video_Game game : database.list_by_creator("2")) {
        creators.push_back(game.get_creator());
    }
    ordered_creators = {"d", "c", "a"};
    assert(creators == ordered_creators);

    database.delete_record(record1);   
    database.delete_record(record2);  
    database.delete_record(record3); 
}

void list_by_year_published_test()
{
    Database database("test_database.txt");
    Video_Game record1("Test Title", "Test genre", "Test creator", 3, 90);
    Video_Game record2("Test Title", "Test genre", "Test creator", 1, 90);
    Video_Game record3("Test Title", "Test genre", "Test creator", 2, 90);
    database.add_record(record1);
    database.add_record(record2);
    database.add_record(record3);

    vector<int> years;
    for (Video_Game game : database.list_by_year_published("1")) {
        years.push_back(game.get_year_published());
    }
    vector<int> ordered_years = {1, 2, 3};
    assert(years == ordered_years);

    years.clear();
     for (Video_Game game : database.list_by_year_published("2")) {
        years.push_back(game.get_year_published());
    }
    ordered_years = {3, 2, 1};
    assert(years == ordered_years);

    database.delete_record(record1);   
    database.delete_record(record2);  
    database.delete_record(record3); 
}
void list_by_metacritic_score_test()
{
    Database database("test_database.txt");
    Video_Game record1("Test Title", "Test genre", "Test creator", 1994, 1);
    Video_Game record2("Test Title", "Test genre", "Test creator", 1994, 2);
    Video_Game record3("Test Title", "Test genre", "Test creator", 1994, 3);
    database.add_record(record1);
    database.add_record(record2);
    database.add_record(record3);

    vector<double> scores;
    for (Video_Game game : database.list_by_metacritic_score("1")) {
        scores.push_back(game.get_metacritic_score());
    }
    vector<double> ordered_scores = {1, 2 , 3};
    assert(scores == ordered_scores);

    scores.clear();
     for (Video_Game game : database.list_by_metacritic_score("2")) {
        scores.push_back(game.get_metacritic_score());
    }
    ordered_scores = {3, 2, 1};
    assert(scores == ordered_scores);

    database.delete_record(record1);   
    database.delete_record(record2);  
    database.delete_record(record3); 
}