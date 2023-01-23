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

/* void death() {
    // -1 life & refresh stats
    life--;
    refresh_stats(life, money);

    // show death screen
    unsigned const int DEATH_SCREEN_DURATION = 200;
    unsigned int tick = 0;
    int exit_death_screen = 0;
    while (!exit_death_screen) {
        if (tick == DEATH_SCREEN_DURATION)
            exit_death_screen = 1;

        // increment tick
        if (tick >= DEATH_SCREEN_DURATION) tick = 0;
        else tick++;

        napms(10);
    }

    // replace with next level method
} */

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
    int i = 0;
    while (1) {
        char c = wgetch(game_win);
        if (c != -1) {
            i++;
            display_map(game_win, maps[i]);
        }
    };

    return 0;
}