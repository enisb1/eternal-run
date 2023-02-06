#ifndef MAP_HPP
#define MAP_HPP

/* Vars */

const int EMPTY_BLOCK = -1;
const int ENTRANCE_BLOCK = 1;
const int EXIT_BLOCK = 2;
const int WALL_BLOCK = 3;

/* Structs */

struct coin_node {
	int y;
	int x; 
	coin_node *next;	
};

struct map {
    int blocks[20][60];
	int entrance_exit_positions[4]; // [entrance_y, entrance_x, exit_y, exit_x]
};

/* Methods */

// adds coin to coin list
void add_coin(coin_node* &head, int y, int x);

// return the specified map's default coin list
void get_default_coin_list(coin_node* &coin_list, int map_index);

// create default_maps for the game and put them inside an array
void create_default_maps(map *default_maps[]);

#endif