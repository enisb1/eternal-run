/* Includes */

#include <cstdlib>

#include "map.hpp"

/* Methods */

map *new_map() {
	map *new_map = new map;

	// set every block of the map as EMPTY_BLOCK
	for (int row = 0; row < 20; row++) {
		for (int col = 0; col < 60; col++) {
			(new_map -> blocks)[row][col] = EMPTY_BLOCK;
		}
	}

	return new_map;
}

void add_block(map *map, int y, int x, int type) {
	(map -> blocks)[y][x] = type;
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

void add_coin(map *map, int y, int x) {
	coin *new_head = new coin;
	new_head->y = y;
	new_head->x = x;
	new_head->next = map->coin_list;

	map->coin_list = new_head;
}

map *create_default_map1() {
	map *default_map1 = new_map();

	// add entrance and exit
    add_blocks_vertically(default_map1, 2, 4, 0, ENTRANCE_BLOCK);
    add_blocks_vertically(default_map1, 2, 4, 59, EXIT_BLOCK);
    
    // add walls
    add_blocks_vertically(default_map1, 4, 11, 9, WALL_BLOCK);
    add_blocks_vertically(default_map1, 4, 11, 10, WALL_BLOCK);
    add_blocks_horizontally(default_map1, 7, 5, 8, WALL_BLOCK);
    add_blocks_horizontally(default_map1, 8, 5, 8, WALL_BLOCK);
    
    add_blocks_vertically(default_map1, 10, 13, 5, WALL_BLOCK);
    add_blocks_vertically(default_map1, 10, 13, 4, WALL_BLOCK);
    add_blocks_horizontally(default_map1, 13, 6, 10, WALL_BLOCK);
    
    add_blocks_vertically(default_map1, 1, 11, 14, WALL_BLOCK);
    add_blocks_vertically(default_map1, 1, 11, 15, WALL_BLOCK);
    add_blocks_vertically(default_map1, 2, 13, 18, WALL_BLOCK);
    add_blocks_vertically(default_map1, 2, 13, 19, WALL_BLOCK);
    add_blocks_horizontally(default_map1, 13, 14, 17, WALL_BLOCK);
    
    add_blocks_horizontally(default_map1, 2, 18, 27, WALL_BLOCK);
    add_blocks_horizontally(default_map1, 2, 32, 41, WALL_BLOCK);
    add_blocks_horizontally(default_map1, 3, 16, 27, WALL_BLOCK);
    add_blocks_horizontally(default_map1, 3, 32, 43, WALL_BLOCK);
    
    add_blocks_horizontally(default_map1, 16, 1, 6, WALL_BLOCK);
    
    add_blocks_horizontally(default_map1, 15, 10, 25, WALL_BLOCK);
    add_blocks_vertically(default_map1, 16, 17, 11, WALL_BLOCK);
    add_blocks_vertically(default_map1, 16, 17, 12, WALL_BLOCK);
    
    add_blocks_horizontally(default_map1, 17, 16, 43, WALL_BLOCK);
    add_blocks_vertically(default_map1, 15, 16, 29, WALL_BLOCK);
    add_blocks_vertically(default_map1, 15, 16, 30, WALL_BLOCK);
    
    add_blocks_horizontally(default_map1, 12, 20, 36, WALL_BLOCK);
    
    add_blocks_horizontally(default_map1, 10, 23, 36, WALL_BLOCK);
    add_blocks_vertically(default_map1, 5, 9, 23, WALL_BLOCK);
    add_blocks_vertically(default_map1, 5, 9, 24, WALL_BLOCK);
    add_blocks_vertically(default_map1, 5, 9, 36, WALL_BLOCK);
    add_blocks_vertically(default_map1, 5, 9, 35, WALL_BLOCK);
    add_blocks_horizontally(default_map1, 5, 23, 28, WALL_BLOCK);
    add_blocks_horizontally(default_map1, 5, 31, 36, WALL_BLOCK);


    add_blocks_vertically(default_map1, 2, 12, 40, WALL_BLOCK);
    add_blocks_vertically(default_map1, 2, 12, 41, WALL_BLOCK);
    
    add_blocks_vertically(default_map1, 1, 11, 44, WALL_BLOCK);
    add_blocks_vertically(default_map1, 1, 11, 45, WALL_BLOCK);
    
    add_blocks_horizontally(default_map1, 13, 40, 45, WALL_BLOCK);
    
    add_blocks_horizontally(default_map1, 15, 34, 49, WALL_BLOCK);
    add_blocks_vertically(default_map1, 16, 17, 47, WALL_BLOCK);
    add_blocks_vertically(default_map1, 16, 17, 48, WALL_BLOCK);
    
    add_blocks_horizontally(default_map1, 16, 53, 58, WALL_BLOCK);
    
    add_blocks_vertically(default_map1, 10, 12, 54, WALL_BLOCK);
    add_blocks_vertically(default_map1, 10, 12, 55, WALL_BLOCK);
    add_blocks_horizontally(default_map1, 13, 49, 55, WALL_BLOCK);

    add_blocks_vertically(default_map1, 4, 11, 50, WALL_BLOCK);
    add_blocks_vertically(default_map1, 4, 11, 49, WALL_BLOCK);
    add_blocks_horizontally(default_map1, 7, 51, 54, WALL_BLOCK);
    add_blocks_horizontally(default_map1, 8, 51, 54, WALL_BLOCK);

	// add coins
	add_coin(default_map1, 4, 12);
	add_coin(default_map1, 7, 12);
	add_coin(default_map1, 10, 12);
	add_coin(default_map1, 13, 12);
	add_coin(default_map1, 4, 47);
	add_coin(default_map1, 7, 47);
	add_coin(default_map1, 10, 47);
	add_coin(default_map1, 13, 47);
	add_coin(default_map1, 4, 17);
	add_coin(default_map1, 8, 16);
	add_coin(default_map1, 12, 17);
	add_coin(default_map1, 4, 42);
	add_coin(default_map1, 8, 43);
	add_coin(default_map1, 12, 42);
	add_coin(default_map1, 11, 20);
	add_coin(default_map1, 6, 21);
	add_coin(default_map1, 11, 39);
	add_coin(default_map1, 6, 38);
	add_coin(default_map1, 1, 21);
	add_coin(default_map1, 1, 38);
	add_coin(default_map1, 1, 29);
	add_coin(default_map1, 7, 28);
	add_coin(default_map1, 8, 31);
	add_coin(default_map1, 16, 21);
	add_coin(default_map1, 16, 38);
	add_coin(default_map1, 18, 1);
    add_coin(default_map1, 18, 58);
	add_coin(default_map1, 18, 8);
	add_coin(default_map1, 18, 17);
	add_coin(default_map1, 18, 25);
	add_coin(default_map1, 18, 51);
	add_coin(default_map1, 18, 42);
	add_coin(default_map1, 18, 34);
	add_coin(default_map1, 15, 27);
	add_coin(default_map1, 15, 32);
	add_coin(default_map1, 15, 1);
	add_coin(default_map1, 15, 58);
    add_coin(default_map1, 16, 13);
    add_coin(default_map1, 16, 46);
    add_coin(default_map1, 12, 6);
    add_coin(default_map1, 12, 53);
    add_coin(default_map1, 2, 16);
    add_coin(default_map1, 2, 43);
    add_coin(default_map1, 6, 25);
    add_coin(default_map1, 9, 25);
    add_coin(default_map1, 6, 34);
    add_coin(default_map1, 9, 34);
    add_coin(default_map1, 1, 10);
    add_coin(default_map1, 2, 5);
    add_coin(default_map1, 4, 7);
    add_coin(default_map1, 5, 3);
    add_coin(default_map1, 7, 2);
    add_coin(default_map1, 10, 2);
    add_coin(default_map1, 13, 1);
	add_coin(default_map1, 1, 49);
    add_coin(default_map1, 2, 54);
    add_coin(default_map1, 4, 52);
    add_coin(default_map1, 5, 56);
    add_coin(default_map1, 7, 57);
    add_coin(default_map1, 10, 57);
    add_coin(default_map1, 13, 58);
    add_coin(default_map1, 13, 25);
    add_coin(default_map1, 13, 34);

	return default_map1;
}

map *create_default_map2() {
	map *default_map2 = new_map();

	// add entrance and exit
    add_blocks_vertically(default_map2, 16, 17, 0, ENTRANCE_BLOCK);
    add_blocks_vertically(default_map2, 16, 17, 59, EXIT_BLOCK);

    // add walls
    add_blocks_vertically(default_map2, 1, 4, 29, WALL_BLOCK);
    add_blocks_vertically(default_map2, 1, 4, 30, WALL_BLOCK);
    add_blocks_horizontally(default_map2, 5, 24, 39, WALL_BLOCK);
    add_blocks_vertically(default_map2, 6, 12, 24, WALL_BLOCK);
    add_blocks_vertically(default_map2, 6, 12, 25, WALL_BLOCK);
    
    add_blocks_vertically(default_map2, 7, 13, 29, WALL_BLOCK);
    add_blocks_vertically(default_map2, 7, 13, 30, WALL_BLOCK);

    add_blocks_horizontally(default_map2, 15, 26, 33, WALL_BLOCK);
    add_blocks_vertically(default_map2, 14, 15, 24, WALL_BLOCK);
    add_blocks_vertically(default_map2, 14, 15, 25, WALL_BLOCK);
    add_blocks_vertically(default_map2, 12, 15, 34, WALL_BLOCK);
    add_blocks_vertically(default_map2, 12, 15, 35, WALL_BLOCK);
    
    add_blocks_vertically(default_map2, 7, 10, 34, WALL_BLOCK);
    add_blocks_vertically(default_map2, 7, 10, 35, WALL_BLOCK);
    add_blocks_horizontally(default_map2, 10, 36, 37, WALL_BLOCK);
    add_blocks_horizontally(default_map2, 10, 40, 43, WALL_BLOCK);
    add_blocks_vertically(default_map2, 7, 18, 38, WALL_BLOCK);
    add_blocks_vertically(default_map2, 7, 18, 39, WALL_BLOCK);
    add_blocks_horizontally(default_map2, 7, 40, 43, WALL_BLOCK);
    add_blocks_vertically(default_map2, 3, 6, 42, WALL_BLOCK);
    add_blocks_vertically(default_map2, 3, 6, 43, WALL_BLOCK);
    
    add_blocks_horizontally(default_map2, 17, 3, 35, WALL_BLOCK);
    add_blocks_vertically(default_map2, 14, 16, 20, WALL_BLOCK);
    add_blocks_vertically(default_map2, 14, 16, 21, WALL_BLOCK);
    
    add_blocks_vertically(default_map2, 14, 15, 16, WALL_BLOCK);
    add_blocks_vertically(default_map2, 14, 15, 17, WALL_BLOCK);
    add_blocks_horizontally(default_map2, 14, 10, 15, WALL_BLOCK);
    add_blocks_horizontally(default_map2, 15, 3, 11, WALL_BLOCK);
    
    add_blocks_vertically(default_map2, 5, 12, 20, WALL_BLOCK);
    add_blocks_vertically(default_map2, 5, 12, 21, WALL_BLOCK);
    add_blocks_horizontally(default_map2, 9, 18, 19, WALL_BLOCK);
    
    add_blocks_horizontally(default_map2, 1, 14, 22, WALL_BLOCK);
    
    add_blocks_vertically(default_map2, 3, 12, 14, WALL_BLOCK);
    add_blocks_vertically(default_map2, 3, 12, 15, WALL_BLOCK);
    add_blocks_horizontally(default_map2, 3, 16, 26, WALL_BLOCK);
    add_blocks_horizontally(default_map2, 2, 25, 26, WALL_BLOCK);
    
    add_blocks_horizontally(default_map2, 2, 3, 11, WALL_BLOCK);
    add_blocks_vertically(default_map2, 3, 12, 3, WALL_BLOCK);
    add_blocks_vertically(default_map2, 3, 12, 4, WALL_BLOCK);
    
    add_blocks_horizontally(default_map2, 4, 9, 11, WALL_BLOCK);
    add_blocks_vertically(default_map2, 4, 6, 7, WALL_BLOCK);
    add_blocks_vertically(default_map2, 4, 6, 8, WALL_BLOCK);
    add_blocks_horizontally(default_map2, 6, 9, 11, WALL_BLOCK);
    add_blocks_vertically(default_map2, 7, 8, 10, WALL_BLOCK);
    add_blocks_vertically(default_map2, 7, 8, 11, WALL_BLOCK);
    add_blocks_horizontally(default_map2, 8, 7, 9, WALL_BLOCK);
    add_blocks_vertically(default_map2, 9, 12, 7, WALL_BLOCK);
    add_blocks_vertically(default_map2, 9, 12, 8, WALL_BLOCK);

    add_blocks_vertically(default_map2, 10, 12, 11, WALL_BLOCK);
    
    add_blocks_vertically(default_map2, 12, 17, 42, WALL_BLOCK);
    add_blocks_vertically(default_map2, 12, 17, 43, WALL_BLOCK);
    add_blocks_horizontally(default_map2, 12, 44, 52, WALL_BLOCK);
    add_blocks_vertically(default_map2, 12, 14, 51, WALL_BLOCK);
    add_blocks_vertically(default_map2, 12, 14, 52, WALL_BLOCK);

    add_blocks_horizontally(default_map2, 17, 46, 56, WALL_BLOCK);
    add_blocks_vertically(default_map2, 7, 16, 55, WALL_BLOCK);
    add_blocks_vertically(default_map2, 7, 16, 56, WALL_BLOCK);
    add_blocks_vertically(default_map2, 15, 17, 46, WALL_BLOCK);
    add_blocks_vertically(default_map2, 15, 17, 47, WALL_BLOCK);
    add_blocks_horizontally(default_map2, 14, 46, 48, WALL_BLOCK);
    add_blocks_horizontally(default_map2, 7, 52, 54, WALL_BLOCK);
    add_blocks_vertically(default_map2, 6, 7, 51, WALL_BLOCK);
    add_blocks_vertically(default_map2, 6, 7, 50, WALL_BLOCK);
    
    add_blocks_horizontally(default_map2, 10, 46, 52, WALL_BLOCK);
    add_blocks_horizontally(default_map2, 9, 46, 52, WALL_BLOCK);
    add_blocks_vertically(default_map2, 6, 8, 46, WALL_BLOCK);
    add_blocks_vertically(default_map2, 6, 8, 47, WALL_BLOCK);
    
    add_blocks_vertically(default_map2, 2, 5, 55, WALL_BLOCK);
    add_blocks_vertically(default_map2, 2, 5, 56, WALL_BLOCK);
    add_blocks_horizontally(default_map2, 2, 46, 54, WALL_BLOCK);

    add_blocks_horizontally(default_map2, 4, 46, 52, WALL_BLOCK);
    
    add_blocks_horizontally(default_map2, 3, 33, 39, WALL_BLOCK);
    add_blocks_horizontally(default_map2, 2, 33, 39, WALL_BLOCK);

	// add coins
	add_coin(default_map2, 1, 1);
    add_coin(default_map2, 4, 2);
    add_coin(default_map2, 8, 1);
    add_coin(default_map2, 12, 2);
    add_coin(default_map2, 1, 12);
    add_coin(default_map2, 3, 10);
    add_coin(default_map2, 7, 9);
    add_coin(default_map2, 9, 9);
    add_coin(default_map2, 11, 13);
    add_coin(default_map2, 2, 23);
    add_coin(default_map2, 4, 20);
    add_coin(default_map2, 7, 16);
    add_coin(default_map2, 12, 19);
    add_coin(default_map2, 16, 10);
    add_coin(default_map2, 18, 9);
    add_coin(default_map2, 18, 18);
    add_coin(default_map2, 18, 27);
    add_coin(default_map2, 16, 30);
    add_coin(default_map2, 14, 26);
    add_coin(default_map2, 14, 33);
    add_coin(default_map2, 8, 28);
    add_coin(default_map2, 8, 31);
    add_coin(default_map2, 4, 40);
    add_coin(default_map2, 4, 32);
    add_coin(default_map2, 4, 44);
    add_coin(default_map2, 11, 44);
    add_coin(default_map2, 14, 41);
    add_coin(default_map2, 18, 40);
    add_coin(default_map2, 18, 50);
    add_coin(default_map2, 5, 58);
    add_coin(default_map2, 10, 57);
    add_coin(default_map2, 15, 58);
    add_coin(default_map2, 1, 28);
    add_coin(default_map2, 1, 31);
    add_coin(default_map2, 5, 9);
    add_coin(default_map2, 18, 37);
    add_coin(default_map2, 9, 37);
    add_coin(default_map2, 9, 40);
    add_coin(default_map2, 15, 15);
    add_coin(default_map2, 3, 54);
    add_coin(default_map2, 16, 48);
    add_coin(default_map2, 13, 50);
    add_coin(default_map2, 8, 54);
    add_coin(default_map2, 7, 22);

	return default_map2;
}

map *create_default_map3() {
	map *default_map3 = new_map();

	// add entrance and exit
    add_blocks_horizontally(default_map3, 19, 3, 6, ENTRANCE_BLOCK);
    add_blocks_horizontally(default_map3, 19, 53, 56, EXIT_BLOCK);

    // add walls
    add_blocks_vertically(default_map3, 4, 18, 29, WALL_BLOCK);
    add_blocks_vertically(default_map3, 4, 18, 30, WALL_BLOCK);

    add_blocks_vertically(default_map3, 2, 3, 25, WALL_BLOCK);
    add_blocks_vertically(default_map3, 2, 3, 26, WALL_BLOCK);
    add_blocks_horizontally(default_map3, 2, 27, 32, WALL_BLOCK);
    add_blocks_vertically(default_map3, 2, 3, 33, WALL_BLOCK);
    add_blocks_vertically(default_map3, 2, 3, 34, WALL_BLOCK);

    add_blocks_vertically(default_map3, 14, 18, 9, WALL_BLOCK);
    add_blocks_vertically(default_map3, 14, 18, 10, WALL_BLOCK);
    
    add_blocks_vertically(default_map3, 13, 16, 13, WALL_BLOCK);
    add_blocks_vertically(default_map3, 13, 16, 14, WALL_BLOCK);
    add_blocks_horizontally(default_map3, 17, 13, 18, WALL_BLOCK);
    add_blocks_vertically(default_map3, 11, 16, 17, WALL_BLOCK);
    add_blocks_vertically(default_map3, 11, 16, 18, WALL_BLOCK);
    add_blocks_horizontally(default_map3, 12, 1, 14, WALL_BLOCK);
    add_blocks_horizontally(default_map3, 10, 1, 18, WALL_BLOCK);

    add_blocks_vertically(default_map3, 9, 14, 21, WALL_BLOCK);
    add_blocks_vertically(default_map3, 9, 14, 22, WALL_BLOCK);
    add_blocks_horizontally(default_map3, 8, 21, 24, WALL_BLOCK);
    add_blocks_vertically(default_map3, 6, 16, 25, WALL_BLOCK);
    add_blocks_vertically(default_map3, 6, 16, 26, WALL_BLOCK);
    
    add_blocks_horizontally(default_map3, 8, 5, 18, WALL_BLOCK);
    add_blocks_vertically(default_map3, 2, 7, 17, WALL_BLOCK);
    add_blocks_vertically(default_map3, 2, 7, 18, WALL_BLOCK);

    add_blocks_horizontally(default_map3, 6, 7, 14, WALL_BLOCK);
    add_blocks_vertically(default_map3, 3, 5, 13, WALL_BLOCK);
    add_blocks_vertically(default_map3, 3, 5, 14, WALL_BLOCK);

    add_block(default_map3, 4, 9, WALL_BLOCK);
    add_block(default_map3, 4, 10, WALL_BLOCK);

    add_blocks_vertically(default_map3, 6, 16, 33, WALL_BLOCK);
    add_blocks_vertically(default_map3, 6, 16, 34, WALL_BLOCK);
    add_blocks_horizontally(default_map3, 8, 33, 38, WALL_BLOCK);
    add_blocks_vertically(default_map3, 9, 14, 37, WALL_BLOCK);
    add_blocks_vertically(default_map3, 9, 14, 38, WALL_BLOCK);

    add_blocks_vertically(default_map3, 11, 16, 41, WALL_BLOCK);
    add_blocks_vertically(default_map3, 11, 16, 42, WALL_BLOCK);
    add_blocks_horizontally(default_map3, 17, 41, 46, WALL_BLOCK);
    add_blocks_vertically(default_map3, 13, 16, 45, WALL_BLOCK);
    add_blocks_vertically(default_map3, 13, 16, 46, WALL_BLOCK);
    add_blocks_horizontally(default_map3, 10, 41, 58, WALL_BLOCK);
    add_blocks_horizontally(default_map3, 12, 45, 58, WALL_BLOCK);

    add_blocks_vertically(default_map3, 14, 18, 49, WALL_BLOCK);
    add_blocks_vertically(default_map3, 14, 18, 50, WALL_BLOCK);

    add_blocks_horizontally(default_map3, 8, 41, 54, WALL_BLOCK);
    add_blocks_vertically(default_map3, 2, 7, 41, WALL_BLOCK);
    add_blocks_vertically(default_map3, 2, 7, 42, WALL_BLOCK);

    add_blocks_horizontally(default_map3, 6, 45, 52, WALL_BLOCK);
    add_blocks_vertically(default_map3, 3, 5, 45, WALL_BLOCK);
    add_blocks_vertically(default_map3, 3, 5, 46, WALL_BLOCK);

    add_block(default_map3, 4, 50, WALL_BLOCK);
    add_block(default_map3, 4, 49, WALL_BLOCK);

	// add coins
	add_coin(default_map3, 12, 20);
    add_coin(default_map3, 12, 39);
    add_coin(default_map3, 9, 24);
    add_coin(default_map3, 9, 35);
    add_coin(default_map3, 7, 16);
    add_coin(default_map3, 7, 43);
    add_coin(default_map3, 5, 12);
    add_coin(default_map3, 5, 47);
    add_coin(default_map3, 1, 1);
    add_coin(default_map3, 1, 58);
    add_coin(default_map3, 3, 30);
    add_coin(default_map3, 17, 2);
    add_coin(default_map3, 13, 9);
    add_coin(default_map3, 14, 3);
    add_coin(default_map3, 15, 7);
    add_coin(default_map3, 17, 57);
    add_coin(default_map3, 13, 50);
    add_coin(default_map3, 14, 56);
    add_coin(default_map3, 15, 52);
    add_coin(default_map3, 18, 15);
    add_coin(default_map3, 18, 28);
    add_coin(default_map3, 13, 27);
    add_coin(default_map3, 8, 28);
    add_coin(default_map3, 18, 44);
    add_coin(default_map3, 18, 31);
    add_coin(default_map3, 13, 32);
    add_coin(default_map3, 8, 31);
    add_coin(default_map3, 16, 22);
    add_coin(default_map3, 16, 37);
    add_coin(default_map3, 12, 23);
    add_coin(default_map3, 12, 36);
    add_coin(default_map3, 5, 23);
    add_coin(default_map3, 3, 21);
    add_coin(default_map3, 5, 36);
    add_coin(default_map3, 3, 38);
    add_coin(default_map3, 1, 10);
    add_coin(default_map3, 2, 5);
    add_coin(default_map3, 3, 7);
    add_coin(default_map3, 4, 3);
    add_coin(default_map3, 5, 5);
    add_coin(default_map3, 6, 1);
	add_coin(default_map3, 1, 49);
    add_coin(default_map3, 2, 54);
    add_coin(default_map3, 3, 52);
    add_coin(default_map3, 4, 56);
    add_coin(default_map3, 5, 54);
    add_coin(default_map3, 6, 58);
    add_coin(default_map3, 7, 10);
    add_coin(default_map3, 7, 49);
    add_coin(default_map3, 4, 16);
    add_coin(default_map3, 4, 43);
    add_coin(default_map3, 3, 29);

	return default_map3;
}

map *create_default_map4() {
	map *default_map4 = new_map();

	// add entrance and exit
	add_blocks_vertically(default_map4, 9, 10, 0, ENTRANCE_BLOCK);
	add_blocks_vertically(default_map4, 9, 10, 59, EXIT_BLOCK);

	// add walls
	add_blocks_vertically(default_map4, 0, 8, 1, WALL_BLOCK);
	add_blocks_vertically(default_map4, 11, 20, 1, WALL_BLOCK);

	add_blocks_vertically(default_map4, 2, 13, 4, WALL_BLOCK);
	add_blocks_vertically(default_map4, 2, 13, 5, WALL_BLOCK);

	add_blocks_horizontally(default_map4, 2, 5, 11, WALL_BLOCK);
	add_blocks_horizontally(default_map4, 3, 5, 11, WALL_BLOCK);
	add_blocks_vertically(default_map4, 4, 7, 8, WALL_BLOCK);
	add_blocks_vertically(default_map4, 4, 7, 9, WALL_BLOCK);

	add_blocks_horizontally(default_map4, 15, 4, 8, WALL_BLOCK);
	add_block(default_map4, 16, 6, WALL_BLOCK);
	add_blocks_horizontally(default_map4, 17, 4, 8, WALL_BLOCK);

	add_blocks_horizontally(default_map4, 13, 8, 13, WALL_BLOCK);
	add_blocks_vertically(default_map4, 9, 12, 10, WALL_BLOCK);
	add_blocks_vertically(default_map4, 9, 12, 11, WALL_BLOCK);

	add_blocks_vertically(default_map4, 15, 18, 11, WALL_BLOCK);
	add_blocks_vertically(default_map4, 15, 18, 12, WALL_BLOCK);
	add_blocks_vertically(default_map4, 15, 18, 13, WALL_BLOCK);

	add_blocks_vertically(default_map4, 2, 3, 15, WALL_BLOCK);
	add_blocks_vertically(default_map4, 2, 3, 16, WALL_BLOCK);
	add_blocks_vertically(default_map4, 2, 3, 17, WALL_BLOCK);
	add_blocks_vertically(default_map4, 2, 3, 18, WALL_BLOCK);
	add_blocks_horizontally(default_map4, 4, 13, 20, WALL_BLOCK);
	add_blocks_horizontally(default_map4, 5, 13, 20, WALL_BLOCK);
	add_blocks_horizontally(default_map4, 6, 13, 20, WALL_BLOCK);

	add_blocks_horizontally(default_map4, 9, 14, 20, WALL_BLOCK);
	add_blocks_horizontally(default_map4, 10, 14, 20, WALL_BLOCK);
	add_blocks_horizontally(default_map4, 11, 14, 20, WALL_BLOCK);
	add_blocks_horizontally(default_map4, 8, 16, 18, WALL_BLOCK);

	add_blocks_vertically(default_map4, 5, 9, 29, WALL_BLOCK);
	add_blocks_vertically(default_map4, 4, 10, 30, WALL_BLOCK);
	add_blocks_vertically(default_map4, 4, 10, 31, WALL_BLOCK);
	add_blocks_vertically(default_map4, 5, 9, 32, WALL_BLOCK);
	add_blocks_horizontally(default_map4, 3, 23, 38, WALL_BLOCK);
	add_blocks_horizontally(default_map4, 11, 23, 38, WALL_BLOCK);

	add_blocks_horizontally(default_map4, 5, 33, 35, WALL_BLOCK);
	add_blocks_horizontally(default_map4, 9, 33, 35, WALL_BLOCK);
	add_block(default_map4, 6, 35, WALL_BLOCK);
	add_block(default_map4, 8, 35, WALL_BLOCK);
	add_blocks_vertically(default_map4, 4, 6, 38, WALL_BLOCK);
	add_blocks_vertically(default_map4, 8, 10, 38, WALL_BLOCK);

	add_blocks_horizontally(default_map4, 5, 26, 28, WALL_BLOCK);
	add_blocks_horizontally(default_map4, 9, 26, 28, WALL_BLOCK);
	add_block(default_map4, 6, 26, WALL_BLOCK);
	add_block(default_map4, 8, 26, WALL_BLOCK);
	add_blocks_vertically(default_map4, 4, 6, 23, WALL_BLOCK);
	add_blocks_vertically(default_map4, 8, 10, 23, WALL_BLOCK);

	add_block(default_map4, 1, 25, WALL_BLOCK);
	add_block(default_map4, 2, 30, WALL_BLOCK);
	add_block(default_map4, 1, 36, WALL_BLOCK);

	add_blocks_horizontally(default_map4, 13, 16, 48, WALL_BLOCK);
	add_blocks_horizontally(default_map4, 14, 16, 48, WALL_BLOCK);
	add_block(default_map4, 15, 20, WALL_BLOCK);
	add_block(default_map4, 15, 28, WALL_BLOCK);
	add_block(default_map4, 15, 36, WALL_BLOCK);
	add_block(default_map4, 15, 44, WALL_BLOCK);
	add_block(default_map4, 16, 24, WALL_BLOCK);
	add_block(default_map4, 16, 32, WALL_BLOCK);
	add_blocks_horizontally(default_map4, 17, 16, 48, WALL_BLOCK);
	add_blocks_horizontally(default_map4, 18, 16, 48, WALL_BLOCK);

	add_blocks_vertically(default_map4, 3, 11, 41, WALL_BLOCK);
	add_blocks_vertically(default_map4, 3, 11, 42, WALL_BLOCK);
	add_blocks_vertically(default_map4, 2, 11, 43, WALL_BLOCK);
	add_blocks_vertically(default_map4, 2, 11, 44, WALL_BLOCK);
	add_blocks_vertically(default_map4, 2, 11, 45, WALL_BLOCK);
	add_blocks_vertically(default_map4, 2, 11, 46, WALL_BLOCK);
	add_blocks_vertically(default_map4, 2, 11, 47, WALL_BLOCK);
	add_blocks_vertically(default_map4, 3, 7, 48, WALL_BLOCK);
	add_blocks_vertically(default_map4, 3, 7, 49, WALL_BLOCK);

	add_blocks_vertically(default_map4, 2, 12, 53, WALL_BLOCK);
	add_blocks_vertically(default_map4, 2, 12, 54, WALL_BLOCK);
	add_blocks_vertically(default_map4, 2, 10, 55, WALL_BLOCK);
	add_blocks_vertically(default_map4, 9, 12, 56, WALL_BLOCK);
	add_blocks_vertically(default_map4, 2, 10, 52, WALL_BLOCK);
	add_blocks_vertically(default_map4, 9, 12, 51, WALL_BLOCK);


	add_blocks_horizontally(default_map4, 15, 51, 56, WALL_BLOCK);
	add_blocks_horizontally(default_map4, 16, 51, 56, WALL_BLOCK);
	add_blocks_horizontally(default_map4, 14, 53, 54, WALL_BLOCK);
	add_blocks_horizontally(default_map4, 17, 53, 54, WALL_BLOCK);

	// add coins
	add_coin(default_map4, 7, 3);
	add_coin(default_map4, 12, 3);
	add_coin(default_map4, 4, 32);
	add_coin(default_map4, 6, 33);
	add_coin(default_map4, 8, 33);
	add_coin(default_map4, 6, 28);
	add_coin(default_map4, 8, 28);
	add_coin(default_map4, 4, 29);
	add_coin(default_map4, 10, 32);
	add_coin(default_map4, 10, 29);
	add_coin(default_map4, 16, 26);
	add_coin(default_map4, 16, 41);
	add_coin(default_map4, 18, 6);
	add_coin(default_map4, 16, 7);
	add_coin(default_map4, 12, 9);
	add_coin(default_map4, 12, 21);
	add_coin(default_map4, 12, 28);
	add_coin(default_map4, 12, 33);
	add_coin(default_map4, 12, 40);
	add_coin(default_map4, 8, 9);
	add_coin(default_map4, 8, 14);
	add_coin(default_map4, 1, 6);
	add_coin(default_map4, 1, 16);
	add_coin(default_map4, 1, 30);
	add_coin(default_map4, 1, 45);
	add_coin(default_map4, 1, 54);
	add_coin(default_map4, 8, 51);
	add_coin(default_map4, 5, 57);
	add_coin(default_map4, 18, 56);
	add_coin(default_map4, 17, 51);
	add_coin(default_map4, 14, 52);
	add_coin(default_map4, 14, 55);
	add_coin(default_map4, 10, 57);
	add_coin(default_map4, 12, 48);
	add_coin(default_map4, 4, 51);
	add_coin(default_map4, 14, 52);
	add_coin(default_map4, 18, 15);
	add_coin(default_map4, 15, 32);
	add_coin(default_map4, 15, 46);
	add_coin(default_map4, 15, 21);
	add_coin(default_map4, 3, 40);
	add_coin(default_map4, 7, 40);
	add_coin(default_map4, 7, 21);
	add_coin(default_map4, 3, 19);
	add_coin(default_map4, 14, 15);
	add_coin(default_map4, 4, 6);
	add_coin(default_map4, 4, 11);

	return default_map4;
}

map *create_default_map5() {
	map *default_map5 = new_map();

	// add entrance and exit
	add_blocks_vertically(default_map5, 9, 10, 0, ENTRANCE_BLOCK);
	add_blocks_vertically(default_map5, 9, 10, 59, EXIT_BLOCK);

	// add walls
	add_blocks_vertically(default_map5, 2, 6, 3, WALL_BLOCK);
	add_blocks_vertically(default_map5, 2, 6, 4, WALL_BLOCK);
	add_blocks_horizontally(default_map5, 2, 4, 8, WALL_BLOCK);
	add_blocks_horizontally(default_map5, 3, 4, 8, WALL_BLOCK);

	add_blocks_horizontally(default_map5, 5, 7, 10, WALL_BLOCK);
	add_blocks_horizontally(default_map5, 6, 7, 10, WALL_BLOCK);
	add_blocks_vertically(default_map5, 2, 6, 11, WALL_BLOCK);
	add_blocks_vertically(default_map5, 2, 6, 12, WALL_BLOCK);

	add_blocks_vertically(default_map5, 2, 6, 15, WALL_BLOCK);
	add_blocks_vertically(default_map5, 2, 6, 16, WALL_BLOCK);
	add_blocks_vertically(default_map5, 2, 6, 17, WALL_BLOCK);

	add_blocks_horizontally(default_map5, 2, 18, 27, WALL_BLOCK);
	add_blocks_horizontally(default_map5, 3, 18, 27, WALL_BLOCK);

	add_blocks_vertically(default_map5, 8, 16, 3, WALL_BLOCK);
	add_blocks_vertically(default_map5, 8, 16, 4, WALL_BLOCK);
	add_block(default_map5, 10, 5, WALL_BLOCK);
	add_block(default_map5, 14, 5, WALL_BLOCK);

	add_blocks_vertically(default_map5, 8, 16, 8, WALL_BLOCK);
	add_blocks_vertically(default_map5, 8, 16, 9, WALL_BLOCK);
	add_block(default_map5, 8, 10, WALL_BLOCK);
	add_block(default_map5, 10, 10, WALL_BLOCK);
	add_block(default_map5, 15, 10, WALL_BLOCK);

	add_blocks_vertically(default_map5, 8, 16, 13, WALL_BLOCK);
	add_blocks_vertically(default_map5, 8, 16, 14, WALL_BLOCK);
	add_blocks_vertically(default_map5, 8, 15, 15, WALL_BLOCK);
	add_blocks_vertically(default_map5, 8, 15, 16, WALL_BLOCK);
	add_blocks_vertically(default_map5, 8, 16, 17, WALL_BLOCK);
	add_block(default_map5, 11, 12, WALL_BLOCK);
	add_block(default_map5, 12, 12, WALL_BLOCK);
	add_block(default_map5, 13, 12, WALL_BLOCK);

	add_blocks_horizontally(default_map5, 18, 3, 17, WALL_BLOCK);

	add_blocks_horizontally(default_map5, 9, 20, 24, WALL_BLOCK);
	add_blocks_horizontally(default_map5, 10, 20, 24, WALL_BLOCK);
	add_blocks_horizontally(default_map5, 11, 20, 24, WALL_BLOCK);
	add_blocks_vertically(default_map5, 5, 15, 25, WALL_BLOCK);
	add_blocks_vertically(default_map5, 5, 15, 26, WALL_BLOCK);
	add_blocks_vertically(default_map5, 5, 15, 27, WALL_BLOCK);
	add_blocks_vertically(default_map5, 9, 11, 28, WALL_BLOCK);
	add_blocks_vertically(default_map5, 9, 11, 29, WALL_BLOCK);

	add_blocks_horizontally(default_map5, 9, 37, 41, WALL_BLOCK);
	add_blocks_horizontally(default_map5, 10, 37, 41, WALL_BLOCK);
	add_blocks_horizontally(default_map5, 11, 37, 41, WALL_BLOCK);
	add_blocks_vertically(default_map5, 9, 11, 32, WALL_BLOCK);
	add_blocks_vertically(default_map5, 9, 11, 33, WALL_BLOCK);
	add_blocks_vertically(default_map5, 5, 15, 34, WALL_BLOCK);
	add_blocks_vertically(default_map5, 5, 15, 35, WALL_BLOCK);
	add_blocks_vertically(default_map5, 5, 15, 36, WALL_BLOCK);

	add_blocks_vertically(default_map5, 5, 7, 30, WALL_BLOCK);
	add_blocks_vertically(default_map5, 5, 7, 31, WALL_BLOCK);

	add_blocks_vertically(default_map5, 13, 15, 30, WALL_BLOCK);
	add_blocks_vertically(default_map5, 13, 15, 31, WALL_BLOCK);

	add_blocks_vertically(default_map5, 13, 17, 20, WALL_BLOCK);
	add_blocks_vertically(default_map5, 13, 17, 21, WALL_BLOCK);
	add_blocks_vertically(default_map5, 13, 17, 22, WALL_BLOCK);

	add_blocks_vertically(default_map5, 13, 17, 39, WALL_BLOCK);
	add_blocks_vertically(default_map5, 13, 17, 40, WALL_BLOCK);
	add_blocks_vertically(default_map5, 13, 17, 41, WALL_BLOCK);

	add_blocks_vertically(default_map5, 5, 7, 20, WALL_BLOCK);
	add_blocks_vertically(default_map5, 5, 7, 21, WALL_BLOCK);
	add_blocks_vertically(default_map5, 5, 7, 22, WALL_BLOCK);

	add_blocks_vertically(default_map5, 5, 7, 39, WALL_BLOCK);
	add_blocks_vertically(default_map5, 5, 7, 40, WALL_BLOCK);
	add_blocks_vertically(default_map5, 5, 7, 41, WALL_BLOCK);

	add_blocks_horizontally(default_map5, 2, 30, 35, WALL_BLOCK);
	add_blocks_horizontally(default_map5, 3, 30, 41, WALL_BLOCK);

	add_blocks_horizontally(default_map5, 17, 25, 36, WALL_BLOCK);
	add_blocks_horizontally(default_map5, 18, 25, 36, WALL_BLOCK);

	add_blocks_horizontally(default_map5, 1, 38, 44, WALL_BLOCK);

	add_blocks_horizontally(default_map5, 3, 44, 45, WALL_BLOCK);

	add_blocks_vertically(default_map5, 2, 5, 56, WALL_BLOCK);
	add_blocks_vertically(default_map5, 2, 5, 55, WALL_BLOCK);
	add_blocks_horizontally(default_map5, 2, 51, 54, WALL_BLOCK);
	add_blocks_horizontally(default_map5, 3, 51, 54, WALL_BLOCK);

	add_blocks_vertically(default_map5, 2, 6, 48, WALL_BLOCK);
	add_blocks_vertically(default_map5, 2, 6, 47, WALL_BLOCK);
	add_blocks_horizontally(default_map5, 5, 49, 52, WALL_BLOCK);
	add_blocks_horizontally(default_map5, 6, 49, 52, WALL_BLOCK);

	add_blocks_vertically(default_map5, 5, 9, 44, WALL_BLOCK);
	add_blocks_vertically(default_map5, 5, 9, 45, WALL_BLOCK);
	add_blocks_vertically(default_map5, 5, 9, 46, WALL_BLOCK);
	add_blocks_horizontally(default_map5, 8, 47, 52, WALL_BLOCK);
	add_blocks_horizontally(default_map5, 9, 47, 52, WALL_BLOCK);

	add_blocks_vertically(default_map5, 7, 12, 55, WALL_BLOCK);
	add_blocks_vertically(default_map5, 7, 12, 56, WALL_BLOCK);
	add_blocks_horizontally(default_map5, 11, 44, 56, WALL_BLOCK);
	add_blocks_horizontally(default_map5, 12, 44, 56, WALL_BLOCK);

	add_blocks_horizontally(default_map5, 14, 44, 45, WALL_BLOCK);
	add_blocks_horizontally(default_map5, 14, 55, 56, WALL_BLOCK);

	add_blocks_horizontally(default_map5, 14, 48, 52, WALL_BLOCK);
	add_blocks_horizontally(default_map5, 15, 48, 52, WALL_BLOCK);
	add_blocks_horizontally(default_map5, 16, 44, 56, WALL_BLOCK);
	add_blocks_horizontally(default_map5, 17, 44, 56, WALL_BLOCK);

	// add coins
	add_coin(default_map5, 9, 2);
	add_coin(default_map5, 9, 57);
	add_coin(default_map5, 1, 1);
	add_coin(default_map5, 1, 19);
	add_coin(default_map5, 1, 28);
	add_coin(default_map5, 1, 58);
	add_coin(default_map5, 18, 58);
	add_coin(default_map5, 18, 1);
	add_coin(default_map5, 4, 13);
	add_coin(default_map5, 7, 8);
	add_coin(default_map5, 10, 19);
	add_coin(default_map5, 18, 19);
	add_coin(default_map5, 4, 18);
	add_coin(default_map5, 4, 28);
	add_coin(default_map5, 4, 41);
	add_coin(default_map5, 13, 5);
	add_coin(default_map5, 10, 42);
	add_coin(default_map5, 10, 54);
	add_coin(default_map5, 15, 53);
	add_coin(default_map5, 18, 40);
	add_coin(default_map5, 15, 42);
	add_coin(default_map5, 16, 28);
	add_coin(default_map5, 4, 54);
	add_coin(default_map5, 1, 45);
	add_coin(default_map5, 16, 33);
	add_coin(default_map5, 14, 12);
	add_coin(default_map5, 12, 24);
	add_coin(default_map5, 8, 24);
	add_coin(default_map5, 8, 37);
	add_coin(default_map5, 12, 37);
	add_coin(default_map5, 8, 28);
	add_coin(default_map5, 8, 33);
	add_coin(default_map5, 12, 28);
	add_coin(default_map5, 12, 33);
	add_coin(default_map5, 4, 33);
	add_coin(default_map5, 18, 48);
	add_coin(default_map5, 13, 50);
	add_coin(default_map5, 7, 47);
	add_coin(default_map5, 4, 5);
	add_coin(default_map5, 17, 11);
	add_coin(default_map5, 10, 12);
	add_coin(default_map5, 7, 14);
	add_coin(default_map5, 2, 37);
	add_coin(default_map5, 1, 10);

	return default_map5;
}

map *create_default_map6() {
	map *default_map6 = new_map();

	// add entrance and exit
	add_blocks_vertically(default_map6, 9, 10, 0, ENTRANCE_BLOCK);
	add_blocks_vertically(default_map6, 9, 10, 59, EXIT_BLOCK);

	// add walls
	add_blocks_horizontally(default_map6, 2, 3, 8, WALL_BLOCK);
	add_blocks_horizontally(default_map6, 3, 3, 8, WALL_BLOCK);
	add_blocks_vertically(default_map6, 4, 6, 7, WALL_BLOCK);
	add_blocks_vertically(default_map6, 4, 6, 8, WALL_BLOCK);
	add_blocks_horizontally(default_map6, 5, 9, 15, WALL_BLOCK);
	add_blocks_horizontally(default_map6, 6, 9, 15, WALL_BLOCK);

	add_blocks_horizontally(default_map6, 2, 11, 15, WALL_BLOCK);
	add_blocks_horizontally(default_map6, 3, 11, 15, WALL_BLOCK);

	add_blocks_horizontally(default_map6, 8, 3, 19, WALL_BLOCK);
	add_blocks_horizontally(default_map6, 9, 3, 19, WALL_BLOCK);
	add_blocks_horizontally(default_map6, 10, 3, 19, WALL_BLOCK);
	add_blocks_horizontally(default_map6, 11, 3, 19, WALL_BLOCK);
	add_blocks_vertically(default_map6, 5, 7, 3, WALL_BLOCK);
	add_blocks_vertically(default_map6, 5, 7, 4, WALL_BLOCK);

	add_blocks_horizontally(default_map6, 13, 3, 13, WALL_BLOCK);
	add_blocks_horizontally(default_map6, 14, 3, 13, WALL_BLOCK);
	add_blocks_vertically(default_map6, 15, 16, 12, WALL_BLOCK);
	add_blocks_vertically(default_map6, 15, 16, 13, WALL_BLOCK);
	add_blocks_horizontally(default_map6, 15, 14, 19, WALL_BLOCK);
	add_blocks_horizontally(default_map6, 16, 14, 19, WALL_BLOCK);

	add_blocks_horizontally(default_map6, 13, 16, 19, WALL_BLOCK);

	add_blocks_horizontally(default_map6, 18, 3, 14, WALL_BLOCK);
	add_blocks_horizontally(default_map6, 17, 3, 9, WALL_BLOCK);
	add_blocks_horizontally(default_map6, 16, 3, 8, WALL_BLOCK);

	add_blocks_horizontally(default_map6, 2, 18, 25, WALL_BLOCK);
	add_block(default_map6, 3, 19, WALL_BLOCK);
	add_block(default_map6, 4, 22, WALL_BLOCK);
	add_blocks_horizontally(default_map6, 5, 18, 24, WALL_BLOCK);
	add_blocks_horizontally(default_map6, 6, 18, 24, WALL_BLOCK);
	add_blocks_horizontally(default_map6, 3, 25, 29, WALL_BLOCK);
	add_blocks_horizontally(default_map6, 4, 25, 29, WALL_BLOCK);

	add_blocks_vertically(default_map6, 2, 6, 30, WALL_BLOCK);
	add_blocks_horizontally(default_map6, 2, 31, 38, WALL_BLOCK);
	add_blocks_horizontally(default_map6, 6, 31, 38, WALL_BLOCK);
	add_block(default_map6, 3, 38, WALL_BLOCK);
	add_block(default_map6, 5, 38, WALL_BLOCK);
	add_block(default_map6, 4, 32, WALL_BLOCK);
	add_block(default_map6, 4, 35, WALL_BLOCK);

	add_blocks_horizontally(default_map6, 10, 22, 38, WALL_BLOCK);
	add_blocks_horizontally(default_map6, 11, 22, 38, WALL_BLOCK);
	add_blocks_vertically(default_map6, 8, 9, 22, WALL_BLOCK);
	add_blocks_vertically(default_map6, 8, 9, 23, WALL_BLOCK);
	add_blocks_vertically(default_map6, 8, 9, 24, WALL_BLOCK);
	add_blocks_vertically(default_map6, 8, 9, 36, WALL_BLOCK);
	add_blocks_vertically(default_map6, 8, 9, 37, WALL_BLOCK);
	add_blocks_vertically(default_map6, 8, 9, 38, WALL_BLOCK);

	add_blocks_horizontally(default_map6, 8, 27, 33, WALL_BLOCK);
	add_blocks_vertically(default_map6, 6, 7, 27, WALL_BLOCK);

	add_blocks_horizontally(default_map6, 13, 22, 38, WALL_BLOCK);
	add_blocks_horizontally(default_map6, 14, 22, 38, WALL_BLOCK);
	add_blocks_vertically(default_map6, 15, 16, 22, WALL_BLOCK);
	add_blocks_vertically(default_map6, 15, 16, 23, WALL_BLOCK);
	add_blocks_vertically(default_map6, 15, 16, 24, WALL_BLOCK);
	add_blocks_vertically(default_map6, 15, 16, 36, WALL_BLOCK);
	add_blocks_vertically(default_map6, 15, 16, 37, WALL_BLOCK);
	add_blocks_vertically(default_map6, 15, 16, 38, WALL_BLOCK);

	add_blocks_horizontally(default_map6, 18, 17, 43, WALL_BLOCK);
	add_blocks_horizontally(default_map6, 16, 27, 33, WALL_BLOCK);
	add_blocks_horizontally(default_map6, 17, 27, 33, WALL_BLOCK);

	add_blocks_horizontally(default_map6, 2, 41, 50, WALL_BLOCK);
	add_blocks_horizontally(default_map6, 3, 41, 50, WALL_BLOCK);
	add_blocks_horizontally(default_map6, 4, 50, 55, WALL_BLOCK);
	add_blocks_horizontally(default_map6, 5, 41, 50, WALL_BLOCK);
	add_blocks_horizontally(default_map6, 6, 41, 50, WALL_BLOCK);
	add_blocks_vertically(default_map6, 2, 3, 55, WALL_BLOCK);
	add_blocks_vertically(default_map6, 5, 6, 55, WALL_BLOCK);
	add_blocks_vertically(default_map6, 2, 6, 56, WALL_BLOCK);
	add_blocks_horizontally(default_map6, 2, 53, 54, WALL_BLOCK);
	add_blocks_horizontally(default_map6, 6, 53, 54, WALL_BLOCK);

	add_blocks_horizontally(default_map6, 8, 41, 47, WALL_BLOCK);
	add_blocks_horizontally(default_map6, 9, 41, 47, WALL_BLOCK);
	add_blocks_horizontally(default_map6, 10, 41, 47, WALL_BLOCK);
	add_blocks_horizontally(default_map6, 11, 41, 47, WALL_BLOCK);

	add_blocks_horizontally(default_map6, 8, 50, 56, WALL_BLOCK);
	add_blocks_horizontally(default_map6, 9, 50, 56, WALL_BLOCK);
	add_blocks_horizontally(default_map6, 10, 50, 56, WALL_BLOCK);
	add_blocks_horizontally(default_map6, 11, 50, 56, WALL_BLOCK);

	add_blocks_horizontally(default_map6, 13, 41, 56, WALL_BLOCK);
	add_blocks_horizontally(default_map6, 14, 41, 56, WALL_BLOCK);
	add_blocks_horizontally(default_map6, 15, 41, 56, WALL_BLOCK);
	add_blocks_horizontally(default_map6, 16, 46, 52, WALL_BLOCK);
	add_blocks_horizontally(default_map6, 17, 46, 52, WALL_BLOCK);

	add_blocks_horizontally(default_map6, 17, 55, 56, WALL_BLOCK);

	add_blocks_horizontally(default_map6, 17, 41, 42, WALL_BLOCK);

	// add coins
	add_coin(default_map6, 10, 57);
	add_coin(default_map6, 18, 58);
	add_coin(default_map6, 17, 10);
	add_coin(default_map6, 17, 26);
	add_coin(default_map6, 15, 30);
	add_coin(default_map6, 17, 34);
	add_coin(default_map6, 12, 30);
	add_coin(default_map6, 12, 36);
	add_coin(default_map6, 12, 24);
	add_coin(default_map6, 9, 30);
	add_coin(default_map6, 7, 28);
	add_coin(default_map6, 9, 35);
	add_coin(default_map6, 9, 25);
	add_coin(default_map6, 7, 5);
	add_coin(default_map6, 7, 15);
	add_coin(default_map6, 4, 9);
	add_coin(default_map6, 10, 20);
	add_coin(default_map6, 14, 14);
	add_coin(default_map6, 12, 17);
	add_coin(default_map6, 10, 2);
	add_coin(default_map6, 10, 39);
	add_coin(default_map6, 10, 48);
	add_coin(default_map6, 12, 54);
	add_coin(default_map6, 12, 43);
	add_coin(default_map6, 18, 44);
	add_coin(default_map6, 18, 51);
	add_coin(default_map6, 17, 18);
	add_coin(default_map6, 12, 8);
	add_coin(default_map6, 16, 53);
	add_coin(default_map6, 5, 57);
	add_coin(default_map6, 4, 49);
	add_coin(default_map6, 1, 48);
	add_coin(default_map6, 4, 40);
	add_coin(default_map6, 4, 36);
	add_coin(default_map6, 4, 33);
	add_coin(default_map6, 4, 24);
	add_coin(default_map6, 4, 20);
	add_coin(default_map6, 1, 14);
	add_coin(default_map6, 2, 29);
	add_coin(default_map6, 2, 26);
	add_coin(default_map6, 1, 34);
	add_coin(default_map6, 7, 43);
	add_coin(default_map6, 5, 54);
	add_coin(default_map6, 3, 54);
	add_coin(default_map6, 7, 52);

	return default_map6;
}

void create_default_maps(map *default_maps[]) {
    map *default_map1 = create_default_map1();
    map *default_map2 = create_default_map2();
    map *default_map3 = create_default_map3();
	map *default_map4 = create_default_map4();
	map *default_map5 = create_default_map5();
	map *default_map6 = create_default_map6();

    default_maps[0] = default_map1;
    default_maps[1] = default_map2;
    default_maps[2] = default_map3;
    default_maps[3] = default_map4;
    default_maps[4] = default_map5;
    default_maps[5] = default_map6;
}