/* Includes */

#include <ncursesw/ncurses.h>

#include <ctime>
#include <cstdlib>

#include "graphics.hpp"
#include "game.hpp"
#include "storing.hpp"

using namespace std; 

/* Vars */

WINDOW *game_win;
WINDOW *info_win;

/* Methods */

void create_colors() {
    if (has_colors()) start_color();

    init_pair(WALL_PAIR, COLOR_WHITE, COLOR_BLUE);
    init_pair(RED_PAIR, COLOR_RED, 0);
    init_pair(CYAN_PAIR, COLOR_CYAN, 0);
    init_pair(YELLOW_PAIR, COLOR_YELLOW, 0);
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

    // delete storing files in case user previously left before game over
    delete_files();
    
    show_splash_screen();

    create_maps();

    // start game 
    game_win = create_game_window();
    info_win = create_info_window(game_win);

    new_game(game_win, info_win);

    start_game_loop(game_win, info_win);

    return 0;
}
