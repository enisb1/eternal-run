/* Includes */

#include <ncursesw/ncurses.h>
#include <fstream>
#include <iostream>

#include "map.hpp"
#include "storing.hpp"

using namespace std; 

/* Methods */

// TODO: remove ncurses library when testing is finished

void store_coins(int level, coin_node *coin_list) {
    ofstream outputFile;
    outputFile.open("storingFiles/coins_map_lvl" + to_string(level) + ".txt");

    while (coin_list!=NULL) {
        outputFile << coin_list->y << " " << coin_list->x << " ";
        coin_list = coin_list->next;
    }

    outputFile.close();
}

void store_map_index(int level, int mapIndex) {
    ofstream outputFile;
    outputFile.open("storingFiles/index_map_lvl" + to_string(level) + ".txt");
    outputFile << mapIndex;
    outputFile.close();
}

coin_node *get_stored_coin_list(int level) {
    ifstream inputFile;
    inputFile.open("storingFiles/coins_map_lvl" + to_string(level) + ".txt");

    coin_node *coin_list = NULL;
    int coordinate;

    // while an integer is readable from the file add coins to coin_list
    while (inputFile >> coordinate) {
        coin_node *new_coin = new coin_node;
        int y = coordinate;
        inputFile >> coordinate;
        int x = coordinate;
        add_coin(coin_list, y, x);
    }

    inputFile.close();   

    return coin_list;
}

int get_stored_map_index(int level) {
    ifstream inputFile;
    inputFile.open("storingFiles/index_map_lvl" + to_string(level) + ".txt");

    char mapIndexChar;
    while(!inputFile.eof()){
        inputFile.get(mapIndexChar);
    }
    inputFile.close();

    return (mapIndexChar - '0');
}