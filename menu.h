#ifndef MENU_H
#define MENU_H

#include "record.h"
#include "database.h"
#include <string>

using namespace std;

// class that displays menus and deals with logic regarding user inputs
class Menu {

private:
    const int WIDTH;
    Database database;

public:
    Menu();

    void main_menu();

    void display_game(Video_Game game);
    void display_games(vector<Video_Game> games);
    void add_menu();

    void find_menu();
    void find_by_title();
    void find_by_genre();
    void find_by_creator();
    void find_by_year_published();
    void find_by_metacritic_score();

    void delete_menu();
    void delete_by_title();
    void delete_by_genre();
    void delete_by_creator();
    void delete_by_year_published();
    void delete_by_metacritic_score();

    void list_menu();
    void list_by_title();
    void list_by_genre();
    void list_by_creator();
    void list_by_year_published();
    void list_by_metacritic_score();
    
};
// no automated tests because this class relies on user input

#endif