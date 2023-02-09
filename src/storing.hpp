#ifndef STORING_HPP
#define STORING_HPP

/* Includes */

#include "map.hpp"
#include "entities.hpp"

/* Methods */

// store the coins list in the corresponding file
void store_coins(int level, coin_node *coin_list);

// store the map index in the corresponding file
void store_map_index(int level, int mapIndex);

// store the list of enemies in the corresponding file
void store_enemies(int level, enemy_node *enemy_list);

// return the level's stored map index
int get_stored_map_index(int level);

// return the level's stored coin list
coin_node *get_stored_coin_list(int level);

// return the level's stored enemy list
enemy_node *get_stored_enemy_list(map *map, Player player, int level);

// delete the files saved in the specific storing files directory
void delete_files();

#endif