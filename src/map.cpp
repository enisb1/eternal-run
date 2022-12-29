/* Includes */

#include "map.hpp"

/* Methods */

void add_block(map *map, int y, int x) {
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
        block new_block = {y, x};
        map -> blocks[map -> num_blocks] = new_block;
        map -> num_blocks++;
    }
}

map *create_map() {
    map *new_map = new map;

    add_block(new_map, 4, 5);
    add_block(new_map, 4, 6);
    add_block(new_map, 4, 7);
    add_block(new_map, 4, 8);
    
    return new_map;
}