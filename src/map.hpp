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

// methods to create each map's default coin list
coin_node *create_coin_list_map1();

coin_node *create_coin_list_map2();

coin_node *create_coin_list_map3();

coin_node *create_coin_list_map4();

coin_node *create_coin_list_map5();

coin_node *create_coin_list_map6();

// create default_maps for the game and put them inside an array
void create_default_maps(map *default_maps[]);

#endif