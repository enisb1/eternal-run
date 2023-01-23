/* Includes */

#include <ncursesw/ncurses.h>

#include <cstring>
#include <ctime>
#include <cstdlib>

#include "graphics.hpp"
#include "map.hpp"

/* Vars */

const int game_win_height = 20;
const int game_win_width = 60;
const int info_win_width = 18;

int level = 1;
int life = 3;
int money = 0;
int currentMapIndex = 0;

/* Methods */

void loadNextLevel(WINDOW *info_win, WINDOW *game_win, map *maps[], coin *cLists[]) {
	level++;
	refresh_title(info_win, level);

	int nextMapIndex = rand()%6;
	while (nextMapIndex == currentMapIndex) nextMapIndex = rand()%6;
	currentMapIndex = nextMapIndex;

	display_map(game_win, maps[currentMapIndex], cLists[currentMapIndex]);
}

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

    // get array containing each map's coins list
    coin *cLists[6];
    create_coins_lists(cLists);

    // set a random number to map index
    srand(time(0));
    currentMapIndex = rand()%6;
    
    showSplashScreen(game_win);

    display_map(game_win, maps[currentMapIndex], cLists[currentMapIndex]);
    refresh_title(info_win, level);
    refresh_stats(info_win, life, money);

    while (1) {

    }

    return 0;
}
