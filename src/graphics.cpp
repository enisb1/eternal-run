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
    wattron(new_win, COLOR_PAIR(WALL_PAIR));
    wborder(new_win, '#', '#', '#', '#', '#', '#', '#', '#');
    wattroff(new_win, COLOR_PAIR(WALL_PAIR));

    refresh();
    wrefresh(new_win);

    return new_win;
}

void display_map(WINDOW *win, map *map) {
    wclear(win);
    wattron(win, COLOR_PAIR(WALL_PAIR));
    wborder(win, '#', '#', '#', '#', '#', '#', '#', '#');
    wattroff(win, COLOR_PAIR(WALL_PAIR));

    for (int i = 0; i < map -> num_blocks; i++) {
        block current_block = (map -> blocks)[i];

        wmove(win, current_block.y, current_block.x);
        switch (current_block.type) {
            case TYPE_WALL:
                wattron(win, COLOR_PAIR(WALL_PAIR));
                waddch(win, '#');
                wattroff(win, COLOR_PAIR(WALL_PAIR));
                break;
            case TYPE_COIN:
                wattron(win, COLOR_PAIR(YELLOW_PAIR));
                waddch(win, '*');
                wattroff(win, COLOR_PAIR(YELLOW_PAIR));
                break;
            case TYPE_ENTRANCE:
                waddch(win, ' ');
                break;
            case TYPE_EXIT:
                waddch(win, ' ');
                break;
        }
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
