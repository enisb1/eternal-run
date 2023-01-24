/* Includes */

#include <ncursesw/ncurses.h>
#include <stdlib.h>
#include <cstring>

#include "graphics.hpp"
#include "map.hpp"

/* Vars */
WINDOW *game_win;
WINDOW *info_win;

map *maps[6];
char title[25];
int life;
int money;

/* Main method */

void create_colors() {
    if (has_colors()) start_color();

    init_pair(WALL_PAIR, COLOR_WHITE, COLOR_BLUE);
    init_pair(RED_PAIR, COLOR_RED, 0);
    init_pair(YELLOW_PAIR, COLOR_YELLOW, 0);
}

void new_game() {
    // initialize vars
    strcpy(title, "LEVEL 1");
    life = 3;
    money = 0;

    // refresh
    refresh_title(info_win, title);
    refresh_stats(info_win, life, money);

    // TODO: new level (replace with random level)
    display_map(game_win, maps[0]);
}

void death() {
    life--;
    refresh_stats(info_win, life, money);

    destroy_map(game_win);
    if (life > 0) {
        // TODO: replace with random level
        display_map(game_win, maps[1]);
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

int main() {
    // start ncurses
    initscr();
    noecho(); // don't print input
    curs_set(0); // cursor invisible
    create_colors(); // create color pairs

    // create game window
    game_win = create_game_window();

    // create the 6 maps and show splash screen
    create_maps(maps);
    show_splash_screen(game_win);

    // start game
    move_game_window(game_win);
    info_win = create_info_window(game_win);

    new_game();

    // test
    while (1) {
        char c = wgetch(game_win);
        if (c != -1) death();
    };

    return 0;
}