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
map *create_map() {
    map *new_map = new map;

    // Entrance and exit
	add_blocks_vertically(new_map, 9, 10, 0, TYPE_ENTRANCE);
	add_blocks_vertically(new_map, 9, 10, 59, TYPE_EXIT);

	// Walls
	// Left
	add_blocks_vertically(new_map, 0, 8, 1, TYPE_WALL);
	add_blocks_vertically(new_map, 11, 20, 1, TYPE_WALL);

	add_blocks_vertically(new_map, 2, 13, 4, TYPE_WALL);
	add_blocks_vertically(new_map, 2, 13, 5, TYPE_WALL);

	add_blocks_horizontally(new_map, 2, 5, 11, TYPE_WALL);
	add_blocks_horizontally(new_map, 3, 5, 11, TYPE_WALL);
	add_blocks_vertically(new_map, 4, 7, 8, TYPE_WALL);
	add_blocks_vertically(new_map, 4, 7, 9, TYPE_WALL);

	add_blocks_horizontally(new_map, 15, 4, 8, TYPE_WALL);
	add_block(new_map, 16, 6, TYPE_WALL);
	add_blocks_horizontally(new_map, 17, 4, 8, TYPE_WALL);

	add_blocks_horizontally(new_map, 13, 8, 13, TYPE_WALL);
	add_blocks_vertically(new_map, 9, 12, 10, TYPE_WALL);
	add_blocks_vertically(new_map, 9, 12, 11, TYPE_WALL);

	add_blocks_vertically(new_map, 15, 18, 11, TYPE_WALL);
	add_blocks_vertically(new_map, 15, 18, 12, TYPE_WALL);
	add_blocks_vertically(new_map, 15, 18, 13, TYPE_WALL);

	add_blocks_vertically(new_map, 2, 3, 15, TYPE_WALL);
	add_blocks_vertically(new_map, 2, 3, 16, TYPE_WALL);
	add_blocks_vertically(new_map, 2, 3, 17, TYPE_WALL);
	add_blocks_vertically(new_map, 2, 3, 18, TYPE_WALL);
	add_blocks_horizontally(new_map, 4, 13, 20, TYPE_WALL);
	add_blocks_horizontally(new_map, 5, 13, 20, TYPE_WALL);
	add_blocks_horizontally(new_map, 6, 13, 20, TYPE_WALL);

	add_blocks_horizontally(new_map, 9, 14, 20, TYPE_WALL);
	add_blocks_horizontally(new_map, 10, 14, 20, TYPE_WALL);
	add_blocks_horizontally(new_map, 11, 14, 20, TYPE_WALL);
	add_blocks_horizontally(new_map, 8, 16, 18, TYPE_WALL);

	// Center
	add_blocks_vertically(new_map, 5, 9, 29, TYPE_WALL);
	add_blocks_vertically(new_map, 4, 10, 30, TYPE_WALL);
	add_blocks_vertically(new_map, 4, 10, 31, TYPE_WALL);
	add_blocks_vertically(new_map, 5, 9, 32, TYPE_WALL);
	add_blocks_horizontally(new_map, 3, 23, 38, TYPE_WALL);
	add_blocks_horizontally(new_map, 11, 23, 38, TYPE_WALL);

	add_blocks_horizontally(new_map, 5, 33, 35, TYPE_WALL);
	add_blocks_horizontally(new_map, 9, 33, 35, TYPE_WALL);
	add_block(new_map, 6, 35, TYPE_WALL);
	add_block(new_map, 8, 35, TYPE_WALL);
	add_blocks_vertically(new_map, 4, 6, 38, TYPE_WALL);
	add_blocks_vertically(new_map, 8, 10, 38, TYPE_WALL);

	add_blocks_horizontally(new_map, 5, 26, 28, TYPE_WALL);
	add_blocks_horizontally(new_map, 9, 26, 28, TYPE_WALL);
	add_block(new_map, 6, 26, TYPE_WALL);
	add_block(new_map, 8, 26, TYPE_WALL);
	add_blocks_vertically(new_map, 4, 6, 23, TYPE_WALL);
	add_blocks_vertically(new_map, 8, 10, 23, TYPE_WALL);

	// Center top
	add_block(new_map, 1, 25, TYPE_WALL);
	add_block(new_map, 2, 30, TYPE_WALL);
	add_block(new_map, 1, 36, TYPE_WALL);

	// Center bottom
	add_blocks_horizontally(new_map, 13, 16, 48, TYPE_WALL);
	add_blocks_horizontally(new_map, 14, 16, 48, TYPE_WALL);
	add_block(new_map, 15, 20, TYPE_WALL);
	add_block(new_map, 15, 28, TYPE_WALL);
	add_block(new_map, 15, 36, TYPE_WALL);
	add_block(new_map, 15, 44, TYPE_WALL);
	add_block(new_map, 16, 24, TYPE_WALL);
	add_block(new_map, 16, 32, TYPE_WALL);
	add_blocks_horizontally(new_map, 17, 16, 48, TYPE_WALL);
	add_blocks_horizontally(new_map, 18, 16, 48, TYPE_WALL);

	// Right
	add_blocks_vertically(new_map, 3, 11, 41, TYPE_WALL);
	add_blocks_vertically(new_map, 3, 11, 42, TYPE_WALL);
	add_blocks_vertically(new_map, 2, 11, 43, TYPE_WALL);
	add_blocks_vertically(new_map, 2, 11, 44, TYPE_WALL);
	add_blocks_vertically(new_map, 2, 11, 45, TYPE_WALL);
	add_blocks_vertically(new_map, 2, 11, 46, TYPE_WALL);
	add_blocks_vertically(new_map, 2, 11, 47, TYPE_WALL);
	add_blocks_vertically(new_map, 3, 7, 48, TYPE_WALL);
	add_blocks_vertically(new_map, 3, 7, 49, TYPE_WALL);

	add_blocks_vertically(new_map, 2, 12, 53, TYPE_WALL);
	add_blocks_vertically(new_map, 2, 12, 54, TYPE_WALL);
	add_blocks_vertically(new_map, 2, 10, 55, TYPE_WALL);
	add_blocks_vertically(new_map, 9, 12, 56, TYPE_WALL);
	add_blocks_vertically(new_map, 2, 10, 52, TYPE_WALL);
	add_blocks_vertically(new_map, 9, 12, 51, TYPE_WALL);


	add_blocks_horizontally(new_map, 15, 51, 56, TYPE_WALL);
	add_blocks_horizontally(new_map, 16, 51, 56, TYPE_WALL);
	add_blocks_horizontally(new_map, 14, 53, 54, TYPE_WALL);
	add_blocks_horizontally(new_map, 17, 53, 54, TYPE_WALL);

    return new_map;
}
