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

int life;
int shield;
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
    int next_map_index = 3;
	while (next_map_index == current_map_index) next_map_index = rand() % 6;
	current_map_index = next_map_index;

    // get coins list based on current map index
    current_coin_list = default_maps[current_map_index]->coin_list;

    // display new level map
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

void new_game() {
    // initialize vars
    life = 3;
    shield = 0;
    coins = 0;
    level = 0;

    srand(time(0));
    
    // refresh stats
    refresh_stats(info_win, life, shield, coins);

    // TODO: new level (replace with random level)
    load_next_level();
}

void collect_coin(int y, int x) {
    // find the coin in the list, remove it and set blank char in that position
    if (current_coin_list != NULL) {
        if (current_coin_list->y == y && current_coin_list->x == x) {
            set_blank_char(game_win, current_coin_list->y, current_coin_list->x);
            coin *tmp = current_coin_list; 
            current_coin_list = current_coin_list->next;
            delete tmp;
        } else {
            bool found = false;
            coin *previous_coin = current_coin_list;
            coin *current_coin = current_coin_list->next;

            while (current_coin != NULL && !found) {
                if (current_coin->y == y && current_coin->x == x) {
                    set_blank_char(game_win, current_coin->y, current_coin->x);
                    coin *tmp = current_coin;
                    previous_coin = current_coin->next;
                    delete tmp;
                    found = true; 
                } else {
                    previous_coin = current_coin; 
                    current_coin = previous_coin->next; 
                }
            }
        }
    }

    // refresh
    wrefresh(game_win);
}

void death() {
    life--;
    refresh_stats(info_win, life, shield, coins);

    destroy_map_with_animation(game_win);
    if (life > 0) load_random_level();
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
        char c = wgetch(game_win);
        
        if (tick == ANIM_PERIOD) {
            if (c != -1) {
                switch (c) {
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

            tick = 0; 
        }
        else tick++;
    };

    return 0;
}
