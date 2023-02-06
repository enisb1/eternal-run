#ifndef STORING_HPP
#define STORING_HPP

// stores the coins list in the corresponding file
void store_coins(int level, coin_node *coin_list);

// stores the map index in the corresponding file
void store_map_index(int level, int mapIndex);

// returns the level's stored map index
int get_stored_map_index(int level);

// returns the level's stored coin list
coin_node *get_stored_coin_list(int level);

#endif