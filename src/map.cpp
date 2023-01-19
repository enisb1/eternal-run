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

map *create_map1() {
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

map *create_map2() {
	map *new_map = new map;

	// Entrance and exit
	add_blocks_vertically(new_map, 9, 10, 0, TYPE_ENTRANCE);
	add_blocks_vertically(new_map, 9, 10, 59, TYPE_EXIT);

	// Walls
	// Left
	add_blocks_vertically(new_map, 2, 5, 3, TYPE_WALL);
	add_blocks_vertically(new_map, 2, 5, 4, TYPE_WALL);
	add_blocks_horizontally(new_map, 2, 4, 8, TYPE_WALL);
	add_blocks_horizontally(new_map, 3, 4, 8, TYPE_WALL);

	add_blocks_horizontally(new_map, 5, 7, 10, TYPE_WALL);
	add_blocks_horizontally(new_map, 6, 7, 10, TYPE_WALL);
	add_blocks_vertically(new_map, 2, 6, 11, TYPE_WALL);
	add_blocks_vertically(new_map, 2, 6, 12, TYPE_WALL);

	add_blocks_vertically(new_map, 2, 6, 15, TYPE_WALL);
	add_blocks_vertically(new_map, 2, 6, 16, TYPE_WALL);
	add_blocks_vertically(new_map, 2, 6, 17, TYPE_WALL);

	add_blocks_horizontally(new_map, 2, 18, 27, TYPE_WALL);
	add_blocks_horizontally(new_map, 3, 18, 27, TYPE_WALL);

	add_blocks_vertically(new_map, 8, 16, 3, TYPE_WALL);
	add_blocks_vertically(new_map, 8, 16, 4, TYPE_WALL);
	add_block(new_map, 10, 5, TYPE_WALL);
	add_block(new_map, 14, 5, TYPE_WALL);

	add_blocks_vertically(new_map, 8, 16, 8, TYPE_WALL);
	add_blocks_vertically(new_map, 8, 16, 9, TYPE_WALL);
	add_block(new_map, 8, 10, TYPE_WALL);
	add_block(new_map, 10, 10, TYPE_WALL);
	add_block(new_map, 15, 10, TYPE_WALL);

	add_blocks_vertically(new_map, 8, 16, 13, TYPE_WALL);
	add_blocks_vertically(new_map, 8, 16, 14, TYPE_WALL);
	add_blocks_vertically(new_map, 8, 15, 15, TYPE_WALL);
	add_blocks_vertically(new_map, 8, 15, 16, TYPE_WALL);
	add_blocks_vertically(new_map, 8, 16, 17, TYPE_WALL);
	add_block(new_map, 11, 12, TYPE_WALL);
	add_block(new_map, 12, 12, TYPE_WALL);
	add_block(new_map, 13, 12, TYPE_WALL);

	add_blocks_horizontally(new_map, 18, 3, 17, TYPE_WALL);

	// Center
	add_blocks_horizontally(new_map, 9, 20, 24, TYPE_WALL);
	add_blocks_horizontally(new_map, 10, 20, 24, TYPE_WALL);
	add_blocks_horizontally(new_map, 11, 20, 24, TYPE_WALL);
	add_blocks_vertically(new_map, 5, 15, 25, TYPE_WALL);
	add_blocks_vertically(new_map, 5, 15, 26, TYPE_WALL);
	add_blocks_vertically(new_map, 5, 15, 27, TYPE_WALL);
	add_blocks_vertically(new_map, 9, 11, 28, TYPE_WALL);
	add_blocks_vertically(new_map, 9, 11, 29, TYPE_WALL);

	add_blocks_horizontally(new_map, 9, 37, 41, TYPE_WALL);
	add_blocks_horizontally(new_map, 10, 37, 41, TYPE_WALL);
	add_blocks_horizontally(new_map, 11, 37, 41, TYPE_WALL);
	add_blocks_vertically(new_map, 9, 11, 32, TYPE_WALL);
	add_blocks_vertically(new_map, 9, 11, 33, TYPE_WALL);
	add_blocks_vertically(new_map, 5, 15, 34, TYPE_WALL);
	add_blocks_vertically(new_map, 5, 15, 35, TYPE_WALL);
	add_blocks_vertically(new_map, 5, 15, 36, TYPE_WALL);

	add_blocks_vertically(new_map, 5, 7, 30, TYPE_WALL);
	add_blocks_vertically(new_map, 5, 7, 31, TYPE_WALL);

	add_blocks_vertically(new_map, 13, 15, 30, TYPE_WALL);
	add_blocks_vertically(new_map, 13, 15, 31, TYPE_WALL);

	add_blocks_vertically(new_map, 13, 17, 20, TYPE_WALL);
	add_blocks_vertically(new_map, 13, 17, 21, TYPE_WALL);
	add_blocks_vertically(new_map, 13, 17, 22, TYPE_WALL);

	add_blocks_vertically(new_map, 13, 17, 39, TYPE_WALL);
	add_blocks_vertically(new_map, 13, 17, 40, TYPE_WALL);
	add_blocks_vertically(new_map, 13, 17, 41, TYPE_WALL);

	add_blocks_vertically(new_map, 5, 7, 20, TYPE_WALL);
	add_blocks_vertically(new_map, 5, 7, 21, TYPE_WALL);
	add_blocks_vertically(new_map, 5, 7, 22, TYPE_WALL);

	add_blocks_vertically(new_map, 5, 7, 39, TYPE_WALL);
	add_blocks_vertically(new_map, 5, 7, 40, TYPE_WALL);
	add_blocks_vertically(new_map, 5, 7, 41, TYPE_WALL);

	// Center top
	add_blocks_horizontally(new_map, 2, 30, 35, TYPE_WALL);
	add_blocks_horizontally(new_map, 3, 30, 41, TYPE_WALL);

	// Center bottom
	add_blocks_horizontally(new_map, 17, 25, 36, TYPE_WALL);
	add_blocks_horizontally(new_map, 18, 25, 36, TYPE_WALL);

	// Right
	add_blocks_horizontally(new_map, 1, 38, 44, TYPE_WALL);

	add_blocks_horizontally(new_map, 3, 44, 45, TYPE_WALL);

	add_blocks_vertically(new_map, 2, 5, 56, TYPE_WALL);
	add_blocks_vertically(new_map, 2, 5, 55, TYPE_WALL);
	add_blocks_horizontally(new_map, 2, 51, 54, TYPE_WALL);
	add_blocks_horizontally(new_map, 3, 51, 54, TYPE_WALL);

	add_blocks_vertically(new_map, 2, 6, 48, TYPE_WALL);
	add_blocks_vertically(new_map, 2, 6, 47, TYPE_WALL);
	add_blocks_horizontally(new_map, 5, 49, 52, TYPE_WALL);
	add_blocks_horizontally(new_map, 6, 49, 52, TYPE_WALL);

	add_blocks_vertically(new_map, 5, 9, 44, TYPE_WALL);
	add_blocks_vertically(new_map, 5, 9, 45, TYPE_WALL);
	add_blocks_vertically(new_map, 5, 9, 46, TYPE_WALL);
	add_blocks_horizontally(new_map, 8, 47, 52, TYPE_WALL);
	add_blocks_horizontally(new_map, 9, 47, 52, TYPE_WALL);

	add_blocks_vertically(new_map, 7, 12, 55, TYPE_WALL);
	add_blocks_vertically(new_map, 7, 12, 56, TYPE_WALL);
	add_blocks_horizontally(new_map, 11, 44, 56, TYPE_WALL);
	add_blocks_horizontally(new_map, 12, 44, 56, TYPE_WALL);

	add_blocks_horizontally(new_map, 14, 44, 45, TYPE_WALL);
	add_blocks_horizontally(new_map, 14, 55, 56, TYPE_WALL);

	add_blocks_horizontally(new_map, 14, 48, 52, TYPE_WALL);
	add_blocks_horizontally(new_map, 15, 48, 52, TYPE_WALL);
	add_blocks_horizontally(new_map, 16, 44, 56, TYPE_WALL);
	add_blocks_horizontally(new_map, 17, 44, 56, TYPE_WALL);

	return new_map;
}

map *create_map3() {
	map *new_map = new map;

	// Entrance and exit
	add_blocks_vertically(new_map, 9, 10, 0, TYPE_ENTRANCE);
	add_blocks_vertically(new_map, 9, 10, 59, TYPE_EXIT);

	// Left
	add_blocks_horizontally(new_map, 2, 3, 8, TYPE_WALL);
	add_blocks_horizontally(new_map, 3, 3, 8, TYPE_WALL);
	add_blocks_vertically(new_map, 4, 6, 7, TYPE_WALL);
	add_blocks_vertically(new_map, 4, 6, 8, TYPE_WALL);
	add_blocks_horizontally(new_map, 5, 9, 15, TYPE_WALL);
	add_blocks_horizontally(new_map, 6, 9, 15, TYPE_WALL);

	add_blocks_horizontally(new_map, 2, 11, 15, TYPE_WALL);
	add_blocks_horizontally(new_map, 3, 11, 15, TYPE_WALL);

	add_blocks_horizontally(new_map, 8, 3, 19, TYPE_WALL);
	add_blocks_horizontally(new_map, 9, 3, 19, TYPE_WALL);
	add_blocks_horizontally(new_map, 10, 3, 19, TYPE_WALL);
	add_blocks_horizontally(new_map, 11, 3, 19, TYPE_WALL);
	add_blocks_vertically(new_map, 5, 7, 3, TYPE_WALL);
	add_blocks_vertically(new_map, 5, 7, 4, TYPE_WALL);

	add_blocks_horizontally(new_map, 13, 3, 13, TYPE_WALL);
	add_blocks_horizontally(new_map, 14, 3, 13, TYPE_WALL);
	add_blocks_vertically(new_map, 15, 16, 12, TYPE_WALL);
	add_blocks_vertically(new_map, 15, 16, 13, TYPE_WALL);
	add_blocks_horizontally(new_map, 15, 14, 19, TYPE_WALL);
	add_blocks_horizontally(new_map, 16, 14, 19, TYPE_WALL);

	add_blocks_horizontally(new_map, 13, 16, 19, TYPE_WALL);

	add_blocks_horizontally(new_map, 18, 3, 14, TYPE_WALL);
	add_blocks_horizontally(new_map, 17, 3, 9, TYPE_WALL);
	add_blocks_horizontally(new_map, 16, 3, 8, TYPE_WALL);

	// Center (from top to bottom)
	add_blocks_horizontally(new_map, 2, 18, 25, TYPE_WALL);
	add_block(new_map, 3, 19, TYPE_WALL);
	add_block(new_map, 4, 22, TYPE_WALL);
	add_blocks_horizontally(new_map, 5, 18, 24, TYPE_WALL);
	add_blocks_horizontally(new_map, 6, 18, 24, TYPE_WALL);
	add_blocks_horizontally(new_map, 3, 25, 29, TYPE_WALL);
	add_blocks_horizontally(new_map, 4, 25, 29, TYPE_WALL);

	add_blocks_vertically(new_map, 2, 6, 30, TYPE_WALL);
	add_blocks_horizontally(new_map, 2, 31, 38, TYPE_WALL);
	add_blocks_horizontally(new_map, 6, 31, 38, TYPE_WALL);
	add_block(new_map, 3, 38, TYPE_WALL);
	add_block(new_map, 5, 38, TYPE_WALL);
	add_block(new_map, 4, 32, TYPE_WALL);
	add_block(new_map, 4, 35, TYPE_WALL);

	add_blocks_horizontally(new_map, 10, 22, 38, TYPE_WALL);
	add_blocks_horizontally(new_map, 11, 22, 38, TYPE_WALL);
	add_blocks_vertically(new_map, 8, 9, 22, TYPE_WALL);
	add_blocks_vertically(new_map, 8, 9, 23, TYPE_WALL);
	add_blocks_vertically(new_map, 8, 9, 24, TYPE_WALL);
	add_blocks_vertically(new_map, 8, 9, 36, TYPE_WALL);
	add_blocks_vertically(new_map, 8, 9, 37, TYPE_WALL);
	add_blocks_vertically(new_map, 8, 9, 38, TYPE_WALL);

	add_blocks_horizontally(new_map, 8, 27, 33, TYPE_WALL);
	add_blocks_vertically(new_map, 6, 7, 27, TYPE_WALL);

	add_blocks_horizontally(new_map, 13, 22, 38, TYPE_WALL);
	add_blocks_horizontally(new_map, 14, 22, 38, TYPE_WALL);
	add_blocks_vertically(new_map, 15, 16, 22, TYPE_WALL);
	add_blocks_vertically(new_map, 15, 16, 23, TYPE_WALL);
	add_blocks_vertically(new_map, 15, 16, 24, TYPE_WALL);
	add_blocks_vertically(new_map, 15, 16, 36, TYPE_WALL);
	add_blocks_vertically(new_map, 15, 16, 37, TYPE_WALL);
	add_blocks_vertically(new_map, 15, 16, 38, TYPE_WALL);

	add_blocks_horizontally(new_map, 18, 17, 43, TYPE_WALL);
	add_blocks_horizontally(new_map, 16, 27, 33, TYPE_WALL);
	add_blocks_horizontally(new_map, 17, 27, 33, TYPE_WALL);

	// Right
	add_blocks_horizontally(new_map, 2, 41, 50, TYPE_WALL);
	add_blocks_horizontally(new_map, 3, 41, 50, TYPE_WALL);
	add_blocks_horizontally(new_map, 4, 50, 55, TYPE_WALL);
	add_blocks_horizontally(new_map, 5, 41, 50, TYPE_WALL);
	add_blocks_horizontally(new_map, 6, 41, 50, TYPE_WALL);
	add_blocks_vertically(new_map, 2, 3, 55, TYPE_WALL);
	add_blocks_vertically(new_map, 5, 6, 55, TYPE_WALL);
	add_blocks_horizontally(new_map, 2, 53, 54, TYPE_WALL);
	add_blocks_horizontally(new_map, 6, 53, 54, TYPE_WALL);

	add_blocks_horizontally(new_map, 8, 41, 47, TYPE_WALL);
	add_blocks_horizontally(new_map, 9, 41, 47, TYPE_WALL);
	add_blocks_horizontally(new_map, 10, 41, 47, TYPE_WALL);
	add_blocks_horizontally(new_map, 11, 41, 47, TYPE_WALL);

	add_blocks_horizontally(new_map, 8, 50, 56, TYPE_WALL);
	add_blocks_horizontally(new_map, 9, 50, 56, TYPE_WALL);
	add_blocks_horizontally(new_map, 10, 50, 56, TYPE_WALL);
	add_blocks_horizontally(new_map, 11, 50, 56, TYPE_WALL);

	add_blocks_horizontally(new_map, 13, 41, 56, TYPE_WALL);
	add_blocks_horizontally(new_map, 14, 41, 56, TYPE_WALL);
	add_blocks_horizontally(new_map, 15, 41, 56, TYPE_WALL);
	add_blocks_horizontally(new_map, 16, 46, 52, TYPE_WALL);
	add_blocks_horizontally(new_map, 17, 46, 52, TYPE_WALL);

	add_blocks_horizontally(new_map, 17, 55, 56, TYPE_WALL);

	add_blocks_horizontally(new_map, 17, 41, 42, TYPE_WALL);

	return new_map;
}
