#ifndef MAP_HPP
#define MAP_HPP

/* Structs */

const int TYPE_WALL = 1;
const int TYPE_BLANK = 0;

struct block {
    int y;
    int x;
	int type;
	char symbol;
};

struct map {
    block blocks[100];
    int num_blocks;
};

/* Methods */

// add a block to a map
void add_block(map *map, int y, int x);

map *create_map();

#endif