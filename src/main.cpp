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
    cbreak();

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

    // refresh info and create first map
    refresh_title(info_win, title);
    refresh_stats(info_win, life, money);

    map *map1 = create_map();
    display_map(game_win, map1);

    getch();
    endwin();

    return 0;
}