/* Includes */

#include <ncursesw/ncurses.h>

#include "graphics.hpp"
#include "map.hpp"

/* Vars */

const int GAME_WIN_HEIGHT = 20;
const int GAME_WIN_WIDTH = 60;
const int INFO_WIN_WIDTH = 18;

/* Game window */

WINDOW *create_game_window() {
    // create game window by centering it in terminal
    int stdscr_maxy, stdscr_maxx;
    getmaxyx(stdscr, stdscr_maxy, stdscr_maxx);

    const int GAME_WIN_BEGY = (stdscr_maxy - GAME_WIN_HEIGHT) / 2;
    const int GAME_WIN_BEGX = (stdscr_maxx - GAME_WIN_WIDTH) / 2;

    WINDOW *game_win = newwin(
        GAME_WIN_HEIGHT, GAME_WIN_WIDTH, 
        GAME_WIN_BEGY, GAME_WIN_BEGX
    );
    box(game_win, 0, 0);

    wtimeout(game_win, 0); // don't stop the program on getch()

    refresh();
    wrefresh(game_win);

    return game_win;
}

void move_game_window(WINDOW *game_win) {
    wclear(game_win);
    wrefresh(game_win);

    int stdscr_maxy, stdscr_maxx;
    getmaxyx(stdscr, stdscr_maxy, stdscr_maxx);

    int GAME_WIN_BEGY = (stdscr_maxy - GAME_WIN_HEIGHT) / 2;
    int GAME_WIN_BEGX = (stdscr_maxx - (GAME_WIN_WIDTH + INFO_WIN_WIDTH)) / 2 - 2;

    mvwin(game_win, GAME_WIN_BEGY, GAME_WIN_BEGX);
    wrefresh(game_win);
}

void show_splash_screen(WINDOW *game_win) {
    wclear(game_win);
    box(game_win, 0, 0);

    // print game name

    // print "Premi un tasto" and wait for an input
    unsigned const int BLINK_PERIOD = 60;
    unsigned int tick = 0;
    int visible = 0;
    int exit_splash_screen = 0;

    while (!exit_splash_screen) {
        char c = wgetch(game_win);
        
        // if char entered exit the loop, otherwise blink the text
        if (c != -1) exit_splash_screen = 1;
        else if (tick == BLINK_PERIOD) {
            if (visible == 0) {
                mvwprintw(game_win, 13, 23, "Premi un tasto");
                visible = 1;
            } else {
                mvwprintw(game_win, 13, 23, "              ");
                visible = 0;
            }

            refresh();
            wrefresh(game_win);
        }

        // increment tick
        if (tick >= BLINK_PERIOD) tick = 0;
        else tick++;

        napms(10);
    }
}

void display_map(WINDOW *game_win, map *map) {
    wclear(game_win);
    wattron(game_win, COLOR_PAIR(WALL_PAIR));
    wborder(game_win, '#', '#', '#', '#', '#', '#', '#', '#');
    wattroff(game_win, COLOR_PAIR(WALL_PAIR));

    // display the map with an animation
    unsigned int tick = 0;
    const unsigned int ANIM_PERIOD = 10;
    int row = 20;

    while (row >= 0) {
        if (tick == ANIM_PERIOD) {
            // display current row
            for (int col = 0; col < 60; col++) {
                wmove(game_win, row, col);
                int current_block = (map -> blocks)[row][col];

                if (current_block != EMPTY_BLOCK) {
                    switch (current_block) {
                        case WALL_BLOCK:
                            wattron(game_win, COLOR_PAIR(WALL_PAIR));
                            waddch(game_win, '#');
                            wattroff(game_win, COLOR_PAIR(WALL_PAIR));
                            break;
                        case COIN_BLOCK:
                            wattron(game_win, COLOR_PAIR(YELLOW_PAIR));
                            waddch(game_win, '*');
                            wattroff(game_win, COLOR_PAIR(YELLOW_PAIR));
                            break;
                        case ENTRANCE_BLOCK:
                            waddch(game_win, ' ');
                            break;
                        case EXIT_BLOCK:
                            waddch(game_win, ' ');
                            break;
                    }
                }
            }

            refresh();
            wrefresh(game_win);

            row--;
        }

        // increment tick
        if (tick >= ANIM_PERIOD) tick = 0;
        else tick++;

        napms(1);
    }

    refresh();
    wrefresh(game_win);
}

/* Info window */

void refresh_title(WINDOW *info_win, char *title) {
    mvwprintw(info_win, 1, 2, "%s", title);

    refresh();
    wrefresh(info_win);
}

void refresh_stats(WINDOW *info_win, int life, int money) {
    // life
    wattron(info_win, COLOR_PAIR(RED_PAIR));
    mvwprintw(info_win, 3, 2, "LIFE: %d", life);
    wattroff(info_win, COLOR_PAIR(RED_PAIR));
    
    // money
    wattron(info_win, COLOR_PAIR(YELLOW_PAIR));
    mvwprintw(info_win, 4, 2, "MONEY: %d", money);
    wattron(info_win, COLOR_PAIR(YELLOW_PAIR));

    refresh();
    wrefresh(info_win);
}

WINDOW *create_info_window(WINDOW *game_win) {
    // get stats window coordinates: aligned to game window
    int stdscr_maxy, stdscr_maxx;
    getmaxyx(stdscr, stdscr_maxy, stdscr_maxx);
    int game_win_begy = getbegy(game_win);
    int game_win_maxx = getmaxx(game_win);

    const int INFO_WIN_BEGY = game_win_begy;
    const int INFO_WIN_BEGX = game_win_maxx + 
        (stdscr_maxx - (GAME_WIN_WIDTH + INFO_WIN_WIDTH)) / 2 + 2;

    // create stats window
    WINDOW *info_win = newwin(
        GAME_WIN_HEIGHT, INFO_WIN_WIDTH,
        INFO_WIN_BEGY, INFO_WIN_BEGX
    );
    box(info_win, 0, 0);

    // print dividers
    mvwprintw(info_win, 2, 1, "----------------");
    mvwprintw(info_win, 5, 1, "----------------");

    // refresh
    refresh();
    wrefresh(info_win);

    return info_win;
}
