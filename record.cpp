#include "record.h"
#include <string>
#include <cassert>

using namespace std;

Video_Game::Video_Game(string t, string g, string c, int y, double m)
: title(t), genre(g), creator(c), year_published(y), metacritic_score(m)
{}

string Video_Game::get_title() const
{
    return title;
}

string Video_Game::get_genre() const
{
    return genre;
}

string Video_Game::get_creator() const
{
    return creator;
}

int Video_Game::get_year_published() const
{
    return year_published;
}

double Video_Game::get_metacritic_score() const
{
    return metacritic_score;
}

bool operator==(Video_Game game1, Video_Game game2) 
{
    if (game1.get_title() != game2.get_title()) {
        return false;
    }
    else if (game1.get_genre() != game2.get_genre()) {
        return false;
    }
    else if (game1.get_creator() != game2.get_creator()) {
        return false;
    }
    else if (game1.get_year_published() != game2.get_year_published()) {
        return false;
    }
    else if (game1.get_metacritic_score() != game2.get_metacritic_score()) {
        return false;
    }
    return true;
}

// All testing regarding the Video_Game class
void Video_Game_tests()
{
    get_title_test();
    get_genre_test();
    get_creator_test();
    get_year_published_test();
    get_metacritic_score_test();
}

void get_title_test()
{
    Video_Game game1("Test", "Action", "Test company" , 2012, 84);
    assert(game1.get_title() == "Test");

    Video_Game game2("Test2", "Action", "Test company" , 2012, 84);
    assert(game2.get_title() == "Test2");
}

void get_genre_test()
{
    Video_Game game1("Test", "Action", "Test company" , 2012, 84);
    assert(game1.get_genre() == "Action");

    Video_Game game2("Test2", "Adventure", "Test company" , 2012, 84);
    assert(game2.get_genre() == "Adventure");
}

void get_creator_test()
{
    Video_Game game1("Test", "Action", "Test company" , 2012, 84);
    assert(game1.get_creator() == "Test company");

    Video_Game game2("Test2", "Action", "Another company" , 2012, 84);
    assert(game2.get_creator() == "Another company");
}

void get_year_published_test()
{
    Video_Game game1("Test", "Action", "Test company" , 2012, 84);
    assert(game1.get_year_published() == 2012);

    Video_Game game2("Test2", "Action", "Test company" , 2005, 84);
    assert(game2.get_year_published() == 2005);
}

void get_metacritic_score_test()
{
    Video_Game game1("Test", "Action", "Test company" , 2012, 84);
    assert(game1.get_metacritic_score() == 84);

    Video_Game game2("Test2", "Action", "Test company" , 2012, 63);
    assert(game2.get_metacritic_score() == 63);
}