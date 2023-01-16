/* Includes */

#include "map.hpp"

/* Methods */

void add_block(map *map, int y, int x, int type, char symbol) {
    // check if block already exists in map
    int i = 0;
    bool found = false;

    while (i < map -> num_blocks && !found) {
        if ((map -> blocks)[i].y == y && (map -> blocks)[i].x == x)
            found = true;
        else i++;
    }

    // add block if not already in map
    if (!found) {
        block new_block = {y, x, type, symbol};
        map -> blocks[map -> num_blocks] = new_block;
        map -> num_blocks++;
    }
}

map *create_map() {
    map *new_map = new map;

    return new_map;
}
