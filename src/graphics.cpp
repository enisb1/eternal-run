/* Includes */

#include <ncursesw/ncurses.h>
#include <cstring>

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

    nodelay(game_win, true); // don't stop the program on getch()
    keypad(game_win, true); // enable keypad inputs

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
    bool visible = false;
    bool exit_splash_screen = false;

    while (!exit_splash_screen) {
        char c = wgetch(game_win);
        
        // if char entered exit the loop, otherwise blink the text
        if (c != -1) exit_splash_screen = true;
        else if (tick == BLINK_PERIOD) {
            if (visible) {
                mvwprintw(game_win, 13, 23, "              ");
                visible = false;
            } else {
                mvwprintw(game_win, 13, 23, "Premi un tasto");
                visible = 1;
            }

            wrefresh(game_win);
        }

        // increment tick
        if (tick >= BLINK_PERIOD) tick = 0;
        else tick++;

        napms(10);
    }
}

void show_menu(
    WINDOW *game_win, 
    char options[][50], 
    int options_length, 
    int starty, 
    int selected_option
    ) {
    for (int i = 0; i < options_length; i++) {
        int y = starty + i * 2;
        int x = (getmaxx(game_win) - strlen(options[i])) / 2;
        
        if (i == selected_option) {
            wattron(game_win, A_REVERSE);
            mvwprintw(game_win, y, x, "- %s", options[i]);
            wattroff(game_win, A_REVERSE);
        } else mvwprintw(game_win, y, x, "- %s", options[i]);
    }

    wrefresh(game_win);
}

void destroy_map(WINDOW *game_win) {
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

            wrefresh(game_win);

            row--;
        }

        // increment tick
        if (tick >= ANIM_PERIOD) tick = 0;
        else tick++;

        napms(1);
    }
}

void print_game_over_text(WINDOW *game_win, int COLOR_PAIR_NUM) {
    mvwprintw(game_win, 4, 3, ".d88b                          .d88b.");
    mvwprintw(game_win, 5, 3, "8P www .d88 8d8b.d8b. .d88b    8P  Y8 Yb  dP .d88b 8d8b");
    mvwprintw(game_win, 6, 3, "8b  d8 8  8 8P Y8P Y8 8.dP'    8b  d8  YbdP  8.dP' 8P   ");
    mvwprintw(game_win, 7, 3, "`Y88P' `Y88 8   8   8 `Y88P    `Y88P'   YP   `Y88P 8    ");
}

int show_game_over_screen(WINDOW *game_win) {
    wclear(game_win);

    // create menu options array
    char menu_options[2][50] = {};
    strcpy(menu_options[0], "Nuova partita");
    strcpy(menu_options[1], "Esci dal gioco");

    // show game over text
    print_game_over_text(game_win, WALL_PAIR);

    // show menu and start menu cicle
    int selected_option = 0;
    show_menu(game_win, menu_options, 2, 12, selected_option);

    int exit_game_over_screen = 0;
    while (!exit_game_over_screen) {
        char c = wgetch(game_win);

        // check if key entered
        if (c != -1) {
            switch (c) {
                case 2:
                    // increase selected option
                    if (selected_option < 1) selected_option++;
                    else selected_option = 0;
                    show_menu(game_win, menu_options, 2, 12, selected_option);
                    break;
                case 3:
                    // decrease selected option
                    if (selected_option > 0) selected_option--;
                    else selected_option = 1;
                    show_menu(game_win, menu_options, 2, 12, selected_option);
                    break;
                case 10:
                    // enter option
                    exit_game_over_screen = true;
            }
        }

        napms(10);
    }

    return selected_option;
}

/* Info window */

void refresh_title(WINDOW *info_win, char *title) {
    mvwprintw(info_win, 1, 2, "%s", title);
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
    wattroff(info_win, COLOR_PAIR(YELLOW_PAIR));

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

    wrefresh(info_win);

    return info_win;
}
