#ifndef MAP_HPP
#define MAP_HPP

/* Structs */

const int type_wall = 3;
const int type_exit = 2;
const int type_entrance = 1;

struct block {
    int y;
    int x;
	int type;
};

struct map {
    block blocks[200];
    int num_blocks;
};

/* Methods */

// add a block to a map
void add_block(map *map, int y, int x);

map *create_map();

#endif