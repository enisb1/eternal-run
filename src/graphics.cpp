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

    WINDOW *new_win = newwin(
        game_win_height, game_win_width, 
        (stdscr_maxy - game_win_height) / 2,     
        (stdscr_maxx - (game_win_width + info_win_width)) / 2
    );
    wborder(new_win, '#', '#', '#', '#', '#', '#', '#', '#');

    refresh();
    wrefresh(new_win);

    return new_win;
}

char getChar(int type) {
	char retChar;

	switch (type) {
	case 1:
		retChar = ' ';
		break;
	case 2:
		retChar = ' ';
		break;
	case 3:
		retChar = '#';
		break;
	}

	return retChar;
}

void display_map(WINDOW *win, map *map) {
    for (int i = 0; i < map -> num_blocks; i++) {
        block current_block = (map -> blocks)[i];
        char symbol = getChar(current_block.type);
        mvwaddch(win, current_block.y, current_block.x, symbol);
    }

    refresh();
    wrefresh(win);
}

/* Info window */

void refresh_title(WINDOW *info_win, char *title) {
    mvwprintw(info_win, 1, 2, "%s", title);

    refresh();
    wrefresh(info_win);
}

void refresh_stats(
        WINDOW *info_win,
        int life, 
        int money
    ) {
    mvwprintw(info_win, 3, 2, "LIFE: %d", life);
    mvwprintw(info_win, 4, 2, "MONEY: %d", money);

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
        (stdscr_maxx - (game_win_width + info_win_width)) / 2;

    // create stats window
    WINDOW *new_win = newwin(
        game_win_height, info_win_width,
        info_win_begy,
        info_win_begx
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
