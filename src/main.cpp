/* Includes */

#include <ncursesw/ncurses.h>
#include <cstring>

#include "graphics.hpp"
#include "map.hpp"

/* Vars */
WINDOW *game_win;
WINDOW *info_win;

map *maps[6];
char title[25];
int life = 3;
int money = 0;

/* Main method */

void create_colors() {
    if (has_colors()) start_color();

    init_pair(WALL_PAIR, COLOR_WHITE, COLOR_BLUE);
    init_pair(RED_PAIR, COLOR_RED, 0);
    init_pair(YELLOW_PAIR, COLOR_YELLOW, 0);
}

void death() {
    life--;
    refresh_stats(info_win, life, money);

    // destroy current map animation
    unsigned int tick = 0;
    const unsigned int ANIM_PERIOD = 10;
    int row = 1;

    while (row < 19) {
        if (tick == ANIM_PERIOD) {
            // destroy current line
            mvwprintw(game_win, row, 1, "                                                          ");
            wrefresh(game_win);

            row++;
        }

        // increment tick
        if (tick >= ANIM_PERIOD) tick = 0;
        else tick++;

        napms(1);
    }
    
    // TODO: replace with random level
    display_map(game_win, maps[1]);
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

    display_map(game_win, maps[0]);
    
    strcpy(title, "LEVEL 1");
    refresh_title(info_win, title);
    refresh_stats(info_win, life, money);

    // test death
    while (1) {
        char c = wgetch(game_win);
        if (c != -1) death();
    };

    return 0;
}