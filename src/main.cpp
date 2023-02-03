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

Player player = Player(0, 0, 0, 0, 0, false);

int coins;
int level;

map *default_maps[6];
int current_map_index = 0;
coin *current_coin_list = NULL;

/* Methods */

void create_colors() {
    if (has_colors()) start_color();

    init_pair(WALL_PAIR, COLOR_WHITE, COLOR_BLUE);
    init_pair(RED_PAIR, COLOR_RED, 0);
    init_pair(CYAN_PAIR, COLOR_CYAN, 0);
    init_pair(YELLOW_PAIR, COLOR_YELLOW, 0);
}

void load_random_level() {
    // get a new random index
    int next_map_index = rand() % 6;
	while (next_map_index == current_map_index) next_map_index = rand() % 6;
	current_map_index = 2;

    // get coins list based on current map index
    current_coin_list = default_maps[current_map_index]->coin_list;

    // display new level map and player
	display_map_with_anim(game_win, default_maps[current_map_index]);
}

void load_next_level() {
    //TODO: save previous level's data in a file

    // increment vars
    level++;
	refresh_title(info_win, level, true);

    // load a new level based on a random index
	load_random_level();
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

void new_game() {
    // initialize vars
    coins = 0;
    level = 0;

    srand(time(0));

    // load next level
    load_next_level();
    
    // create and display player
    player = Player(
        default_maps[current_map_index]->entrance_exit_positions[0],
        default_maps[current_map_index]->entrance_exit_positions[1],
        get_player_starting_direction(),
        3, 0, false
    );

    display_player(game_win, player);
    
    // refresh stats
    refresh_stats(info_win, player, coins);
}

bool collect_coin(int y, int x) {
    // if coin in list -> coin removed, coin counter incremented, return=True
    // else return=False
    bool found = false;

    if (current_coin_list != NULL) {
        if (current_coin_list->y == y && current_coin_list->x == x) {
            set_blank_char(game_win, current_coin_list->y, current_coin_list->x);
            coin *tmp = current_coin_list; 
            current_coin_list = current_coin_list->next;
            delete tmp;
            found = true;
        } else {
            coin *previous_coin = current_coin_list;
            coin *current_coin = current_coin_list->next;
            while (current_coin != NULL && !found) {
                if (current_coin->y == y && current_coin->x == x) {
                    set_blank_char(game_win, current_coin->y, current_coin->x);
                    coin *tmp = current_coin;
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
        // refresh
        refresh_stats(info_win, player, coins);
        wrefresh(game_win);
    }

    return found;
}

void move_player() {
    // check if next block is a wall
    int new_y = player.get_y();
    int new_x = player.get_x();

    switch (player.get_direction()) {
        case DOWN:
            new_y++;
            break;
        case UP:
            new_y--;
            break;
        case RIGHT:
            new_x++;
            break;
        case LEFT:
            new_x--;
            break;
    }

    if (default_maps[current_map_index]->blocks[new_y][new_x] != WALL_BLOCK) {
        set_blank_char(game_win, player.get_y(), player.get_x());
        player.set_y(new_y);
        player.set_x(new_x);

        bool is_coin = collect_coin(new_y, new_x);
        if (!is_coin) {
            if (default_maps[current_map_index]->blocks[new_y][new_x] == ENTRANCE_BLOCK) {
            // previous level
            } else if (default_maps[current_map_index]->blocks[new_y][new_x] == EXIT_BLOCK) {
            // new level
            }
        }
    }
    
    // display player in new block
    display_player(game_win, player);
}

void death() {
    player.decrease_life();
    refresh_stats(info_win, player, coins);

    destroy_map_with_animation(game_win);
    if (player.get_life() > 0) load_random_level();
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

    // game loop
    unsigned int tick = 0;
    const unsigned int ANIM_PERIOD = 1;

    while (1) {
        int c = wgetch(game_win);

        if (c != -1) {
            switch (c) {
                case KEY_DOWN:
                    player.set_direction(DOWN);
                    move_player();
                    break;
                case KEY_UP:
                    player.set_direction(UP);
                    move_player();
                    break;
                case KEY_RIGHT:
                    player.set_direction(RIGHT);
                    move_player();
                    break;
                case KEY_LEFT:
                    player.set_direction(LEFT);
                    move_player();
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

        napms(10);
    };

    return 0;
}
