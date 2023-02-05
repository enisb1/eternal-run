/* Includes */

#include <ncursesw/ncurses.h>
#include <stdlib.h>
#include <cstring>

#include <ctime>
#include <cstdlib>

#include "graphics.hpp"
#include "map.hpp"
#include "entities.hpp"

using namespace std; 

/* Vars */

WINDOW *game_win;
WINDOW *info_win;
const int game_win_height = 20;
const int game_win_width = 60;
const int info_win_width = 18;

Player player;
enemy_node *current_enemy_list = NULL;

int coins;
int level;

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

int get_player_starting_direction() {
    int direction;

    if (default_maps[current_map_index]->entrance_exit_positions[0] == 0)
        direction = DOWN;
    else if (default_maps[current_map_index]->entrance_exit_positions[0] == 19)
        direction = UP;
    else if (default_maps[current_map_index]->entrance_exit_positions[1] == 0)
        direction = RIGHT;
    else if (default_maps[current_map_index]->entrance_exit_positions[1] == 59)
        direction = LEFT;
    
    return direction;
}

void set_player_starting_properties() {
    player.set_y(default_maps[current_map_index]->entrance_exit_positions[0]);
    player.set_x(default_maps[current_map_index]->entrance_exit_positions[1]);
    player.set_direction(get_player_starting_direction());
    player.set_is_moving(false);
}

void delete_coin_list() {
    while (current_coin_list!=NULL) {
        coin_node *tmp = current_coin_list;
        current_coin_list = current_coin_list->next;
        delete tmp;
    }
}

void get_default_coin_list() {
    switch (current_map_index) {
        case 0:
            current_coin_list = create_coin_list_map1();
            break;
        case 1:
            current_coin_list = create_coin_list_map2();
            break;
        case 2:
            current_coin_list = create_coin_list_map3();
            break;
        case 3:
            current_coin_list = create_coin_list_map4();
            break;
        case 4:
            current_coin_list = create_coin_list_map5();
            break;
        case 5:
            current_coin_list = create_coin_list_map6();
            break;                       
    }
}

void load_random_map() {
    // get a new random index
    int next_map_index = rand() % 6;
	while (next_map_index == current_map_index) next_map_index = rand() % 6;
	current_map_index = next_map_index;

    // set a new default coin list to current_coin_list based on current map index
    delete_coin_list();
    get_default_coin_list();

    // display the new level's map
    if (level>=2) display_map(game_win, default_maps[current_map_index], current_coin_list);
	else display_map_with_anim(game_win, default_maps[current_map_index], current_coin_list);
}

void load_next_level() {
    //TODO: save previous level's data in a file

    // increment level
    level++;
	refresh_title(info_win, level, false);

    // load a new level based on a random index
	load_random_map();

    // set player's starting properties and display it
    set_player_starting_properties();
    display_player(game_win, player);

    // create enemy list and display it
    create_enemy_list(default_maps[current_map_index], player, current_enemy_list, level);
    display_enemies(game_win, current_enemy_list);
}

void new_game() {
    // initialize vars
    coins = 0;
    level = 0;

    srand(time(0));

    // create player
    player = Player(
        default_maps[current_map_index]->entrance_exit_positions[0],
        default_maps[current_map_index]->entrance_exit_positions[1],
        get_player_starting_direction(), false,
        3, 0, false
    );

    load_next_level();
    
    refresh_stats(info_win, player, coins);
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
    // check if next block is a wall
    int next_y = player.get_y();
    int next_x = player.get_x();
    get_next_position(player.get_direction(), next_y, next_x);

    if (default_maps[current_map_index]->blocks[next_y][next_x] != WALL_BLOCK) {
        set_blank_char(game_win, player.get_y(), player.get_x());
        player.set_y(next_y);
        player.set_x(next_x);

        bool is_coin = collect_coin(next_y, next_x);
        if (!is_coin) {
            if (default_maps[current_map_index]->blocks[next_y][next_x] == ENTRANCE_BLOCK) {
                // previous level
            } else if (default_maps[current_map_index]->blocks[next_y][next_x] == EXIT_BLOCK) {
                // new level
                load_next_level();
            }
        }
    }
    
    // display player in new block
    display_player(game_win, player);
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

void move_enemies() {
    enemy_node *enemy_list_iterator = current_enemy_list;

    while (enemy_list_iterator != NULL) {
        bool can_cross = false;

        if (enemy_list_iterator->current_enemy.get_blocks_traveled() > 8) {
            // check if can cross in one direction
            int new_direction = (enemy_list_iterator->current_enemy.get_direction() + 1) % 4;
            
            if (can_move_in_next_two_blocks(
                new_direction, 
                enemy_list_iterator->current_enemy.get_y(), 
                enemy_list_iterator->current_enemy.get_x()
            )) {
                enemy_list_iterator->current_enemy.set_direction(new_direction);
                can_cross = true;
            } else {
                // check if can cross in the other direction
                int new_direction = (enemy_list_iterator->current_enemy.get_direction() + 3) % 4;

                if (can_move_in_next_two_blocks(
                    new_direction, 
                    enemy_list_iterator->current_enemy.get_y(), 
                    enemy_list_iterator->current_enemy.get_x()
                    )
                ) {
                    enemy_list_iterator->current_enemy.set_direction(new_direction);
                    can_cross = true;
                }
            }
        }

        // get next blocks position based on current direction
        int next_y = enemy_list_iterator->current_enemy.get_y();
        int next_x = enemy_list_iterator->current_enemy.get_x();

        get_next_position(
            enemy_list_iterator->current_enemy.get_direction(), 
            next_y, next_x
        );

        // change enemy direction if next block is a wall
        if (can_cross) enemy_list_iterator->current_enemy.reset_blocks_traveled();
        else {
            if (!can_move_in_block(next_y, next_x)) {
                // if next block is a wall change to a random direction
                enemy_list_iterator->current_enemy.set_direction(
                    get_random_enemy_direction(
                        default_maps[current_map_index], 
                        enemy_list_iterator->current_enemy.get_y(),
                        enemy_list_iterator->current_enemy.get_x()
                    )
                );

                next_y = enemy_list_iterator->current_enemy.get_y();
                next_x = enemy_list_iterator->current_enemy.get_x();

                get_next_position(
                    enemy_list_iterator->current_enemy.get_direction(), 
                    next_y, next_x
                );
            }

            enemy_list_iterator->current_enemy.increment_blocks_traveled();
        }

        // move enemy
        set_blank_char(
            game_win, 
            enemy_list_iterator->current_enemy.get_y(), 
            enemy_list_iterator->current_enemy.get_x()
        );
        enemy_list_iterator->current_enemy.set_y(next_y);
        enemy_list_iterator->current_enemy.set_x(next_x);

        enemy_list_iterator = enemy_list_iterator->next;
    }

    display_enemies(game_win, current_enemy_list);
}

void death() {
    player.decrease_life();
    refresh_stats(info_win, player, coins);

    destroy_map_with_animation(game_win);
    if (player.get_life() > 0) load_random_map();
    else {
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

void start_game_loop() {
    unsigned int tick = 0;
    const unsigned int ANIM_PERIOD = 1;

    while (1) {
        int c = wgetch(game_win);

        if (c != -1) {
            switch (c) {
                case KEY_DOWN:
                    player.set_direction(DOWN);
                    if (!player.get_is_moving()) player.set_is_moving(true);
                    break;
                case KEY_UP:
                    player.set_direction(UP);
                    if (!player.get_is_moving()) player.set_is_moving(true);
                    break;
                case KEY_RIGHT:
                    player.set_direction(RIGHT);
                    if (!player.get_is_moving()) player.set_is_moving(true);
                    break;
                case KEY_LEFT:
                    player.set_direction(LEFT);
                    if (!player.get_is_moving()) player.set_is_moving(true);
                    break;
                case 27:
                    // esc
                    switch (show_esc_screen(game_win)) {
                        case 0:
                            endwin();
                            exit(0);
                            break;
                        case 1:
                            // resume_game();
                            break;
                    }
                    break;
            }
        }

        if (player.get_is_moving()) move_player();
        move_enemies();

        napms(160);
    };
}

/* Main method */

int main() {
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
