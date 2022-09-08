#ifndef DATABASE_H
#define DATABASE_H

#include "record.h"
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class Database {

private:
    vector<Video_Game> all_records;
    // represents the file that's being opened
    // this var exits because there is 2 txt files with one being for testing
    string file; 

    // helper functions
    void convert_special_chars(string& s);
    void convert_commas(string& s);
    void update_database_file();

public:
    Database(string filename);

    vector<Video_Game> get_all_records() const;

    void add_record(Video_Game v);

    // find methods that return array of all records
    vector<Video_Game> find_by_title(string string_or_substring, string title) const;
    vector<Video_Game> find_by_genre(string string_or_substring, string genre) const;
    vector<Video_Game> find_by_creator(string string_or_substring, string creator) const;
    vector<Video_Game> find_by_year_published(int starting_year, int ending_year) const;
    vector<Video_Game> find_by_metacritic_score(double starting_score, double ending_score) const;

    // delete methods 
    void delete_record(Video_Game v);
    void delete_list_of_records(const vector<Video_Game>& vec);

    // list methods
    vector<Video_Game> list_by_title(string alpha_or_reverse) const;
    vector<Video_Game> list_by_genre(string alpha_or_reverse) const;
    vector<Video_Game> list_by_creator(string alpha_or_reverse) const;
    vector<Video_Game> list_by_year_published(string ascending_or_descending) const;
    vector<Video_Game> list_by_metacritic_score(string ascending_or_descending) const;
};

string convert_to_lower_case(string s);

void Database_tests();

void constructor_test();
void add_record_test();

void find_by_title_test();
void find_by_genre_test();
void find_by_creator_test();
void find_by_year_published_test();
void find_by_metacritic_score_test();

void delete_record_test();
void delete_list_of_records_test();

void list_by_title_test();
void list_by_genre_test();
void list_by_creator_test();
void list_by_year_published_test();
void list_by_metacritic_score_test();

#endif