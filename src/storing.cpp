/* Includes */

#include <fstream>

#include "map.hpp"
#include "storing.hpp"

using namespace std; 

/* Methods */

void store_coins(int level, coin_node *cHead) {
    ofstream outputFile;
    outputFile.open("coins_map_lvl_" + to_string(level) + ".txt");

    while (cHead!=NULL) {
        outputFile << cHead->y << "," << cHead->x << endl;
        cHead = cHead->next;
    }

    outputFile.close();
}

void store_map_index(int level, int mapIndex) {
    ofstream outputFile;
    outputFile.open("index_map_lvl" + to_string(level) + ".txt");
    outputFile << mapIndex;
    outputFile.close();
}