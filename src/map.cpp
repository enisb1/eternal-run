/* Includes */

#include "map.hpp"

/* Methods */

void add_block(map *map, int y, int x, int type) {
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
        block new_block = {y, x, type};
        map -> blocks[map -> num_blocks] = new_block;
        map -> num_blocks++;
    }
}

void add_blocks_vertically(map *map, int y1, int y2, int x, int type) {
	// Precondition: y1 and y2 should not be out of bounds and y1<y2
	// 0 < y1 < 20 && y1 < y2
	for (int i = y1; i <= y2; i++) {
		add_block(map, i, x, type);
	}
}

void add_blocks_horizontally(map *map, int y, int x1, int x2, int type) {
	// Precondition: x1 and x2 should not be out of bounds and x1<x2
	// 0 < x1 < 60 && x1 < x2
	for (int i = x1; i <= x2; i++) {
		add_block(map, y, i, type);
	}
}

map *create_map() {
    map *new_map = new map;

    // add entry and exit
    add_blocks_vertically(new_map, 2, 4, 0, TYPE_ENTRANCE);
    add_blocks_vertically(new_map, 2, 4, 59, TYPE_EXIT);
    
    // add walls
    add_blocks_horizontally(new_map, 1, 1, 15, TYPE_WALL);
    add_blocks_horizontally(new_map, 1, 44, 58, TYPE_WALL);

    add_blocks_vertically(new_map, 4, 11, 9, TYPE_WALL);
    add_blocks_vertically(new_map, 4, 11, 10, TYPE_WALL);
    add_blocks_horizontally(new_map, 7, 5, 8, TYPE_WALL);
    add_blocks_horizontally(new_map, 8, 5, 8, TYPE_WALL);
    
    add_blocks_vertically(new_map, 10, 13, 5, TYPE_WALL);
    add_blocks_vertically(new_map, 10, 13, 4, TYPE_WALL);
    add_blocks_horizontally(new_map, 13, 6, 10, TYPE_WALL);
    
    add_blocks_vertically(new_map, 2, 11, 14, TYPE_WALL);
    add_blocks_vertically(new_map, 2, 11, 15, TYPE_WALL);
    add_blocks_vertically(new_map, 2, 13, 18, TYPE_WALL);
    add_blocks_vertically(new_map, 2, 13, 19, TYPE_WALL);
    add_blocks_horizontally(new_map, 13, 14, 17, TYPE_WALL);
    
    add_blocks_horizontally(new_map, 2, 18, 27, TYPE_WALL);
    add_blocks_horizontally(new_map, 2, 32, 41, TYPE_WALL);
    add_blocks_horizontally(new_map, 3, 16, 27, TYPE_WALL);
    add_blocks_horizontally(new_map, 3, 32, 43, TYPE_WALL);

    return new_map;
}