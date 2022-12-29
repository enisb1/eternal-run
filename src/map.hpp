#ifndef MAP_HPP
#define MAP_HPP

/* Structs */

struct block {
    int y;
    int x;
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