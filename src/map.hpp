#ifndef MAP_HPP
#define MAP_HPP

/* Structs */

const int TYPE_WALL = 3;
const int TYPE_EXIT = 2;
const int TYPE_ENTRANCE = 1;

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

map *create_map();

#endif