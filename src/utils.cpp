/* Includes */

#include <cstdlib>

#include "utils.hpp"

/* Methods */

bool are_entities_in_same_position(Entity entity_1, Entity entity_2) {
    return entity_1.get_x() == entity_2.get_x() 
        && entity_1.get_y() == entity_2.get_y();
}

void get_next_position(int direction, int &y, int &x) {
    // increase/decrease position based on direction
    switch (direction) {
        case DOWN:
            y++;
            break;
        case UP:
            y--;
            break;
        case RIGHT:
            x++;
            break;
        case LEFT:
            x--;
            break;
    }
}

bool can_move_in_block(int y, int x, map *maps[], int current_map_index) {
    return maps[current_map_index]->blocks[y][x] != WALL_BLOCK
        && maps[current_map_index]->blocks[y][x] != ENTRANCE_BLOCK
        && maps[current_map_index]->blocks[y][x] != EXIT_BLOCK;
}

bool can_move_in_next_two_blocks(int direction, int start_y, int start_x, map *maps[], int current_map_index) {
    int next_y1 = start_y;
    int next_x1 = start_x;
    get_next_position(direction, next_y1, next_x1);

    int next_y2 = next_y1;
    int next_x2 = next_x1;
    get_next_position(direction, next_y2, next_x2);

    return can_move_in_block(next_y1, next_x1, maps, current_map_index) 
    && can_move_in_block(next_y2, next_x2, maps, current_map_index);
}

void delete_coin_list(coin_node* &coin_list) {
    while (coin_list!=NULL) {
        coin_node *tmp = coin_list;
        coin_list = coin_list->next;
        delete tmp;
    }
}

void delete_bullet_list(bullet_node* &bullet_list) {
    while (bullet_list!=NULL) {
        bullet_node *tmp = bullet_list;
        bullet_list = bullet_list->next;
        delete tmp;
    }
}

int get_player_starting_direction(bool is_at_entrance, map *maps[], int current_map_index) {
    int direction;
    int y; 
    int x;

    if (is_at_entrance) {
        y = maps[current_map_index]->entrance_exit_positions[0];
        x = maps[current_map_index]->entrance_exit_positions[1];
    } else {
        y = maps[current_map_index]->entrance_exit_positions[2];
        x = maps[current_map_index]->entrance_exit_positions[3];
    }

    if (y == 0) direction = DOWN;
    else if (y == 19) direction = UP;
    else if (x == 0) direction = RIGHT;
    else if (x == 59) direction = LEFT;
    
    return direction;
}

void set_player_starting_properties(bool is_at_entrance, Player *player, map *maps[], int current_map_index) {
    if (is_at_entrance) {
        player->set_y(maps[current_map_index]->entrance_exit_positions[0]);
        player->set_x(maps[current_map_index]->entrance_exit_positions[1]);
    } else {
        player->set_y(maps[current_map_index]->entrance_exit_positions[2]);
        player->set_x(maps[current_map_index]->entrance_exit_positions[3]);
    }
    player->set_direction(get_player_starting_direction(is_at_entrance, maps, current_map_index));
    player->set_is_moving(false);
}