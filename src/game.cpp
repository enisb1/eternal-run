/* Includes */

#include <ncursesw/ncurses.h>

#include <stdlib.h>
#include <cstring>
#include <ctime>
#include <cstdlib>

#include "game.hpp"
#include "entities.hpp"
#include "map.hpp"
#include "graphics.hpp"
#include "storing.hpp"
#include "utils.hpp"

/* Vars */

Player player;
enemy_node *current_enemy_list = NULL;
bullet_node *current_bullet_list = NULL;

int coins;
int level;
int max_level = 0;

map *maps[6];
int current_map_index = 0;
coin_node *current_coin_list = NULL;

/* Methods */

void create_maps() {
    map *map1 = create_map1();
    map *map2 = create_map2();
    map *map3 = create_map3();
	map *map4 = create_map4();
	map *map5 = create_map5();
	map *map6 = create_map6();

    maps[0] = map1;
    maps[1] = map2;
    maps[2] = map3;
    maps[3] = map4;
    maps[4] = map5;
    maps[5] = map6;
}

void load_saved_map(WINDOW *game_win, bool is_entering_level) {
    delete_bullet_list(current_bullet_list);

    delete_coin_list(current_coin_list);
    current_coin_list = get_stored_coin_list(level);
    display_coins(game_win, current_coin_list);

    current_map_index = get_stored_map_index(level);
    display_map(game_win, maps[current_map_index], current_coin_list);
    
    set_player_starting_properties(is_entering_level, &player, maps, current_map_index);
    display_player(game_win, player);

    current_enemy_list = get_stored_enemy_list(maps[current_map_index], player, level);
    display_enemies(game_win, current_enemy_list);
}

void load_random_map(WINDOW *game_win, bool is_entering_level, bool is_death) {
    // get a new random index
    int next_map_index = rand() % 6;
	while (next_map_index == current_map_index) next_map_index = rand() % 6;
	current_map_index = next_map_index;

    // set a new default coin list to current_coin_list based on current map index
    delete_coin_list(current_coin_list);
    get_default_coin_list(current_coin_list, current_map_index);

    delete_bullet_list(current_bullet_list);

    // display the new level's map
    if (level >= 2 && !is_death)
        display_map(
            game_win, 
            maps[current_map_index], 
            current_coin_list
        );
	else
        display_map_with_anim(
            game_win, 
            maps[current_map_index], 
            current_coin_list
        );

    // set player's starting properties and display it
    set_player_starting_properties(is_entering_level, &player, maps, current_map_index);
    display_player(game_win, player);

    // create enemy list and display it
    create_enemy_list(maps[current_map_index], player, current_enemy_list, level);
    display_enemies(game_win, current_enemy_list);
}

void load_next_level(WINDOW *game_win, WINDOW *info_win) {
    level++;
    refresh_title(info_win, level, false);

    // store level's data in files
    if (level > 1) {
        store_map_index(level - 1, current_map_index);
        store_coins(level - 1, current_coin_list);
        store_enemies(level - 1, current_enemy_list);
    }

    // checks if it's a new level or not
    if (level > max_level) {
        max_level++;

        // load a new map based on a random index
        load_random_map(game_win, true, false);
    } else load_saved_map(game_win, true);
}

void load_previous_level(WINDOW *game_win, WINDOW *info_win) {
    // store level's data in files
    store_map_index(level, current_map_index);
    store_coins(level, current_coin_list);
    store_enemies(level, current_enemy_list);

    level--;
    refresh_title(info_win, level, false);

    load_saved_map(game_win, false);
}

void new_game(WINDOW *game_win, WINDOW *info_win) {
    // initialize vars
    coins = 0;
    level = 0;
    max_level = 0;

    // create player
    player = Player(
        maps[current_map_index]->entrance_exit_positions[0],
        maps[current_map_index]->entrance_exit_positions[1],
        get_player_starting_direction(true, maps, current_map_index), false,
        3, 0
    );

    refresh_title(info_win, level, true);
    refresh_stats(info_win, player, coins);

    load_next_level(game_win, info_win);
    
    // refresh info window
    wclear(info_win);
    box(info_win, 0, 0);
    mvwprintw(info_win, 2, 1, "----------------");
    mvwprintw(info_win, 6, 1, "----------------");
    refresh_stats(info_win, player, coins);
    refresh_title(info_win, level, false);
}

bool collect_coin(WINDOW *info_win, int y, int x) {
    // if coin in list -> coin removed, coin counter incremented, return=True
    // else return=False
    bool found = false;

    if (current_coin_list != NULL) {
        if (current_coin_list->y == y && current_coin_list->x == x) {
            coin_node *tmp = current_coin_list; 
            current_coin_list = current_coin_list->next;
            delete tmp;
            found = true;
        } else {
            coin_node *previous_coin = current_coin_list;
            coin_node *current_coin = current_coin_list->next;
            while (current_coin != NULL && !found) {
                if (current_coin->y == y && current_coin->x == x) {
                    coin_node *tmp = current_coin;
                    previous_coin->next = current_coin->next;
                    delete tmp;
                    found = true;
                } else {
                    previous_coin = current_coin; 
                    current_coin = previous_coin->next; 
                }
            }
        }
    }

    if (found) {
        coins++;
        refresh_stats(info_win, player, coins);
    }

    return found;
}

void move_player(WINDOW *game_win, WINDOW *info_win) {
    // get next block based on direction
    int next_y = player.get_y();
    int next_x = player.get_x();
    get_next_position(player.get_direction(), next_y, next_x);

    // check if next block is not a wall && is inside the map
    if (maps[current_map_index]->blocks[next_y][next_x] != WALL_BLOCK
        && next_y >= 0 && next_y < 20 && next_x >= 0 && next_x < 60) {
        // move player to next position and display it
        set_blank_char(game_win, player.get_y(), player.get_x());
        player.set_y(next_y);
        player.set_x(next_x);

        // check if next block is a special block (coin, entrance or exit)
        bool is_coin = collect_coin(info_win, next_y, next_x);
        if (!is_coin) {
            if (maps[current_map_index]->blocks[next_y][next_x] == ENTRANCE_BLOCK
                && level > 1) {
                // previous level
                player.set_is_moving(false);
                load_previous_level(game_win, info_win);
            } else if (maps[current_map_index]->blocks[next_y][next_x] == EXIT_BLOCK) {
                // next level
                if (level % 2 == 0 && max_level == level) {
                    // market level
                    refresh_title(info_win, level, true);
                    show_market_screen(game_win, info_win, &player, coins);

                    load_next_level(game_win, info_win);
                } else load_next_level(game_win, info_win);
            }
        }
    }
    
}

void death(WINDOW *game_win, WINDOW *info_win) {
    player.set_is_moving(false);
    player.decrease_life();
    refresh_stats(info_win, player, coins);

    destroy_map_with_animation(game_win);
    if (player.get_life() > 0) {
        load_random_map(game_win, true, true);
        wrefresh(game_win);
    } else {
        // game over
        switch (show_game_over_screen(game_win)) {
            case 0:
                new_game(game_win, info_win);
                break;
            case 1:
                endwin();
                exit(0);
                break;
        }
    }
}

// change enemy direction if can cross,
// and returns 1 if can cross, 0 otherwise
bool change_direction_to_cross(Enemy *current_enemy) {
    // check if can cross in one direction
    bool can_cross = false;

    int new_direction = (current_enemy->get_direction() + 1) % 4;
    
    if (can_move_in_next_two_blocks(
        new_direction, 
        current_enemy->get_y(), 
        current_enemy->get_x(), 
        maps, 
        current_map_index
    )) {
        current_enemy->set_direction(new_direction);
        can_cross = true;
    } else {
        // check if can cross in the other direction
        int new_direction = (current_enemy->get_direction() + 3) % 4;

        if (can_move_in_next_two_blocks(
            new_direction, 
            current_enemy->get_y(), 
            current_enemy->get_x(),
            maps, 
            current_map_index
        )) {
            current_enemy->set_direction(new_direction);
            can_cross = true;
        }
    }

    return can_cross;
}

void move_enemies(WINDOW *game_win, WINDOW *info_win) {
    enemy_node *enemy_list_iterator = current_enemy_list;
    bool is_death = false;

    while (enemy_list_iterator != NULL && !is_death) {
        Enemy *current_enemy = &enemy_list_iterator->current_enemy;
        
        // check if enemy is in the player's position before moving
        if (are_entities_in_same_position(player, *current_enemy)) {
            // enemy position = player position, before moving
            if (player.get_shield() > 0) {
                player.decrease_shield();
                refresh_stats(info_win, player, coins);
            } else {
                is_death = true;
                death(game_win, info_win);
            }
        }

        if (!is_death) {
            // enemy position != player position, before moving
            bool can_cross = false;

            if (current_enemy->get_blocks_traveled() > 8) 
                can_cross = change_direction_to_cross(current_enemy);

            // get next block position based on current direction
            int next_y = current_enemy->get_y();
            int next_x = current_enemy->get_x();

            get_next_position(
                current_enemy->get_direction(), 
                next_y, next_x
            );

            if (can_cross) current_enemy->reset_blocks_traveled();
            else {
                // change enemy direction randomically
                // if player can't move to next block
                // and get next block position
                if (!can_move_in_block(next_y, next_x, maps, current_map_index)) {
                    current_enemy->set_direction(
                        get_random_enemy_direction(
                            maps[current_map_index], 
                            current_enemy->get_y(),
                            current_enemy->get_x()
                        )
                    );

                    next_y = current_enemy->get_y();
                    next_x = current_enemy->get_x();

                    get_next_position(
                        current_enemy->get_direction(), 
                        next_y, next_x
                    );
                }

                current_enemy->increment_blocks_traveled();
            }

            // move enemy
            set_blank_char(
                game_win, 
                current_enemy->get_y(), 
                current_enemy->get_x()
            );

            current_enemy->set_y(next_y);
            current_enemy->set_x(next_x);

            display_enemy(game_win, *current_enemy);

            // check if enemy is in the player's position after moving
            if (are_entities_in_same_position(player, *current_enemy)) {
                if (player.get_shield() > 0) {
                    player.decrease_shield();
                    refresh_stats(info_win, player, coins);
                } else {
                    is_death = true;
                    death(game_win, info_win);
                }
            } else enemy_list_iterator = enemy_list_iterator->next;
        }
    }
}

void create_bullet() {
    int bullet_y = player.get_y();
    int bullet_x = player.get_x();
    get_next_position(player.get_direction(), bullet_y, bullet_x);
    
    if (can_move_in_block(bullet_y, bullet_x, maps, current_map_index)) {
        Entity new_bullet = Entity(
            bullet_y, bullet_x, 
            player.get_direction()
        );

        add_bullet(current_bullet_list, new_bullet);
    }
}

void move_bullets(WINDOW *game_win) {
    if (current_bullet_list != NULL) {
        bullet_node *new_bullet_list = NULL;

        bullet_node *bullet_list_iterator = current_bullet_list;

        // create new bullet list with valid bullets
        // and new enemy list with valid enemies
        while (bullet_list_iterator != NULL) {
            Entity *current_bullet = &bullet_list_iterator->current_bullet;
            bool valid_bullet = true;
            
            // check if bullet is in enemy position before moving
            enemy_node *new_enemy_list = NULL;
            enemy_node *enemy_list_iterator = current_enemy_list;
            while (enemy_list_iterator != NULL) {
                if (are_entities_in_same_position(
                    *current_bullet, 
                    enemy_list_iterator->current_enemy
                )) {
                    valid_bullet = false;
                    
                    enemy_list_iterator->current_enemy.decrease_level(player.get_bullet_damage());
                    if (enemy_list_iterator->current_enemy.get_level()>0) 
                        add_enemy(
                        new_enemy_list, 
                        enemy_list_iterator->current_enemy
                    );
                }
                else add_enemy(new_enemy_list, enemy_list_iterator->current_enemy);

                enemy_node *tmp_enemy = enemy_list_iterator;
                enemy_list_iterator = enemy_list_iterator->next;
                delete tmp_enemy;
            }

            // set blank char for the current position and get next position
            int next_y = current_bullet->get_y();
            int next_x = current_bullet->get_x();
        
            set_blank_char(game_win, next_y, next_x);

            get_next_position(current_bullet->get_direction(), next_y, next_x);

            // move if next block is valid
            if (can_move_in_block(next_y, next_x, maps, current_map_index)) {
                current_bullet->set_y(next_y);
                current_bullet->set_x(next_x);
            } else valid_bullet = false;

            // check if bullet is in enemy position after moving
            enemy_node *new_enemy_list_after_moving = new_enemy_list;
            new_enemy_list = NULL;
            while (new_enemy_list_after_moving != NULL) {
                if (are_entities_in_same_position(
                    *current_bullet, 
                    new_enemy_list_after_moving->current_enemy
                )) {
                    valid_bullet = false;
                    
                    new_enemy_list_after_moving->current_enemy.decrease_level(player.get_bullet_damage());
                    if (new_enemy_list_after_moving->current_enemy.get_level()>0) 
                        add_enemy(
                        new_enemy_list, 
                        new_enemy_list_after_moving->current_enemy
                        );
                    else set_blank_char(game_win, current_bullet->get_y(), current_bullet->get_x());
                }
                else add_enemy(new_enemy_list, new_enemy_list_after_moving->current_enemy);

                enemy_node *tmp_enemy = new_enemy_list_after_moving;
                new_enemy_list_after_moving = new_enemy_list_after_moving->next;
                delete tmp_enemy;
            }

            if (valid_bullet) {
                add_bullet(new_bullet_list, *current_bullet);
                mvwaddch(game_win, next_y, next_x, '.');
            }

            // set new list to enemy list
            current_enemy_list = new_enemy_list;

            bullet_node *tmp_bullet = bullet_list_iterator;
            bullet_list_iterator = bullet_list_iterator->next;
            delete tmp_bullet;
        }

        // set new list to bullet list
        current_bullet_list = new_bullet_list;
    }
}

void start_game_loop(WINDOW *game_win, WINDOW *info_win) {
    const unsigned int ANIM_PERIOD = 1;

    unsigned int tick = 0;
    int move_player_enemies_tick;

    const unsigned int KEY_SPACEBAR = 32;
    int old_input_char = -1;

    while (1) {
        int input_char = wgetch(game_win);

        if (input_char != -1) {
            while (input_char == old_input_char)
                input_char = wgetch(game_win);

            switch (input_char) {
                case KEY_DOWN:
                    if (!player.get_is_moving()) {
                        if (player.get_direction() == DOWN) 
                            player.set_is_moving(true);
                    } else player.set_direction(DOWN);
                    break;
                case KEY_UP:
                    if (!player.get_is_moving()) {
                        if (player.get_direction() == UP) 
                            player.set_is_moving(true);
                    } else player.set_direction(UP);
                    break;
                case KEY_RIGHT:
                    if (!player.get_is_moving()) {
                        if (player.get_direction() == RIGHT) 
                            player.set_is_moving(true);
                    } else player.set_direction(RIGHT);
                    break;
                case KEY_LEFT:
                    if (!player.get_is_moving()) {
                        if (player.get_direction() == LEFT) 
                            player.set_is_moving(true);
                    } else player.set_direction(LEFT);
                    break;
                case KEY_SPACEBAR:
                    if (player.get_is_moving() && player.get_has_weapon())
                        create_bullet();
                    break;
                case 27:
                    // esc
                    switch (show_esc_screen(game_win)) {
                        case 0:
                            endwin();
                            exit(0);
                            break;
                        case 1:
                            display_map(
                                game_win, 
                                maps[current_map_index], 
                                current_coin_list
                            );
                            break;
                    }
                    break;
            }
        }

        if (player.get_is_moving()) {
            if (player.get_faster_bullet_speed())
                move_player_enemies_tick = 2;
            else move_player_enemies_tick = 1;

            if (tick == move_player_enemies_tick) {
                move_player(game_win, info_win);
                display_coins(game_win, current_coin_list);
                move_enemies(game_win, info_win);
            }

            move_bullets(game_win);

            if (tick == move_player_enemies_tick)
                display_player(game_win, player);

            tick++;
            if (tick > move_player_enemies_tick) tick = 0;
        }

        old_input_char = input_char;

        wrefresh(game_win);

        if (player.get_faster_bullet_speed())
            napms(53);
        else napms(80);
    };

}