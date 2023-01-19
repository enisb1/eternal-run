#ifndef MAP_HPP
#define MAP_HPP

/* Structs */

const int TYPE_ENTRANCE = 1;
const int TYPE_EXIT = 2;
const int TYPE_WALL = 3;
const int TYPE_COIN = 4;

struct block {
    int y;
    int x;
	int type;
};

struct map {
    block blocks[600];
    int num_blocks;
};

/* Methods */

// add a block to a map
void add_block(map *map, int y, int x);

// create maps for the game and put them inside an array
void create_maps(map *maps[]);

#endif