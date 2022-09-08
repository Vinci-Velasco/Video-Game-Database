#ifndef RECORD_H
#define RECORD_H
#include <string>

using namespace std;

class Video_Game {

private:
    string title;
    string genre;
    string creator;
    int year_published;
    double metacritic_score;

public:
    Video_Game(string t, string g, string c, int y, double m);
    string get_title() const;
    string get_genre() const;
    string get_creator() const;
    int get_year_published() const;
    double get_metacritic_score() const;

};

bool operator==(Video_Game game1, Video_Game game2);

void Video_Game_tests(); // uses all test functions
void get_title_test();
void get_genre_test();
void get_creator_test();
void get_year_published_test();
void get_metacritic_score_test();

#endif