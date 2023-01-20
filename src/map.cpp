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

void create_maps(map *maps[]) {
    /* Map 1 */
    map *map1 = new map;

    // add entrance and exit
    add_blocks_vertically(map1, 2, 4, 0, TYPE_ENTRANCE);
    add_blocks_vertically(map1, 2, 4, 59, TYPE_EXIT);
    
    // add walls
    add_blocks_vertically(map1, 4, 11, 9, TYPE_WALL);
    add_blocks_vertically(map1, 4, 11, 10, TYPE_WALL);
    add_blocks_horizontally(map1, 7, 5, 8, TYPE_WALL);
    add_blocks_horizontally(map1, 8, 5, 8, TYPE_WALL);
    
    add_blocks_vertically(map1, 10, 13, 5, TYPE_WALL);
    add_blocks_vertically(map1, 10, 13, 4, TYPE_WALL);
    add_blocks_horizontally(map1, 13, 6, 10, TYPE_WALL);
    
    add_blocks_vertically(map1, 1, 11, 14, TYPE_WALL);
    add_blocks_vertically(map1, 1, 11, 15, TYPE_WALL);
    add_blocks_vertically(map1, 2, 13, 18, TYPE_WALL);
    add_blocks_vertically(map1, 2, 13, 19, TYPE_WALL);
    add_blocks_horizontally(map1, 13, 14, 17, TYPE_WALL);
    
    add_blocks_horizontally(map1, 2, 18, 27, TYPE_WALL);
    add_blocks_horizontally(map1, 2, 32, 41, TYPE_WALL);
    add_blocks_horizontally(map1, 3, 16, 27, TYPE_WALL);
    add_blocks_horizontally(map1, 3, 32, 43, TYPE_WALL);
    
    add_blocks_horizontally(map1, 16, 1, 6, TYPE_WALL);
    
    add_blocks_horizontally(map1, 15, 10, 25, TYPE_WALL);
    add_blocks_vertically(map1, 16, 17, 11, TYPE_WALL);
    add_blocks_vertically(map1, 16, 17, 12, TYPE_WALL);
    
    add_blocks_horizontally(map1, 17, 16, 43, TYPE_WALL);
    add_blocks_vertically(map1, 15, 16, 29, TYPE_WALL);
    add_blocks_vertically(map1, 15, 16, 30, TYPE_WALL);
    
    add_blocks_horizontally(map1, 12, 20, 36, TYPE_WALL);
    
    add_blocks_horizontally(map1, 10, 23, 36, TYPE_WALL);
    add_blocks_vertically(map1, 5, 9, 23, TYPE_WALL);
    add_blocks_vertically(map1, 5, 9, 24, TYPE_WALL);
    add_blocks_vertically(map1, 5, 9, 36, TYPE_WALL);
    add_blocks_vertically(map1, 5, 9, 35, TYPE_WALL);
    add_blocks_horizontally(map1, 5, 23, 28, TYPE_WALL);
    add_blocks_horizontally(map1, 5, 31, 36, TYPE_WALL);


    add_blocks_vertically(map1, 2, 12, 40, TYPE_WALL);
    add_blocks_vertically(map1, 2, 12, 41, TYPE_WALL);
    
    add_blocks_vertically(map1, 1, 11, 44, TYPE_WALL);
    add_blocks_vertically(map1, 1, 11, 45, TYPE_WALL);
    
    add_blocks_horizontally(map1, 13, 40, 45, TYPE_WALL);
    
    add_blocks_horizontally(map1, 15, 34, 49, TYPE_WALL);
    add_blocks_vertically(map1, 16, 17, 47, TYPE_WALL);
    add_blocks_vertically(map1, 16, 17, 48, TYPE_WALL);
    
    add_blocks_horizontally(map1, 16, 53, 58, TYPE_WALL);
    
    add_blocks_vertically(map1, 10, 12, 54, TYPE_WALL);
    add_blocks_vertically(map1, 10, 12, 55, TYPE_WALL);
    add_blocks_horizontally(map1, 13, 49, 55, TYPE_WALL);

    add_blocks_vertically(map1, 4, 11, 50, TYPE_WALL);
    add_blocks_vertically(map1, 4, 11, 49, TYPE_WALL);
    add_blocks_horizontally(map1, 7, 51, 54, TYPE_WALL);
    add_blocks_horizontally(map1, 8, 51, 54, TYPE_WALL);

    // add coins
    add_block(map1, 18, 1, TYPE_COIN);
    add_block(map1, 18, 58, TYPE_COIN);
    
    add_block(map1, 16, 13, TYPE_COIN);
    add_block(map1, 16, 46, TYPE_COIN);
    
    add_block(map1, 12, 6, TYPE_COIN);
    add_block(map1, 12, 53, TYPE_COIN);
    
    add_block(map1, 2, 16, TYPE_COIN);
    add_block(map1, 2, 43, TYPE_COIN);
    
    add_block(map1, 6, 25, TYPE_COIN);
    add_block(map1, 9, 25, TYPE_COIN);
    add_block(map1, 6, 34, TYPE_COIN);
    add_block(map1, 9, 34, TYPE_COIN);

    /* Map 2 */
    map *map2 = new map;

    // add entrance and exit
    add_blocks_vertically(map2, 16, 17, 0, TYPE_ENTRANCE);
    add_blocks_vertically(map2, 16, 17, 59, TYPE_EXIT);

    // add walls
    add_blocks_vertically(map2, 1, 4, 29, TYPE_WALL);
    add_blocks_vertically(map2, 1, 4, 30, TYPE_WALL);
    add_blocks_horizontally(map2, 5, 24, 39, TYPE_WALL);
    add_blocks_vertically(map2, 6, 12, 24, TYPE_WALL);
    add_blocks_vertically(map2, 6, 12, 25, TYPE_WALL);
    
    add_blocks_vertically(map2, 7, 13, 29, TYPE_WALL);
    add_blocks_vertically(map2, 7, 13, 30, TYPE_WALL);

    add_blocks_horizontally(map2, 15, 26, 33, TYPE_WALL);
    add_blocks_vertically(map2, 14, 15, 24, TYPE_WALL);
    add_blocks_vertically(map2, 14, 15, 25, TYPE_WALL);
    add_blocks_vertically(map2, 12, 15, 34, TYPE_WALL);
    add_blocks_vertically(map2, 12, 15, 35, TYPE_WALL);
    
    add_blocks_vertically(map2, 7, 10, 34, TYPE_WALL);
    add_blocks_vertically(map2, 7, 10, 35, TYPE_WALL);
    add_blocks_horizontally(map2, 10, 36, 37, TYPE_WALL);
    add_blocks_horizontally(map2, 10, 40, 43, TYPE_WALL);
    add_blocks_vertically(map2, 7, 18, 38, TYPE_WALL);
    add_blocks_vertically(map2, 7, 18, 39, TYPE_WALL);
    add_blocks_horizontally(map2, 7, 40, 43, TYPE_WALL);
    add_blocks_vertically(map2, 3, 6, 42, TYPE_WALL);
    add_blocks_vertically(map2, 3, 6, 43, TYPE_WALL);
    
    add_blocks_horizontally(map2, 17, 3, 35, TYPE_WALL);
    add_blocks_vertically(map2, 14, 16, 20, TYPE_WALL);
    add_blocks_vertically(map2, 14, 16, 21, TYPE_WALL);
    
    add_blocks_vertically(map2, 14, 15, 16, TYPE_WALL);
    add_blocks_vertically(map2, 14, 15, 17, TYPE_WALL);
    add_blocks_horizontally(map2, 14, 10, 15, TYPE_WALL);
    add_blocks_horizontally(map2, 15, 3, 11, TYPE_WALL);
    
    add_blocks_vertically(map2, 5, 12, 20, TYPE_WALL);
    add_blocks_vertically(map2, 5, 12, 21, TYPE_WALL);
    add_blocks_horizontally(map2, 9, 18, 19, TYPE_WALL);
    
    add_blocks_horizontally(map2, 1, 14, 22, TYPE_WALL);
    
    add_blocks_vertically(map2, 3, 12, 14, TYPE_WALL);
    add_blocks_vertically(map2, 3, 12, 15, TYPE_WALL);
    add_blocks_horizontally(map2, 3, 16, 26, TYPE_WALL);
    add_blocks_horizontally(map2, 2, 25, 26, TYPE_WALL);
    
    add_blocks_horizontally(map2, 2, 3, 11, TYPE_WALL);
    add_blocks_vertically(map2, 3, 12, 3, TYPE_WALL);
    add_blocks_vertically(map2, 3, 12, 4, TYPE_WALL);
    
    add_blocks_horizontally(map2, 4, 9, 11, TYPE_WALL);
    add_blocks_vertically(map2, 4, 6, 7, TYPE_WALL);
    add_blocks_vertically(map2, 4, 6, 8, TYPE_WALL);
    add_blocks_horizontally(map2, 6, 9, 11, TYPE_WALL);
    add_blocks_vertically(map2, 7, 8, 10, TYPE_WALL);
    add_blocks_vertically(map2, 7, 8, 11, TYPE_WALL);
    add_blocks_horizontally(map2, 8, 7, 9, TYPE_WALL);
    add_blocks_vertically(map2, 9, 12, 7, TYPE_WALL);
    add_blocks_vertically(map2, 9, 12, 8, TYPE_WALL);

    add_blocks_vertically(map2, 10, 12, 11, TYPE_WALL);
    
    add_blocks_vertically(map2, 12, 17, 42, TYPE_WALL);
    add_blocks_vertically(map2, 12, 17, 43, TYPE_WALL);
    add_blocks_horizontally(map2, 12, 44, 52, TYPE_WALL);
    add_blocks_vertically(map2, 12, 14, 51, TYPE_WALL);
    add_blocks_vertically(map2, 12, 14, 52, TYPE_WALL);

    add_blocks_horizontally(map2, 17, 46, 56, TYPE_WALL);
    add_blocks_vertically(map2, 7, 16, 55, TYPE_WALL);
    add_blocks_vertically(map2, 7, 16, 56, TYPE_WALL);
    add_blocks_vertically(map2, 15, 17, 46, TYPE_WALL);
    add_blocks_vertically(map2, 15, 17, 47, TYPE_WALL);
    add_blocks_horizontally(map2, 14, 46, 48, TYPE_WALL);
    add_blocks_horizontally(map2, 7, 52, 54, TYPE_WALL);
    add_blocks_vertically(map2, 6, 7, 51, TYPE_WALL);
    add_blocks_vertically(map2, 6, 7, 50, TYPE_WALL);
    
    add_blocks_horizontally(map2, 10, 46, 52, TYPE_WALL);
    add_blocks_horizontally(map2, 9, 46, 52, TYPE_WALL);
    add_blocks_vertically(map2, 6, 8, 46, TYPE_WALL);
    add_blocks_vertically(map2, 6, 8, 47, TYPE_WALL);
    
    add_blocks_vertically(map2, 2, 5, 55, TYPE_WALL);
    add_blocks_vertically(map2, 2, 5, 56, TYPE_WALL);
    add_blocks_horizontally(map2, 2, 46, 54, TYPE_WALL);

    add_blocks_horizontally(map2, 4, 46, 52, TYPE_WALL);
    
    add_blocks_horizontally(map2, 3, 33, 39, TYPE_WALL);
    add_blocks_horizontally(map2, 2, 33, 39, TYPE_WALL);

    // add coins
    add_block(map2, 1, 28, TYPE_COIN);
    add_block(map2, 1, 31, TYPE_COIN);
    add_block(map2, 5, 9, TYPE_COIN);
    add_block(map2, 18, 37, TYPE_COIN);
    add_block(map2, 9, 37, TYPE_COIN);
    add_block(map2, 9, 40, TYPE_COIN);
    add_block(map2, 15, 15, TYPE_COIN);
    add_block(map2, 3, 54, TYPE_COIN);
    add_block(map2, 16, 48, TYPE_COIN);
    add_block(map2, 13, 50, TYPE_COIN);
    add_block(map2, 8, 54, TYPE_COIN);
    add_block(map2, 7, 22, TYPE_COIN);

    /* Map 3 */
    map *map3 = new map;

    // add entrance and exit
    add_blocks_horizontally(map3, 19, 3, 6, TYPE_ENTRANCE);
    add_blocks_horizontally(map3, 19, 53, 56, TYPE_EXIT);

    // add walls
    add_blocks_vertically(map3, 4, 18, 29, TYPE_WALL);
    add_blocks_vertically(map3, 4, 18, 30, TYPE_WALL);

    add_blocks_vertically(map3, 2, 3, 25, TYPE_WALL);
    add_blocks_vertically(map3, 2, 3, 26, TYPE_WALL);
    add_blocks_horizontally(map3, 2, 27, 32, TYPE_WALL);
    add_blocks_vertically(map3, 2, 3, 33, TYPE_WALL);
    add_blocks_vertically(map3, 2, 3, 34, TYPE_WALL);

    // left
    add_blocks_vertically(map3, 14, 18, 9, TYPE_WALL);
    add_blocks_vertically(map3, 14, 18, 10, TYPE_WALL);
    
    add_blocks_vertically(map3, 13, 16, 13, TYPE_WALL);
    add_blocks_vertically(map3, 13, 16, 14, TYPE_WALL);
    add_blocks_horizontally(map3, 17, 13, 18, TYPE_WALL);
    add_blocks_vertically(map3, 11, 16, 17, TYPE_WALL);
    add_blocks_vertically(map3, 11, 16, 18, TYPE_WALL);
    add_blocks_horizontally(map3, 12, 1, 14, TYPE_WALL);
    add_blocks_horizontally(map3, 10, 1, 18, TYPE_WALL);

    add_blocks_vertically(map3, 9, 14, 21, TYPE_WALL);
    add_blocks_vertically(map3, 9, 14, 22, TYPE_WALL);
    add_blocks_horizontally(map3, 8, 21, 24, TYPE_WALL);
    add_blocks_vertically(map3, 6, 16, 25, TYPE_WALL);
    add_blocks_vertically(map3, 6, 16, 26, TYPE_WALL);
    
    add_blocks_horizontally(map3, 8, 5, 18, TYPE_WALL);
    add_blocks_vertically(map3, 2, 7, 17, TYPE_WALL);
    add_blocks_vertically(map3, 2, 7, 18, TYPE_WALL);

    add_blocks_horizontally(map3, 6, 7, 14, TYPE_WALL);
    add_blocks_vertically(map3, 3, 5, 13, TYPE_WALL);
    add_blocks_vertically(map3, 3, 5, 14, TYPE_WALL);

    add_block(map3, 4, 9, TYPE_WALL);
    add_block(map3, 4, 10, TYPE_WALL);

    // right
    add_blocks_vertically(map3, 6, 16, 33, TYPE_WALL);
    add_blocks_vertically(map3, 6, 16, 34, TYPE_WALL);
    add_blocks_horizontally(map3, 8, 33, 38, TYPE_WALL);
    add_blocks_vertically(map3, 9, 14, 37, TYPE_WALL);
    add_blocks_vertically(map3, 9, 14, 38, TYPE_WALL);

    add_blocks_vertically(map3, 11, 16, 41, TYPE_WALL);
    add_blocks_vertically(map3, 11, 16, 42, TYPE_WALL);
    add_blocks_horizontally(map3, 17, 41, 46, TYPE_WALL);
    add_blocks_vertically(map3, 13, 16, 45, TYPE_WALL);
    add_blocks_vertically(map3, 13, 16, 46, TYPE_WALL);
    add_blocks_horizontally(map3, 10, 41, 58, TYPE_WALL);
    add_blocks_horizontally(map3, 12, 45, 58, TYPE_WALL);

    add_blocks_vertically(map3, 14, 18, 49, TYPE_WALL);
    add_blocks_vertically(map3, 14, 18, 50, TYPE_WALL);

    add_blocks_horizontally(map3, 8, 41, 54, TYPE_WALL);
    add_blocks_vertically(map3, 2, 7, 41, TYPE_WALL);
    add_blocks_vertically(map3, 2, 7, 42, TYPE_WALL);

    add_blocks_horizontally(map3, 6, 45, 52, TYPE_WALL);
    add_blocks_vertically(map3, 3, 5, 45, TYPE_WALL);
    add_blocks_vertically(map3, 3, 5, 46, TYPE_WALL);

    add_block(map3, 4, 50, TYPE_WALL);
    add_block(map3, 4, 49, TYPE_WALL);

    // add coins
    add_block(map3, 12, 20, TYPE_COIN);
    add_block(map3, 12, 39, TYPE_COIN);
    add_block(map3, 9, 24, TYPE_COIN);
    add_block(map3, 9, 35, TYPE_COIN);
    add_block(map3, 7, 16, TYPE_COIN);
    add_block(map3, 7, 43, TYPE_COIN);
    add_block(map3, 5, 12, TYPE_COIN);
    add_block(map3, 5, 47, TYPE_COIN);
    add_block(map3, 1, 1, TYPE_COIN);
    add_block(map3, 1, 58, TYPE_COIN);
    add_block(map3, 3, 30, TYPE_COIN);

	/* Map 4 */
	map *map4 = new map;
	
    // Entrance and exit
	add_blocks_vertically(map4, 9, 10, 0, TYPE_ENTRANCE);
	add_blocks_vertically(map4, 9, 10, 59, TYPE_EXIT);

	// Walls
	// Left
	add_blocks_vertically(map4, 0, 8, 1, TYPE_WALL);
	add_blocks_vertically(map4, 11, 20, 1, TYPE_WALL);

	add_blocks_vertically(map4, 2, 13, 4, TYPE_WALL);
	add_blocks_vertically(map4, 2, 13, 5, TYPE_WALL);

	add_blocks_horizontally(map4, 2, 5, 11, TYPE_WALL);
	add_blocks_horizontally(map4, 3, 5, 11, TYPE_WALL);
	add_blocks_vertically(map4, 4, 7, 8, TYPE_WALL);
	add_blocks_vertically(map4, 4, 7, 9, TYPE_WALL);

	add_blocks_horizontally(map4, 15, 4, 8, TYPE_WALL);
	add_block(map4, 16, 6, TYPE_WALL);
	add_blocks_horizontally(map4, 17, 4, 8, TYPE_WALL);

	add_blocks_horizontally(map4, 13, 8, 13, TYPE_WALL);
	add_blocks_vertically(map4, 9, 12, 10, TYPE_WALL);
	add_blocks_vertically(map4, 9, 12, 11, TYPE_WALL);

	add_blocks_vertically(map4, 15, 18, 11, TYPE_WALL);
	add_blocks_vertically(map4, 15, 18, 12, TYPE_WALL);
	add_blocks_vertically(map4, 15, 18, 13, TYPE_WALL);

	add_blocks_vertically(map4, 2, 3, 15, TYPE_WALL);
	add_blocks_vertically(map4, 2, 3, 16, TYPE_WALL);
	add_blocks_vertically(map4, 2, 3, 17, TYPE_WALL);
	add_blocks_vertically(map4, 2, 3, 18, TYPE_WALL);
	add_blocks_horizontally(map4, 4, 13, 20, TYPE_WALL);
	add_blocks_horizontally(map4, 5, 13, 20, TYPE_WALL);
	add_blocks_horizontally(map4, 6, 13, 20, TYPE_WALL);

	add_blocks_horizontally(map4, 9, 14, 20, TYPE_WALL);
	add_blocks_horizontally(map4, 10, 14, 20, TYPE_WALL);
	add_blocks_horizontally(map4, 11, 14, 20, TYPE_WALL);
	add_blocks_horizontally(map4, 8, 16, 18, TYPE_WALL);

	// Center
	add_blocks_vertically(map4, 5, 9, 29, TYPE_WALL);
	add_blocks_vertically(map4, 4, 10, 30, TYPE_WALL);
	add_blocks_vertically(map4, 4, 10, 31, TYPE_WALL);
	add_blocks_vertically(map4, 5, 9, 32, TYPE_WALL);
	add_blocks_horizontally(map4, 3, 23, 38, TYPE_WALL);
	add_blocks_horizontally(map4, 11, 23, 38, TYPE_WALL);

	add_blocks_horizontally(map4, 5, 33, 35, TYPE_WALL);
	add_blocks_horizontally(map4, 9, 33, 35, TYPE_WALL);
	add_block(map4, 6, 35, TYPE_WALL);
	add_block(map4, 8, 35, TYPE_WALL);
	add_blocks_vertically(map4, 4, 6, 38, TYPE_WALL);
	add_blocks_vertically(map4, 8, 10, 38, TYPE_WALL);

	add_blocks_horizontally(map4, 5, 26, 28, TYPE_WALL);
	add_blocks_horizontally(map4, 9, 26, 28, TYPE_WALL);
	add_block(map4, 6, 26, TYPE_WALL);
	add_block(map4, 8, 26, TYPE_WALL);
	add_blocks_vertically(map4, 4, 6, 23, TYPE_WALL);
	add_blocks_vertically(map4, 8, 10, 23, TYPE_WALL);

	// Center top
	add_block(map4, 1, 25, TYPE_WALL);
	add_block(map4, 2, 30, TYPE_WALL);
	add_block(map4, 1, 36, TYPE_WALL);

	// Center bottom
	add_blocks_horizontally(map4, 13, 16, 48, TYPE_WALL);
	add_blocks_horizontally(map4, 14, 16, 48, TYPE_WALL);
	add_block(map4, 15, 20, TYPE_WALL);
	add_block(map4, 15, 28, TYPE_WALL);
	add_block(map4, 15, 36, TYPE_WALL);
	add_block(map4, 15, 44, TYPE_WALL);
	add_block(map4, 16, 24, TYPE_WALL);
	add_block(map4, 16, 32, TYPE_WALL);
	add_blocks_horizontally(map4, 17, 16, 48, TYPE_WALL);
	add_blocks_horizontally(map4, 18, 16, 48, TYPE_WALL);

	// Right
	add_blocks_vertically(map4, 3, 11, 41, TYPE_WALL);
	add_blocks_vertically(map4, 3, 11, 42, TYPE_WALL);
	add_blocks_vertically(map4, 2, 11, 43, TYPE_WALL);
	add_blocks_vertically(map4, 2, 11, 44, TYPE_WALL);
	add_blocks_vertically(map4, 2, 11, 45, TYPE_WALL);
	add_blocks_vertically(map4, 2, 11, 46, TYPE_WALL);
	add_blocks_vertically(map4, 2, 11, 47, TYPE_WALL);
	add_blocks_vertically(map4, 3, 7, 48, TYPE_WALL);
	add_blocks_vertically(map4, 3, 7, 49, TYPE_WALL);

	add_blocks_vertically(map4, 2, 12, 53, TYPE_WALL);
	add_blocks_vertically(map4, 2, 12, 54, TYPE_WALL);
	add_blocks_vertically(map4, 2, 10, 55, TYPE_WALL);
	add_blocks_vertically(map4, 9, 12, 56, TYPE_WALL);
	add_blocks_vertically(map4, 2, 10, 52, TYPE_WALL);
	add_blocks_vertically(map4, 9, 12, 51, TYPE_WALL);


	add_blocks_horizontally(map4, 15, 51, 56, TYPE_WALL);
	add_blocks_horizontally(map4, 16, 51, 56, TYPE_WALL);
	add_blocks_horizontally(map4, 14, 53, 54, TYPE_WALL);
	add_blocks_horizontally(map4, 17, 53, 54, TYPE_WALL);

	// Coins
	add_block(map4, 7, 3, TYPE_COIN);
	add_block(map4, 12, 3, TYPE_COIN);
	add_block(map4, 4, 32, TYPE_COIN);
	add_block(map4, 6, 33, TYPE_COIN);
	add_block(map4, 8, 33, TYPE_COIN);
	add_block(map4, 6, 28, TYPE_COIN);
	add_block(map4, 8, 28, TYPE_COIN);
	add_block(map4, 4, 29, TYPE_COIN);
	add_block(map4, 10, 32, TYPE_COIN);
	add_block(map4, 10, 29, TYPE_COIN);
	add_block(map4, 16, 26, TYPE_COIN);
	add_block(map4, 16, 41, TYPE_COIN);
	add_block(map4, 18, 6, TYPE_COIN);
	add_block(map4, 16, 7, TYPE_COIN);
	add_block(map4, 12, 9, TYPE_COIN);
	add_block(map4, 12, 21, TYPE_COIN);
	add_block(map4, 12, 28, TYPE_COIN);
	add_block(map4, 12, 33, TYPE_COIN);
	add_block(map4, 12, 40, TYPE_COIN);
	add_block(map4, 8, 9, TYPE_COIN);
	add_block(map4, 8, 14, TYPE_COIN);
	add_block(map4, 1, 6, TYPE_COIN);
	add_block(map4, 1, 16, TYPE_COIN);
	add_block(map4, 1, 30, TYPE_COIN);
	add_block(map4, 1, 45, TYPE_COIN);
	add_block(map4, 1, 54, TYPE_COIN);
	add_block(map4, 8, 51, TYPE_COIN);
	add_block(map4, 5, 57, TYPE_COIN);
	add_block(map4, 18, 56, TYPE_COIN);
	add_block(map4, 17, 51, TYPE_COIN);
	add_block(map4, 14, 52, TYPE_COIN);
	add_block(map4, 14, 55, TYPE_COIN);
	add_block(map4, 10, 57, TYPE_COIN);
	add_block(map4, 12, 48, TYPE_COIN);
	add_block(map4, 4, 51, TYPE_COIN);
	add_block(map4, 14, 52, TYPE_COIN);
	add_block(map4, 18, 15, TYPE_COIN);
	add_block(map4, 15, 32, TYPE_COIN);
	add_block(map4, 15, 46, TYPE_COIN);
	add_block(map4, 15, 21, TYPE_COIN);
	add_block(map4, 3, 40, TYPE_COIN);
	add_block(map4, 7, 40, TYPE_COIN);
	add_block(map4, 7, 21, TYPE_COIN);
	add_block(map4, 3, 19, TYPE_COIN);
	add_block(map4, 14, 15, TYPE_COIN);
	add_block(map4, 4, 6, TYPE_COIN);
	add_block(map4, 4, 11, TYPE_COIN);


	/* Map 5 */
	map *map5 = new map;

	// Entrance and exit
	add_blocks_vertically(map5, 9, 10, 0, TYPE_ENTRANCE);
	add_blocks_vertically(map5, 9, 10, 59, TYPE_EXIT);

	// Walls
	// Left
	add_blocks_vertically(map5, 2, 6, 3, TYPE_WALL);
	add_blocks_vertically(map5, 2, 6, 4, TYPE_WALL);
	add_blocks_horizontally(map5, 2, 4, 8, TYPE_WALL);
	add_blocks_horizontally(map5, 3, 4, 8, TYPE_WALL);

	add_blocks_horizontally(map5, 5, 7, 10, TYPE_WALL);
	add_blocks_horizontally(map5, 6, 7, 10, TYPE_WALL);
	add_blocks_vertically(map5, 2, 6, 11, TYPE_WALL);
	add_blocks_vertically(map5, 2, 6, 12, TYPE_WALL);

	add_blocks_vertically(map5, 2, 6, 15, TYPE_WALL);
	add_blocks_vertically(map5, 2, 6, 16, TYPE_WALL);
	add_blocks_vertically(map5, 2, 6, 17, TYPE_WALL);

	add_blocks_horizontally(map5, 2, 18, 27, TYPE_WALL);
	add_blocks_horizontally(map5, 3, 18, 27, TYPE_WALL);

	add_blocks_vertically(map5, 8, 16, 3, TYPE_WALL);
	add_blocks_vertically(map5, 8, 16, 4, TYPE_WALL);
	add_block(map5, 10, 5, TYPE_WALL);
	add_block(map5, 14, 5, TYPE_WALL);

	add_blocks_vertically(map5, 8, 16, 8, TYPE_WALL);
	add_blocks_vertically(map5, 8, 16, 9, TYPE_WALL);
	add_block(map5, 8, 10, TYPE_WALL);
	add_block(map5, 10, 10, TYPE_WALL);
	add_block(map5, 15, 10, TYPE_WALL);

	add_blocks_vertically(map5, 8, 16, 13, TYPE_WALL);
	add_blocks_vertically(map5, 8, 16, 14, TYPE_WALL);
	add_blocks_vertically(map5, 8, 15, 15, TYPE_WALL);
	add_blocks_vertically(map5, 8, 15, 16, TYPE_WALL);
	add_blocks_vertically(map5, 8, 16, 17, TYPE_WALL);
	add_block(map5, 11, 12, TYPE_WALL);
	add_block(map5, 12, 12, TYPE_WALL);
	add_block(map5, 13, 12, TYPE_WALL);

	add_blocks_horizontally(map5, 18, 3, 17, TYPE_WALL);

	// Center
	add_blocks_horizontally(map5, 9, 20, 24, TYPE_WALL);
	add_blocks_horizontally(map5, 10, 20, 24, TYPE_WALL);
	add_blocks_horizontally(map5, 11, 20, 24, TYPE_WALL);
	add_blocks_vertically(map5, 5, 15, 25, TYPE_WALL);
	add_blocks_vertically(map5, 5, 15, 26, TYPE_WALL);
	add_blocks_vertically(map5, 5, 15, 27, TYPE_WALL);
	add_blocks_vertically(map5, 9, 11, 28, TYPE_WALL);
	add_blocks_vertically(map5, 9, 11, 29, TYPE_WALL);

	add_blocks_horizontally(map5, 9, 37, 41, TYPE_WALL);
	add_blocks_horizontally(map5, 10, 37, 41, TYPE_WALL);
	add_blocks_horizontally(map5, 11, 37, 41, TYPE_WALL);
	add_blocks_vertically(map5, 9, 11, 32, TYPE_WALL);
	add_blocks_vertically(map5, 9, 11, 33, TYPE_WALL);
	add_blocks_vertically(map5, 5, 15, 34, TYPE_WALL);
	add_blocks_vertically(map5, 5, 15, 35, TYPE_WALL);
	add_blocks_vertically(map5, 5, 15, 36, TYPE_WALL);

	add_blocks_vertically(map5, 5, 7, 30, TYPE_WALL);
	add_blocks_vertically(map5, 5, 7, 31, TYPE_WALL);

	add_blocks_vertically(map5, 13, 15, 30, TYPE_WALL);
	add_blocks_vertically(map5, 13, 15, 31, TYPE_WALL);

	add_blocks_vertically(map5, 13, 17, 20, TYPE_WALL);
	add_blocks_vertically(map5, 13, 17, 21, TYPE_WALL);
	add_blocks_vertically(map5, 13, 17, 22, TYPE_WALL);

	add_blocks_vertically(map5, 13, 17, 39, TYPE_WALL);
	add_blocks_vertically(map5, 13, 17, 40, TYPE_WALL);
	add_blocks_vertically(map5, 13, 17, 41, TYPE_WALL);

	add_blocks_vertically(map5, 5, 7, 20, TYPE_WALL);
	add_blocks_vertically(map5, 5, 7, 21, TYPE_WALL);
	add_blocks_vertically(map5, 5, 7, 22, TYPE_WALL);

	add_blocks_vertically(map5, 5, 7, 39, TYPE_WALL);
	add_blocks_vertically(map5, 5, 7, 40, TYPE_WALL);
	add_blocks_vertically(map5, 5, 7, 41, TYPE_WALL);

	// Center top
	add_blocks_horizontally(map5, 2, 30, 35, TYPE_WALL);
	add_blocks_horizontally(map5, 3, 30, 41, TYPE_WALL);

	// Center bottom
	add_blocks_horizontally(map5, 17, 25, 36, TYPE_WALL);
	add_blocks_horizontally(map5, 18, 25, 36, TYPE_WALL);

	// Right
	add_blocks_horizontally(map5, 1, 38, 44, TYPE_WALL);

	add_blocks_horizontally(map5, 3, 44, 45, TYPE_WALL);

	add_blocks_vertically(map5, 2, 5, 56, TYPE_WALL);
	add_blocks_vertically(map5, 2, 5, 55, TYPE_WALL);
	add_blocks_horizontally(map5, 2, 51, 54, TYPE_WALL);
	add_blocks_horizontally(map5, 3, 51, 54, TYPE_WALL);

	add_blocks_vertically(map5, 2, 6, 48, TYPE_WALL);
	add_blocks_vertically(map5, 2, 6, 47, TYPE_WALL);
	add_blocks_horizontally(map5, 5, 49, 52, TYPE_WALL);
	add_blocks_horizontally(map5, 6, 49, 52, TYPE_WALL);

	add_blocks_vertically(map5, 5, 9, 44, TYPE_WALL);
	add_blocks_vertically(map5, 5, 9, 45, TYPE_WALL);
	add_blocks_vertically(map5, 5, 9, 46, TYPE_WALL);
	add_blocks_horizontally(map5, 8, 47, 52, TYPE_WALL);
	add_blocks_horizontally(map5, 9, 47, 52, TYPE_WALL);

	add_blocks_vertically(map5, 7, 12, 55, TYPE_WALL);
	add_blocks_vertically(map5, 7, 12, 56, TYPE_WALL);
	add_blocks_horizontally(map5, 11, 44, 56, TYPE_WALL);
	add_blocks_horizontally(map5, 12, 44, 56, TYPE_WALL);

	add_blocks_horizontally(map5, 14, 44, 45, TYPE_WALL);
	add_blocks_horizontally(map5, 14, 55, 56, TYPE_WALL);

	add_blocks_horizontally(map5, 14, 48, 52, TYPE_WALL);
	add_blocks_horizontally(map5, 15, 48, 52, TYPE_WALL);
	add_blocks_horizontally(map5, 16, 44, 56, TYPE_WALL);
	add_blocks_horizontally(map5, 17, 44, 56, TYPE_WALL);

	// Coins
	add_block(map5, 9, 2, TYPE_COIN);
	add_block(map5, 9, 57, TYPE_COIN);
	add_block(map5, 1, 1, TYPE_COIN);
	add_block(map5, 1, 19, TYPE_COIN);
	add_block(map5, 1, 28, TYPE_COIN);
	add_block(map5, 1, 58, TYPE_COIN);
	add_block(map5, 18, 58, TYPE_COIN);
	add_block(map5, 18, 1, TYPE_COIN);
	add_block(map5, 4, 13, TYPE_COIN);
	add_block(map5, 7, 8, TYPE_COIN);
	add_block(map5, 10, 19, TYPE_COIN);
	add_block(map5, 18, 19, TYPE_COIN);
	add_block(map5, 4, 18, TYPE_COIN);
	add_block(map5, 4, 28, TYPE_COIN);
	add_block(map5, 4, 41, TYPE_COIN);
	add_block(map5, 13, 5, TYPE_COIN);
	add_block(map5, 10, 42, TYPE_COIN);
	add_block(map5, 10, 54, TYPE_COIN);
	add_block(map5, 15, 53, TYPE_COIN);
	add_block(map5, 18, 40, TYPE_COIN);
	add_block(map5, 15, 42, TYPE_COIN);
	add_block(map5, 16, 28, TYPE_COIN);
	add_block(map5, 4, 54, TYPE_COIN);
	add_block(map5, 1, 45, TYPE_COIN);
	add_block(map5, 16, 33, TYPE_COIN);
	add_block(map5, 14, 12, TYPE_COIN);
	add_block(map5, 12, 24, TYPE_COIN);
	add_block(map5, 8, 24, TYPE_COIN);
	add_block(map5, 8, 37, TYPE_COIN);
	add_block(map5, 12, 37, TYPE_COIN);
	add_block(map5, 8, 28, TYPE_COIN);
	add_block(map5, 8, 33, TYPE_COIN);
	add_block(map5, 12, 28, TYPE_COIN);
	add_block(map5, 12, 33, TYPE_COIN);
	add_block(map5, 4, 33, TYPE_COIN);
	add_block(map5, 18, 48, TYPE_COIN);
	add_block(map5, 13, 50, TYPE_COIN);
	add_block(map5, 7, 47, TYPE_COIN);
	add_block(map5, 4, 5, TYPE_COIN);
	add_block(map5, 17, 11, TYPE_COIN);
	add_block(map5, 10, 12, TYPE_COIN);
	add_block(map5, 7, 14, TYPE_COIN);
	add_block(map5, 2, 37, TYPE_COIN);
	add_block(map5, 1, 10, TYPE_COIN);

	/* Map 6 */
	map *map6 = new map;

	// Entrance and exit
	add_blocks_vertically(map6, 9, 10, 0, TYPE_ENTRANCE);
	add_blocks_vertically(map6, 9, 10, 59, TYPE_EXIT);

	// Left
	add_blocks_horizontally(map6, 2, 3, 8, TYPE_WALL);
	add_blocks_horizontally(map6, 3, 3, 8, TYPE_WALL);
	add_blocks_vertically(map6, 4, 6, 7, TYPE_WALL);
	add_blocks_vertically(map6, 4, 6, 8, TYPE_WALL);
	add_blocks_horizontally(map6, 5, 9, 15, TYPE_WALL);
	add_blocks_horizontally(map6, 6, 9, 15, TYPE_WALL);

	add_blocks_horizontally(map6, 2, 11, 15, TYPE_WALL);
	add_blocks_horizontally(map6, 3, 11, 15, TYPE_WALL);

	add_blocks_horizontally(map6, 8, 3, 19, TYPE_WALL);
	add_blocks_horizontally(map6, 9, 3, 19, TYPE_WALL);
	add_blocks_horizontally(map6, 10, 3, 19, TYPE_WALL);
	add_blocks_horizontally(map6, 11, 3, 19, TYPE_WALL);
	add_blocks_vertically(map6, 5, 7, 3, TYPE_WALL);
	add_blocks_vertically(map6, 5, 7, 4, TYPE_WALL);

	add_blocks_horizontally(map6, 13, 3, 13, TYPE_WALL);
	add_blocks_horizontally(map6, 14, 3, 13, TYPE_WALL);
	add_blocks_vertically(map6, 15, 16, 12, TYPE_WALL);
	add_blocks_vertically(map6, 15, 16, 13, TYPE_WALL);
	add_blocks_horizontally(map6, 15, 14, 19, TYPE_WALL);
	add_blocks_horizontally(map6, 16, 14, 19, TYPE_WALL);

	add_blocks_horizontally(map6, 13, 16, 19, TYPE_WALL);

	add_blocks_horizontally(map6, 18, 3, 14, TYPE_WALL);
	add_blocks_horizontally(map6, 17, 3, 9, TYPE_WALL);
	add_blocks_horizontally(map6, 16, 3, 8, TYPE_WALL);

	// Center (from top to bottom)
	add_blocks_horizontally(map6, 2, 18, 25, TYPE_WALL);
	add_block(map6, 3, 19, TYPE_WALL);
	add_block(map6, 4, 22, TYPE_WALL);
	add_blocks_horizontally(map6, 5, 18, 24, TYPE_WALL);
	add_blocks_horizontally(map6, 6, 18, 24, TYPE_WALL);
	add_blocks_horizontally(map6, 3, 25, 29, TYPE_WALL);
	add_blocks_horizontally(map6, 4, 25, 29, TYPE_WALL);

	add_blocks_vertically(map6, 2, 6, 30, TYPE_WALL);
	add_blocks_horizontally(map6, 2, 31, 38, TYPE_WALL);
	add_blocks_horizontally(map6, 6, 31, 38, TYPE_WALL);
	add_block(map6, 3, 38, TYPE_WALL);
	add_block(map6, 5, 38, TYPE_WALL);
	add_block(map6, 4, 32, TYPE_WALL);
	add_block(map6, 4, 35, TYPE_WALL);

	add_blocks_horizontally(map6, 10, 22, 38, TYPE_WALL);
	add_blocks_horizontally(map6, 11, 22, 38, TYPE_WALL);
	add_blocks_vertically(map6, 8, 9, 22, TYPE_WALL);
	add_blocks_vertically(map6, 8, 9, 23, TYPE_WALL);
	add_blocks_vertically(map6, 8, 9, 24, TYPE_WALL);
	add_blocks_vertically(map6, 8, 9, 36, TYPE_WALL);
	add_blocks_vertically(map6, 8, 9, 37, TYPE_WALL);
	add_blocks_vertically(map6, 8, 9, 38, TYPE_WALL);

	add_blocks_horizontally(map6, 8, 27, 33, TYPE_WALL);
	add_blocks_vertically(map6, 6, 7, 27, TYPE_WALL);

	add_blocks_horizontally(map6, 13, 22, 38, TYPE_WALL);
	add_blocks_horizontally(map6, 14, 22, 38, TYPE_WALL);
	add_blocks_vertically(map6, 15, 16, 22, TYPE_WALL);
	add_blocks_vertically(map6, 15, 16, 23, TYPE_WALL);
	add_blocks_vertically(map6, 15, 16, 24, TYPE_WALL);
	add_blocks_vertically(map6, 15, 16, 36, TYPE_WALL);
	add_blocks_vertically(map6, 15, 16, 37, TYPE_WALL);
	add_blocks_vertically(map6, 15, 16, 38, TYPE_WALL);

	add_blocks_horizontally(map6, 18, 17, 43, TYPE_WALL);
	add_blocks_horizontally(map6, 16, 27, 33, TYPE_WALL);
	add_blocks_horizontally(map6, 17, 27, 33, TYPE_WALL);

	// Right
	add_blocks_horizontally(map6, 2, 41, 50, TYPE_WALL);
	add_blocks_horizontally(map6, 3, 41, 50, TYPE_WALL);
	add_blocks_horizontally(map6, 4, 50, 55, TYPE_WALL);
	add_blocks_horizontally(map6, 5, 41, 50, TYPE_WALL);
	add_blocks_horizontally(map6, 6, 41, 50, TYPE_WALL);
	add_blocks_vertically(map6, 2, 3, 55, TYPE_WALL);
	add_blocks_vertically(map6, 5, 6, 55, TYPE_WALL);
	add_blocks_vertically(map6, 2, 6, 56, TYPE_WALL);
	add_blocks_horizontally(map6, 2, 53, 54, TYPE_WALL);
	add_blocks_horizontally(map6, 6, 53, 54, TYPE_WALL);

	add_blocks_horizontally(map6, 8, 41, 47, TYPE_WALL);
	add_blocks_horizontally(map6, 9, 41, 47, TYPE_WALL);
	add_blocks_horizontally(map6, 10, 41, 47, TYPE_WALL);
	add_blocks_horizontally(map6, 11, 41, 47, TYPE_WALL);

	add_blocks_horizontally(map6, 8, 50, 56, TYPE_WALL);
	add_blocks_horizontally(map6, 9, 50, 56, TYPE_WALL);
	add_blocks_horizontally(map6, 10, 50, 56, TYPE_WALL);
	add_blocks_horizontally(map6, 11, 50, 56, TYPE_WALL);

	add_blocks_horizontally(map6, 13, 41, 56, TYPE_WALL);
	add_blocks_horizontally(map6, 14, 41, 56, TYPE_WALL);
	add_blocks_horizontally(map6, 15, 41, 56, TYPE_WALL);
	add_blocks_horizontally(map6, 16, 46, 52, TYPE_WALL);
	add_blocks_horizontally(map6, 17, 46, 52, TYPE_WALL);

	add_blocks_horizontally(map6, 17, 55, 56, TYPE_WALL);

	add_blocks_horizontally(map6, 17, 41, 42, TYPE_WALL);

	// Coins
	add_block(map6, 10, 2, TYPE_COIN);
	add_block(map6, 10, 57, TYPE_COIN);
	add_block(map6, 1, 3, TYPE_COIN);
	add_block(map6, 1, 58, TYPE_COIN);
	add_block(map6, 18, 58, TYPE_COIN);
	add_block(map6, 18, 1, TYPE_COIN);
	add_block(map6, 17, 10, TYPE_COIN);
	add_block(map6, 17, 26, TYPE_COIN);
	add_block(map6, 15, 30, TYPE_COIN);
	add_block(map6, 17, 34, TYPE_COIN);
	add_block(map6, 12, 30, TYPE_COIN);
	add_block(map6, 12, 36, TYPE_COIN);
	add_block(map6, 12, 24, TYPE_COIN);
	add_block(map6, 9, 30, TYPE_COIN);
	add_block(map6, 7, 28, TYPE_COIN);
	add_block(map6, 9, 35, TYPE_COIN);
	add_block(map6, 9, 25, TYPE_COIN);
	add_block(map6, 7, 5, TYPE_COIN);
	add_block(map6, 7, 15, TYPE_COIN);
	add_block(map6, 4, 9, TYPE_COIN);
	add_block(map6, 10, 20, TYPE_COIN);
	add_block(map6, 14, 14, TYPE_COIN);
	add_block(map6, 12, 17, TYPE_COIN);
	add_block(map6, 10, 2, TYPE_COIN);
	add_block(map6, 10, 39, TYPE_COIN);
	add_block(map6, 10, 48, TYPE_COIN);
	add_block(map6, 12, 54, TYPE_COIN);
	add_block(map6, 12, 43, TYPE_COIN);
	add_block(map6, 18, 44, TYPE_COIN);
	add_block(map6, 18, 51, TYPE_COIN);
	add_block(map6, 17, 18, TYPE_COIN);
	add_block(map6, 12, 8, TYPE_COIN);
	add_block(map6, 16, 53, TYPE_COIN);
	add_block(map6, 5, 57, TYPE_COIN);
	add_block(map6, 4, 49, TYPE_COIN);
	add_block(map6, 1, 44, TYPE_COIN);
	add_block(map6, 4, 40, TYPE_COIN);
	add_block(map6, 4, 36, TYPE_COIN);
	add_block(map6, 4, 33, TYPE_COIN);
	add_block(map6, 4, 24, TYPE_COIN);
	add_block(map6, 4, 20, TYPE_COIN);
	add_block(map6, 1, 18, TYPE_COIN);
	add_block(map6, 2, 29, TYPE_COIN);
	add_block(map6, 2, 26, TYPE_COIN);
	add_block(map6, 1, 34, TYPE_COIN);
	add_block(map6, 7, 43, TYPE_COIN);
	add_block(map6, 5, 54, TYPE_COIN);
	add_block(map6, 3, 54, TYPE_COIN);
	add_block(map6, 7, 52, TYPE_COIN);

    /* Create array of maps */
    maps[0] = map1;
    maps[1] = map2;
    maps[2] = map3;
    maps[3] = map4;
    maps[4] = map5;
    maps[5] = map6;
}
