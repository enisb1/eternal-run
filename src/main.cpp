/* Includes */

#include <ncursesw/ncurses.h>

#include <ctime>
#include <cstdlib>

#include "graphics.hpp"
#include "map.hpp"

using namespace std; 

/* Vars */

const int game_win_height = 20;
const int game_win_width = 60;
const int info_win_width = 18;

int level = 1;
int life = 3;
int money = 0;
int currentMapIndex = 0;
coin *currentCoinsList = NULL;

/* Methods */

void load_next_level(WINDOW *info_win, WINDOW *game_win, map *maps[], coin *cLists[]) {
	level++;
	refresh_title(info_win, level);

	int nextMapIndex = rand()%6;
	while (nextMapIndex == currentMapIndex) nextMapIndex = rand()%6;
	currentMapIndex = nextMapIndex;

    currentCoinsList = get_default_cList(currentMapIndex);
	display_map(game_win, maps[currentMapIndex], currentCoinsList);
    
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

    // set a random number to map index
    srand(time(0));
    currentMapIndex = rand()%6;

    // get coins list based on map index 
    currentCoinsList = get_default_cList(currentMapIndex);
    
    showSplashScreen(game_win);

    display_map(game_win, maps[currentMapIndex], currentCoinsList);
    refresh_title(info_win, level);
    refresh_stats(info_win, life, money);

    while (1) {

    }

    return 0;
}
