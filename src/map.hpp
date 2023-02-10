#ifndef MAP_HPP
#define MAP_HPP

/* Constants */

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

// add coin to coin list
void add_coin(coin_node* &head, int y, int x);

// return the first map 
map *create_map1();

// return the second map
map *create_map2();

// return the third map
map *create_map3();

// return the fourth map
map *create_map4();

// return the fifth map
map *create_map5();

// return the sixth map
map *create_map6();

// return the specified map's default coin list
void get_default_coin_list(coin_node* &coin_list, int map_index);

#endif