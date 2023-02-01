#ifndef MAP_HPP
#define MAP_HPP

/* Vars */

const int EMPTY_BLOCK = -1;
const int ENTRANCE_BLOCK = 1;
const int EXIT_BLOCK = 2;
const int WALL_BLOCK = 3;
const int COIN_BLOCK = 4;

/* Structs */

struct coin {
	int y;
	int x; 
	coin *next;	
};

struct map {
    int blocks[20][60];
	int entrance_exit_positions[4]; // [entrancey, entrancex, exity, exitx]
	coin *coin_list;
};

/* Methods */

// create default_maps for the game and put them inside an array
void create_default_maps(map *default_maps[]);

#endif