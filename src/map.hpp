#ifndef MAP_HPP
#define MAP_HPP

/* Structs */

struct coin {
	int y;
	int x; 
	coin *next;	
};

const int EMPTY_BLOCK = -1;
const int ENTRANCE_BLOCK = 1;
const int EXIT_BLOCK = 2;
const int WALL_BLOCK = 3;
const int COIN_BLOCK = 4;

struct map {
    int blocks[20][60];
};

/* Methods */

// create maps for the game and put them inside an array
void create_maps(map *maps[]);

// create coins lists for each map and put them inside an array 
void create_coins_lists(coin *cLists[]);

#endif