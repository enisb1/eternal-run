/* Includes */

#include <fstream>
#include <cstring>
#include <dirent.h>
#include <sys/stat.h>

#include "storing.hpp"

using namespace std; 

/* Methods */

// creates directory to store files if it doesn't exist
void createDir(DIR* dir) {
    if (!dir) mkdir("storing_files");
}

void store_map_index(int level, int mapIndex) {
    ofstream outputFile;

    DIR* dir = opendir("storing_files/");
    createDir(dir);

    outputFile.open("storing_files/index_map_lvl" + to_string(level) + ".txt");
    outputFile << mapIndex;

    closedir(dir);
    outputFile.close();
}

void store_coins(int level, coin_node *coin_list) {
    ofstream outputFile;
    
    DIR* dir = opendir("storing_files/");
    createDir(dir);

    outputFile.open("storing_files/coins_map_lvl" + to_string(level) + ".txt");

    while (coin_list!=NULL) {
        outputFile << coin_list->y << " " << coin_list->x << " ";
        coin_list = coin_list->next;
    }

    closedir(dir);
    outputFile.close();
}

void store_enemies(int level, enemy_node *enemy_list) {
    ofstream outputFile;

    DIR* dir = opendir("storing_files/");
    createDir(dir);

    outputFile.open("storing_files/enemies_map_lvl" + to_string(level) + ".txt");

    while (enemy_list!=NULL) {
        outputFile << enemy_list->current_enemy.get_level() << " ";
        enemy_list = enemy_list->next;
    }

    closedir(dir);
    outputFile.close();
}

int get_stored_map_index(int level) {
    ifstream inputFile;
    inputFile.open("storing_files/index_map_lvl" + to_string(level) + ".txt");

    char mapIndexChar;
    while(!inputFile.eof()){
        inputFile.get(mapIndexChar);
    }
    inputFile.close();

    return (mapIndexChar - '0');
}

coin_node *get_stored_coin_list(int level) {
    ifstream inputFile;
    inputFile.open("storing_files/coins_map_lvl" + to_string(level) + ".txt");

    coin_node *coin_list = NULL;
    int coordinate;

    // while an integer is readable from the file add coin to coin_list
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

enemy_node *get_stored_enemy_list(map *map, Player player, int level) {
    ifstream inputFile;
    inputFile.open("storing_files/enemies_map_lvl" + to_string(level) + ".txt");

    enemy_node *enemy_list = NULL;
    int enemy_level;
    int enemy_y;
    int enemy_x;

    // while an integer is readable from the file add enemy to enemy_list
    while (inputFile >> enemy_level) {
        enemy_node *new_enemy = new enemy_node;
        
        get_random_enemy_position(map, player, enemy_y, enemy_x);
        Enemy new_enemy_object = Enemy(
            enemy_y, 
            enemy_x, 
            get_random_enemy_direction(map, enemy_y, enemy_x), 
            enemy_level
        );
        
        add_enemy(enemy_list, new_enemy_object);
    }

    inputFile.close();

    return enemy_list;
}

void delete_files() {
    DIR *dir = opendir("storing_files/");

    struct dirent *child;
    while ((child = readdir(dir)) != NULL) {
        char file_path[50];
        strcat(strcpy(file_path, "storing_files/"), child->d_name);
        remove(file_path);
    }

    closedir(dir);
}