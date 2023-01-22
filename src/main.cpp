/* Includes */

#include <ncursesw/ncurses.h>
#include <cstring>

#include "graphics.hpp"
#include "map.hpp"

/* Vars */

const int game_win_height = 20;
const int game_win_width = 60;
const int info_win_width = 18;

char title[25];
int life = 3;
int money = 0;

/* Main method */

int main() {
    // start ncurses
    initscr();
    noecho();
    cbreak();
    
    // start colors
    if (has_colors()) start_color();

    init_pair(WALL_PAIR, COLOR_WHITE, COLOR_BLUE);
    init_pair(RED_PAIR, COLOR_RED, 0);
    init_pair(YELLOW_PAIR, COLOR_YELLOW, 0);

    // sets cursor state to invisible
    curs_set(0);

    // create windows
    strcpy(title, "LEVEL 1");

    WINDOW *game_win = create_game_window(
        game_win_height, 
        game_win_width, 
        info_win_width
    );
    WINDOW *info_win = create_info_window(
        game_win,
        game_win_height, 
        game_win_width, 
        info_win_width
    );

    wtimeout(game_win, 0);

    // create the 6 maps
    map *maps[6];
    create_maps(maps);
    
    showSplashScreen(game_win);

    display_map(game_win, maps[0]);
    refresh_title(info_win, title);
    refresh_stats(info_win, life, money);

    while (1) {

    }

    return 0;
}