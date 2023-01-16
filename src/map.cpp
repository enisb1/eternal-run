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
	// 0 < y1&&y2 < 20 && y1<y2
	for (int i = y1; i <= y2; i++) {
		add_block(map, i, x, type);
	}
}

void add_blocks_horizontally(map *map, int y, int x1, int x2, int type) {
	// Precondition: x1 and x2 should not be out of bounds and x1<x2
	// 0 < x1&&x2 < 60 && x1<x2
	for (int i = x1; i <= x2; i++) {
		add_block(map, y, i, type);
	}
}

void add_hor_passage(map *map, int y, int x1, int x2, int type) {
	// Precondition: same as add_blocks_horizontally
	add_blocks_horizontally(map, y, x1, x2, type);
}

void add_ver_passage(map *map, int y1, int y2, int x, int type) {
	// Precondition: same as add_blocks_vertically
	add_blocks_vertically(map, y1, y2, x, type);
}

map *create_map() {
    map *new_map = new map;

    // Entrance and exit
	add_hor_passage(new_map, 19, 5, 7, type_entrance);
	add_ver_passage(new_map, 9, 10, 59, type_exit);

    return new_map;
}
