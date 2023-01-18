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

    /* Map 2 */
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
    
    /* add_blocks_horizontally(map3, 1, 1, 7, TYPE_WALL);
    add_blocks_horizontally(map3, 2, 1, 4, TYPE_WALL);
    add_blocks_horizontally(map3, 3, 1, 2, TYPE_WALL); */

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

    /* Create array of maps */
    maps[0] = map1;
    maps[1] = map2;
    maps[2] = map3;
}