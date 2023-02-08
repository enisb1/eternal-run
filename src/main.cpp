/* Includes */

#include <ncursesw/ncurses.h>

#include <stdlib.h>
#include <cstring>
#include <ctime>
#include <cstdlib>

#include "graphics.hpp"
#include "map.hpp"
#include "entities.hpp"
#include "storing.hpp"

using namespace std; 

/* Vars */

WINDOW *game_win;
WINDOW *info_win;
const int game_win_height = 20;
const int game_win_width = 60;
const int info_win_width = 18;

Player player;
enemy_node *current_enemy_list = NULL;
bullet_node *current_bullet_list = NULL;

int coins;
int level;
int max_level = 0;

map *default_maps[6];
int current_map_index = 0;
coin_node *current_coin_list = NULL;

/* Methods */

void create_colors() {
    if (has_colors()) start_color();

    init_pair(WALL_PAIR, COLOR_WHITE, COLOR_BLUE);
    init_pair(RED_PAIR, COLOR_RED, 0);
    init_pair(CYAN_PAIR, COLOR_CYAN, 0);
    init_pair(YELLOW_PAIR, COLOR_YELLOW, 0);
}

int get_player_starting_direction(bool is_at_entrance) {
    int direction;
    int y; 
    int x;

    if (is_at_entrance) {
        y = default_maps[current_map_index]->entrance_exit_positions[0];
        x = default_maps[current_map_index]->entrance_exit_positions[1];
    } else {
        y = default_maps[current_map_index]->entrance_exit_positions[2];
        x = default_maps[current_map_index]->entrance_exit_positions[3];
    }

    if (y == 0) direction = DOWN;
    else if (y == 19) direction = UP;
    else if (x == 0) direction = RIGHT;
    else if (x == 59) direction = LEFT;
    
    return direction;
}

void set_player_starting_properties(bool is_at_entrance) {
    if (is_at_entrance) {
        player.set_y(default_maps[current_map_index]->entrance_exit_positions[0]);
        player.set_x(default_maps[current_map_index]->entrance_exit_positions[1]);
    } else {
        player.set_y(default_maps[current_map_index]->entrance_exit_positions[2]);
        player.set_x(default_maps[current_map_index]->entrance_exit_positions[3]);
    }
    player.set_direction(get_player_starting_direction(is_at_entrance));
    player.set_is_moving(false);
}

void delete_coin_list() {
    while (current_coin_list!=NULL) {
        coin_node *tmp = current_coin_list;
        current_coin_list = current_coin_list->next;
        delete tmp;
    }
}

void load_saved_map(bool is_entering_level) {
    current_map_index = get_stored_map_index(level);
    current_coin_list = get_stored_coin_list(level);

    display_map(game_win, default_maps[current_map_index], current_coin_list);
    set_player_starting_properties(is_entering_level);
    display_player(game_win, player);

    // TODO: display saved enemies
    create_enemy_list(default_maps[current_map_index], player, current_enemy_list, level);
    display_enemies(game_win, current_enemy_list);
}

void load_random_map(bool is_entering_level, bool is_death) {
    // get a new random index
    int next_map_index = rand() % 6;
	while (next_map_index == current_map_index) next_map_index = rand() % 6;
	current_map_index = next_map_index;

    // set a new default coin list to current_coin_list based on current map index
    delete_coin_list();
    get_default_coin_list(current_coin_list, current_map_index);

    // display the new level's map
    if (level >= 2 && !is_death)
        display_map(
            game_win, 
            default_maps[current_map_index], 
            current_coin_list
        );
	else
        display_map_with_anim(
            game_win, 
            default_maps[current_map_index], 
            current_coin_list
        );

    // set player's starting properties and display it
    set_player_starting_properties(is_entering_level);
    display_player(game_win, player);

    // create enemy list and display it
    create_enemy_list(default_maps[current_map_index], player, current_enemy_list, level);
    display_enemies(game_win, current_enemy_list);
}

void load_next_level() {
    level++;
    refresh_title(info_win, level, false);

    // store level's data in files
    if (level > 1) {
        store_map_index(level - 1, current_map_index);
        store_coins(level - 1, current_coin_list);
    }

    // checks if it's a new level or not
    if (level > max_level) {
        max_level++;

        // load a new map based on a random index
        load_random_map(true, false);
    } else load_saved_map(true);
}

void load_previous_level() {
    // store level's data in files
    store_map_index(level, current_map_index);
    store_coins(level, current_coin_list);

    level--;
    refresh_title(info_win, level, false);

    load_saved_map(false);
}

void new_game() {
    // initialize vars
    coins = 0;
    level = 0;

    // create player
    player = Player(
        default_maps[current_map_index]->entrance_exit_positions[0],
        default_maps[current_map_index]->entrance_exit_positions[1],
        get_player_starting_direction(true), false,
        3, 0
    );

    refresh_title(info_win, level, true);
    refresh_stats(info_win, player, coins);
    int coins_2 = 170;
    show_market_screen(game_win, info_win, &player, coins_2);

    load_next_level();
    
    // refresh info window
    wclear(info_win);
    box(info_win, 0, 0);
    mvwprintw(info_win, 2, 1, "----------------");
    mvwprintw(info_win, 6, 1, "----------------");
    refresh_stats(info_win, player, coins);
    refresh_title(info_win, level, false);
}

bool collect_coin(int y, int x) {
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

void move_player() {
    // get next block based on direction
    int next_y = player.get_y();
    int next_x = player.get_x();
    get_next_position(player.get_direction(), next_y, next_x);

    // check if next block is not a wall && is inside the map
    if (default_maps[current_map_index]->blocks[next_y][next_x] != WALL_BLOCK
        && next_y >= 0 && next_y < 20 && next_x >= 0 && next_x < 60) {
        // move player to next position and display it
        set_blank_char(game_win, player.get_y(), player.get_x());
        player.set_y(next_y);
        player.set_x(next_x);

        // check if next block is a special block (coin, entrance or exit)
        bool is_coin = collect_coin(next_y, next_x);
        if (!is_coin) {
            if (default_maps[current_map_index]->blocks[next_y][next_x] == ENTRANCE_BLOCK
                && level > 1) {
                // previous level
                player.set_is_moving(false);
                load_previous_level();
            } else if (default_maps[current_map_index]->blocks[next_y][next_x] == EXIT_BLOCK) {
                // next level
                if (level % 2 == 0 && max_level == level) {
                    // market level
                    refresh_title(info_win, level, true);
                    show_market_screen(game_win, info_win, &player, coins);

                    load_next_level();
                } else load_next_level();
            }
        }
    }
    
}

bool can_move_in_block(int y, int x) {
    return default_maps[current_map_index]->blocks[y][x] != WALL_BLOCK
        && default_maps[current_map_index]->blocks[y][x] != ENTRANCE_BLOCK
        && default_maps[current_map_index]->blocks[y][x] != EXIT_BLOCK;
}

bool can_move_in_next_two_blocks(int direction, int start_y, int start_x) {
    int next_y1 = start_y;
    int next_x1 = start_x;
    get_next_position(direction, next_y1, next_x1);

    int next_y2 = next_y1;
    int next_x2 = next_x1;
    get_next_position(direction, next_y2, next_x2);

    return can_move_in_block(next_y1, next_x1) && can_move_in_block(next_y2, next_x2);
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
        current_enemy->get_x()
    )) {
        current_enemy->set_direction(new_direction);
        can_cross = true;
    } else {
        // check if can cross in the other direction
        int new_direction = (current_enemy->get_direction() + 3) % 4;

        if (can_move_in_next_two_blocks(
            new_direction, 
            current_enemy->get_y(), 
            current_enemy->get_x()
        )) {
            current_enemy->set_direction(new_direction);
            can_cross = true;
        }
    }

    return can_cross;
}

bool are_entities_in_same_position(Entity entity_1, Entity entity_2) {
    return entity_1.get_x() == entity_2.get_x() 
        && entity_1.get_y() == entity_2.get_y();
}

void death() {
    player.set_is_moving(false);
    player.decrease_life();
    refresh_stats(info_win, player, coins);

    destroy_map_with_animation(game_win);
    if (player.get_life() > 0) {
        load_random_map(true, true);
        wrefresh(game_win);
    } else {
        // game over
        switch (show_game_over_screen(game_win)) {
            case 0:
                new_game();
                break;
            case 1:
                endwin();
                exit(0);
                break;
        }
    }
}

void move_enemies() {
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
                death();
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
                if (!can_move_in_block(next_y, next_x)) {
                    current_enemy->set_direction(
                        get_random_enemy_direction(
                            default_maps[current_map_index], 
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
                    death();
                }
            } else enemy_list_iterator = enemy_list_iterator->next;
        }
    }
}

void create_bullet() {
    int bullet_y = player.get_y();
    int bullet_x = player.get_x();
    get_next_position(player.get_direction(), bullet_y, bullet_x);
    
    if (can_move_in_block(bullet_y, bullet_x)) {
        Entity new_bullet = Entity(
            bullet_y, bullet_x, 
            player.get_direction()
        );

        add_bullet(current_bullet_list, new_bullet);
    }
}

void move_bullets() {
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
                )) valid_bullet = false;
                else add_enemy(
                    new_enemy_list, 
                    enemy_list_iterator->current_enemy
                );

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
            if (can_move_in_block(next_y, next_x)) {
                current_bullet->set_y(next_y);
                current_bullet->set_x(next_x);
            } else valid_bullet = false;

            // check if bullet is in enemy position after moving
            enemy_node *new_enemy_list_after_moving = new_enemy_list;
            new_enemy_list = NULL;
            while (enemy_list_iterator != NULL) {
                if (!are_entities_in_same_position(
                    *current_bullet, 
                    enemy_list_iterator->current_enemy
                )) valid_bullet = false;
                else add_enemy(
                    new_enemy_list_after_moving, 
                    enemy_list_iterator->current_enemy
                );

                enemy_node *tmp_enemy = enemy_list_iterator;
                enemy_list_iterator = enemy_list_iterator->next;
                delete tmp_enemy;
            }

            if (valid_bullet) {
                add_bullet(new_bullet_list, *current_bullet);
                mvwaddch(game_win, next_y, next_x, '.');
            }

            // set new list to enemy list
            current_enemy_list = new_enemy_list_after_moving;

            bullet_node *tmp_bullet = bullet_list_iterator;
            bullet_list_iterator = bullet_list_iterator->next;
            delete tmp_bullet;
        }

        // set new list to bullet list
        current_bullet_list = new_bullet_list;
    }
}

void start_game_loop() {
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
                                default_maps[current_map_index], 
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
                display_coins(game_win, current_coin_list);
                move_enemies();
            }

            move_bullets();

            if (tick == move_player_enemies_tick) {
                move_player();
                display_player(game_win, player);
            }

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

/* Main method */

int main() {
    srand(time(0));

    // start ncurses
    initscr();
    curs_set(0); // cursor invisible
    noecho(); // don't print input
    nodelay(stdscr, true); // don't stop the program on getch()
    create_colors(); // create color pairs

    // create the 6 default_maps and show splash screen
    create_default_maps(default_maps);

    show_splash_screen();

    // start game
    game_win = create_game_window();
    info_win = create_info_window(game_win);

    new_game();

    start_game_loop();

    return 0;
}
