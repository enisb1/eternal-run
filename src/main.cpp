/* Includes */

#include <ncursesw/ncurses.h>
#include <stdlib.h>
#include <cstring>

#include <ctime>
#include <cstdlib>

#include "graphics.hpp"
#include "map.hpp"

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

map *maps[6];
int map_index = 0;
coin *coin_list = NULL;

/* Methods */

void create_colors() {
    if (has_colors()) start_color();

    init_pair(WALL_PAIR, COLOR_WHITE, COLOR_BLUE);
    init_pair(RED_PAIR, COLOR_RED, 0);
    init_pair(CYAN_PAIR, COLOR_CYAN, 0);
    init_pair(YELLOW_PAIR, COLOR_YELLOW, 0);
}

void new_game() {
    // initialize vars
    life = 3;
    shield = 0;
    coins = 0;
    level = 1; 

    // set a random number(0-5) to map index
    srand(time(0));
    map_index = rand() % 6;

    // get coins list based on map index 
    coin_list = maps[map_index]->coin_list;
    
    // refresh
    refresh_title(info_win, level);
    refresh_stats(info_win, life, shield, coins);

    // TODO: new level (replace with random level)
    display_map_with_anim(game_win, maps[map_index], coin_list);
}

void load_next_level(WINDOW *info_win, WINDOW *game_win, map *maps[], coin *cLists[]) {
	level++;
	refresh_title(info_win, level);

	int nextMapIndex = rand()%6;
	while (nextMapIndex == map_index) nextMapIndex = rand()%6;
	map_index = nextMapIndex;

    coin_list = maps[map_index]->coin_list;
	display_map(game_win, maps[map_index], coin_list);
    
    //TODO: save previous level's data in a file
}

void set_blank_char(WINDOW *window, int y, int x) {
    wmove(window, y, x);
    waddch(window, ' ');
}

coin *collect_coin(WINDOW *window, coin *head, int y, int x) {
    // find the coin in the list, remove it and set blank char in that position
    if (head!=NULL) {
        if (head->y == y && head->x == x) {
            set_blank_char(window, head->y, head->x);
            coin *tmp = head; 
            head = head->next; 
            delete tmp;
        } else {
            bool found = false;
            coin *prevPtr = head; 
            coin *ptr = head->next; 
            while (ptr!=NULL && !found) {
                if (ptr->y == y && ptr->x == x) {
                    set_blank_char(window, ptr->y, ptr->x);
                    coin *tmp = ptr;
                    prevPtr = ptr->next;
                    delete tmp; 
                    ptr = prevPtr->next;
                    found = true; 
                }
                else {
                    prevPtr = ptr; 
                    ptr = prevPtr->next; 
                }
            }
        }
    }

    // refresh game window
    refresh();
    wrefresh(window);

    return head; 
}

void death() {
    life--;
    refresh_stats(info_win, life, shield, coins);

    destroy_map_with_animation(game_win);
    if (life > 0) {
        // TODO: replace with random level
        display_map_with_anim(game_win, maps[1], coin_list);
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

/* Main method */

int main() {
    // start ncurses
    initscr();
    curs_set(0); // cursor invisible
    noecho(); // don't print input
    nodelay(stdscr, true); // don't stop the program on getch()
    create_colors(); // create color pairs

    // create the 6 maps and show splash screen
    create_maps(maps);

    show_splash_screen();

    // start game
    game_win = create_game_window();
    info_win = create_info_window(game_win);

    new_game();

    // game loop
    while (1) {
        char c = wgetch(game_win);
        
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
    };

    return 0;
}
