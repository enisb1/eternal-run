/* Includes */

#include <ncursesw/ncurses.h>

#include "graphics.hpp"
#include "map.hpp"

/* Game window */

WINDOW *create_game_window(
        int game_win_height, 
        int game_win_width, 
        int info_win_width
    ) {
    // create game window by centering it in terminal
    int stdscr_maxy, stdscr_maxx;
    getmaxyx(stdscr, stdscr_maxy, stdscr_maxx);

    int game_win_begy = (stdscr_maxy - game_win_height) / 2;
    int game_win_begx = (stdscr_maxx - (game_win_width + info_win_width)) / 2 - 2;

    WINDOW *new_win = newwin(
        game_win_height, game_win_width, 
        game_win_begy, game_win_begx
    );
    box(new_win, 0, 0);

    refresh();
    wrefresh(new_win);

    return new_win;
}

void showSplashScreen(WINDOW *win) {
    wclear(win);
    box(win, 0, 0);

    // print game name

    // print "Premi un tasto per giocare" and wait for an input
    unsigned const int BLINK_PERIOD = 60;
    unsigned int tick = 0;
    int visible = 0;
    int exit_splash_screen = 0;
    while (!exit_splash_screen) {
        char c = wgetch(win);
        
        // if char entered exit the loop, otherwise blink the text
        if (c != -1) exit_splash_screen = 1;
        else if (tick == BLINK_PERIOD) {
            if (visible == 0) {
                mvwprintw(win, 13, 23, "Premi un tasto");
                visible = 1;
            } else {
                mvwprintw(win, 13, 23, "              ");
                visible = 0;
            }

            refresh();
            wrefresh(win);
        }

        // increment tick
        if (tick >= BLINK_PERIOD) tick = 0;
        else tick++;

        napms(10);
    }
}

void display_map(WINDOW *win, map *map, coin *cHead) {
    wclear(win);
    wattron(win, COLOR_PAIR(WALL_PAIR));
    wborder(win, '#', '#', '#', '#', '#', '#', '#', '#');
    wattroff(win, COLOR_PAIR(WALL_PAIR));

    // display the map with an animation
    unsigned int tick = 0;
    const unsigned int ANIM_PERIOD = 10;
    int row = 20;

    while (row >= 0) {
        if (tick == ANIM_PERIOD) {
            // display current row
            for (int col = 0; col < 60; col++) {
                wmove(win, row, col);
                int current_block = (map -> blocks)[row][col];
                if (current_block != EMPTY_BLOCK) {
                    switch (current_block) {
                        case WALL_BLOCK:
                            wattron(win, COLOR_PAIR(WALL_PAIR));
                            waddch(win, '#');
                            wattroff(win, COLOR_PAIR(WALL_PAIR));
                            break;
                        case ENTRANCE_BLOCK:
                            waddch(win, ' ');
                            break;
                        case EXIT_BLOCK:
                            waddch(win, ' ');
                            break;
                    }
                }
            }

            refresh();
            wrefresh(win);

            row--;
        }

        // increment tick
        if (tick >= ANIM_PERIOD) tick = 0;
        else tick++;

        napms(1);
    }

    coin *iterator = cHead;
	while (iterator!=NULL) {
		wmove(win, iterator->y, iterator->x);
		wattron(win, COLOR_PAIR(YELLOW_PAIR));
		waddch(win, '*');
		wattroff(win, COLOR_PAIR(YELLOW_PAIR));
		iterator = iterator->next;
	}

    refresh();
    wrefresh(win);
}

/* Info window */

void refresh_title(WINDOW *info_win, int level) {
    mvwprintw(info_win, 1, 2, "LEVEL %d", level);

    refresh();
    wrefresh(info_win);
}

void refresh_stats(
        WINDOW *info_win,
        int life, 
        int money
    ) {
    wattron(info_win, COLOR_PAIR(RED_PAIR));
    mvwprintw(info_win, 3, 2, "LIFE: %d", life);
    wattroff(info_win, COLOR_PAIR(RED_PAIR));
    
    wattron(info_win, COLOR_PAIR(YELLOW_PAIR));
    mvwprintw(info_win, 4, 2, "MONEY: %d", money);
    wattron(info_win, COLOR_PAIR(YELLOW_PAIR));

    refresh();
    wrefresh(info_win);
}

WINDOW *create_info_window(
        WINDOW *game_win,
        int game_win_height, 
        int game_win_width, 
        int info_win_width
    ) {
    // get stats window coordinates: aligned to game window
    int stdscr_maxy, stdscr_maxx;
    getmaxyx(stdscr, stdscr_maxy, stdscr_maxx);
    int game_win_begy = getbegy(game_win);
    int game_win_maxx = getmaxx(game_win);

    int info_win_begy = game_win_begy;
    int info_win_begx = game_win_maxx + 
        (stdscr_maxx - (game_win_width + info_win_width)) / 2 + 2;

    // create stats window
    WINDOW *new_win = newwin(
        game_win_height, info_win_width,
        info_win_begy, info_win_begx
    );
    box(new_win, 0, 0);

    // print dividers
    mvwprintw(new_win, 2, 1, "----------------");
    mvwprintw(new_win, 5, 1, "----------------");

    // refresh
    refresh();
    wrefresh(new_win);

    return new_win;
}
