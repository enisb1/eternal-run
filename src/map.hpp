#ifndef MAP_HPP
#define MAP_HPP

/* Structs */

const int TYPE_EMPTY = -1;
const int TYPE_ENTRANCE = 1;
const int TYPE_EXIT = 2;
const int TYPE_WALL = 3;
const int TYPE_COIN = 4;

struct map {
    int blocks[20][60];
};

/* Methods */

// create maps for the game and put them inside an array
void create_maps(map *maps[]);

#endif