#ifndef UTILS_HPP
#define UTILS_HPP

/* Includes */

#include "entities.hpp"
#include "map.hpp"

// return true if entities are in the same position
bool are_entities_in_same_position(Entity entity_1, Entity entity_2);

// set y and x to the next position's coordinates based on the given direction
void get_next_position(int direction, int &y, int &x);

// return true if the entity can move in the block specified by y and x
bool can_move_in_block(int y, int x, map* maps[], int current_map_index);

// return true if the entity can move in the next two blocks specified by y and x
bool can_move_in_next_two_blocks(int direction, int start_y, int start_x, map* maps[], int current_map_index);

// delete the given coin list
void delete_coin_list(coin_node* &coin_list);

// delete the given bullet list
void delete_bullet_list(bullet_node* &bullet_list);

// return the player's starting direction based on the entrance/exit position
int get_player_starting_direction(bool is_at_entrance, map* maps[], int current_map_index);

// set player's starting properties based on the entrance/exit position
void set_player_starting_properties(bool is_at_entrance, Player *player, map* maps[], int current_map_index);

#endif