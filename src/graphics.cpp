/* Includes */

#include <ncursesw/ncurses.h>
#include <cstring>

#include "graphics.hpp"
#include "map.hpp"

/* Vars */

const int GAME_WIN_HEIGHT = 20;
const int GAME_WIN_WIDTH = 60;
const int INFO_WIN_WIDTH = 18;

/* Standard screen */

void print_game_name_text() {
    int x = (getmaxx(stdscr) - 87) / 2;
    // int x = (getmaxx(stdscr) - 78) / 2;
    // int x = (getmaxx(stdscr) - 54) / 2;
    int y = (getmaxy(stdscr) - 10) / 2;

    attron(COLOR_PAIR(CYAN_PAIR));
    mvprintw(y, x, "    dMMMMMP dMMMMMMP dMMMMMP dMMMMb  dMMMMb  .aMMMb  dMP         dMMMMb  dMP dMP dMMMMb");
    mvprintw(y + 1, x, "   dMP        dMP   dMP     dMP.dMP dMP dMP dMP\"dMP dMP         dMP.dMP dMP dMP dMP dMP");
    mvprintw(y + 2, x, "  dMMMP      dMP   dMMMP   dMMMMK\" dMP dMP dMMMMMP dMP         dMMMMK\" dMP dMP dMP dMP");
    mvprintw(y + 3, x, " dMP        dMP   dMP     dMP\"AMF dMP dMP dMP dMP dMP         dMP\"AMF dMP.aMP dMP dMP");
    mvprintw(y + 4, x, "dMMMMMP    dMP   dMMMMMP dMP dMP dMP dMP dMP dMP dMMMMMP     dMP dMP  VMMMP\" dMP dMP");
    /* mvprintw(y, x, "888888 888888 888888 88\"\"Yb 88b 88    db    88         88\"\"Yb 88   88 88b 88");
    mvprintw(y + 1, x, "88__     88   88__   88__dP 88Yb88   dPYb   88         88__dP 88   88 88Yb88");
    mvprintw(y + 2, x, "88\"\"     88   88\"\"   88\"Yb  88 Y88  dP__Yb  88  .o     88\"Yb  Y8   8P 88 Y88");
    mvprintw(y + 3, x, "888888   88   888888 88  Yb 88  Y8 dP\"\"\"\"Yb 88ood8     88  Yb `YbodP' 88  Y8"); */   
    /* mvprintw(y, x, "8888  w                         8    888b.");
    mvprintw(y + 1, x, "8www w8ww .d88b 8d8b 8d8b. .d88 8    8  .8 8   8 8d8b.");
    mvprintw(y + 2, x, "8     8   8.dP' 8P   8P Y8 8  8 8    8wwK' 8b d8 8P Y8");
    mvprintw(y + 3, x, "8888  Y8P `Y88P 8    8   8 `Y88 8    8  Yb `Y8P8 8   8"); */
    attroff(COLOR_PAIR(CYAN_PAIR));
}

void show_splash_screen() {
    clear();
    refresh();

    // print game name
    print_game_name_text();

    // print "Premi un tasto" and wait for an input
    unsigned const int BLINK_PERIOD = 60;
    unsigned int tick = 0;
    bool visible = false;
    bool exit_splash_screen = false;

    int textx = (getmaxx(stdscr) - 14) / 2;
    int texty = (getmaxy(stdscr) - 10) / 2 + 8;
    while (!exit_splash_screen) {
        char c = getch();
        
        // if char entered exit the loop, otherwise blink the text
        if (c != -1) exit_splash_screen = true;
        else if (tick == BLINK_PERIOD) {
            if (visible) {
                mvprintw(texty, textx, "              ");
                visible = false;
            } else {
                mvprintw(texty, textx, "Premi un tasto");
                visible = true;
            }

            refresh();
        }

        // increment tick
        if (tick >= BLINK_PERIOD) tick = 0;
        else tick++;

        napms(10);
    }

    clear();
    refresh();
}

WINDOW *create_game_window() {
    // create game window by aligning it to info window
    int stdscr_maxy, stdscr_maxx;
    getmaxyx(stdscr, stdscr_maxy, stdscr_maxx);

    const int GAME_WIN_BEGY = (stdscr_maxy - GAME_WIN_HEIGHT) / 2;
    const int GAME_WIN_BEGX = (stdscr_maxx - (GAME_WIN_WIDTH + INFO_WIN_WIDTH)) / 2 - 2;

    WINDOW *game_win = newwin(
        GAME_WIN_HEIGHT, GAME_WIN_WIDTH, 
        GAME_WIN_BEGY, GAME_WIN_BEGX
    );

    nodelay(game_win, true); // don't stop the program on getch()
    keypad(game_win, true); // enable keypad inputs

    wrefresh(game_win);

    return game_win;
}

void show_menu(
    WINDOW *game_win, 
    char options[][50], 
    int options_length, 
    int starty, 
    int selected_option
    ) {
    // get max strlen() of options
    int max_option_length = strlen(options[0]);
    for (int i = 1; i < options_length; i++) {
        int current_option_length = strlen(options[i]);
        if (current_option_length > max_option_length)
            max_option_length = current_option_length;
    }

    // get start x for all the options
    int x = (getmaxx(game_win) - max_option_length) / 2 - 1;

    // print options
    for (int i = 0; i < options_length; i++) {
        int y = starty + i * 2;
        
        if (i == selected_option) {
            wattron(game_win, A_REVERSE);
            mvwprintw(game_win, y, x, "- %s", options[i]);
            wattroff(game_win, A_REVERSE);
        } else mvwprintw(game_win, y, x, "- %s", options[i]);
    }

    wrefresh(game_win);
}

void print_game_over_text(WINDOW *game_win, int COLOR_PAIR_NUM) {
    wattron(game_win, COLOR_PAIR(RED_PAIR));
    mvwprintw(game_win, 4, 3, ".d88b                          .d88b.");
    mvwprintw(game_win, 5, 3, "8P www .d88 8d8b.d8b. .d88b    8P  Y8 Yb  dP .d88b 8d8b");
    mvwprintw(game_win, 6, 3, "8b  d8 8  8 8P Y8P Y8 8.dP'    8b  d8  YbdP  8.dP' 8P");
    mvwprintw(game_win, 7, 3, "`Y88P' `Y88 8   8   8 `Y88P    `Y88P'   YP   `Y88P 8");
    wattroff(game_win, COLOR_PAIR(RED_PAIR));
}

int show_game_over_screen(WINDOW *game_win) {
    wclear(game_win);

    print_game_over_text(game_win, WALL_PAIR);

    // create menu options array
    char menu_options[2][50] = {};
    strcpy(menu_options[0], "Nuova partita");
    strcpy(menu_options[1], "Esci dal gioco");

    // show menu and start menu loop
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

int show_esc_screen(WINDOW *game_win) {
    wclear(game_win);

    mvwprintw(game_win, 6, 17, "Sei sicuro di voler uscire?");

    // create menu options array
    char menu_options[2][50] = {};
    strcpy(menu_options[0], "Si");
    strcpy(menu_options[1], "No");

    // show menu and start menu cicle
    int selected_option = 0;
    show_menu(game_win, menu_options, 2, 10, selected_option);

    int exit_esc_screen = 0;
    while (!exit_esc_screen) {
        char c = wgetch(game_win);

        // check if key entered
        if (c != -1) {
            switch (c) {
                case 2:
                    // increase selected option
                    if (selected_option < 1) selected_option++;
                    else selected_option = 0;
                    show_menu(game_win, menu_options, 2, 10, selected_option);
                    break;
                case 3:
                    // decrease selected option
                    if (selected_option > 0) selected_option--;
                    else selected_option = 1;
                    show_menu(game_win, menu_options, 2, 10, selected_option);
                    break;
                case 10:
                    // enter option
                    exit_esc_screen = true;
            }
        }

        napms(10);
    }

    return selected_option;
}

void display_map(WINDOW *game_win, map *map) {
    // diplay map border
    wclear(game_win);
    wattron(game_win, COLOR_PAIR(WALL_PAIR));
    wborder(game_win, '#', '#', '#', '#', '#', '#', '#', '#');
    wattroff(game_win, COLOR_PAIR(WALL_PAIR));

    // display all the map walls and coins at once
    for (int row = 0; row < 20; row++) {
        for (int col = 0; col < 60; col++) {
            wmove(game_win, row, col);
            int current_block = (map->blocks)[row][col];

            if (current_block != EMPTY_BLOCK) {
                switch (current_block) {
                    case WALL_BLOCK:
                        wattron(game_win, COLOR_PAIR(WALL_PAIR));
                        waddch(game_win, '#');
                        wattroff(game_win, COLOR_PAIR(WALL_PAIR));
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
    }

    coin *iterator = map->coin_list;
	while (iterator != NULL) {
		wmove(game_win, iterator->y, iterator->x);
		wattron(game_win, COLOR_PAIR(YELLOW_PAIR));
		waddch(game_win, '*');
		wattroff(game_win, COLOR_PAIR(YELLOW_PAIR));
		iterator = iterator->next;
	}

    wrefresh(game_win);
}

void display_map_with_anim(WINDOW *game_win, map *map) {
    // display map border
    wclear(game_win);
    wattron(game_win, COLOR_PAIR(WALL_PAIR));
    wborder(game_win, '#', '#', '#', '#', '#', '#', '#', '#');
    wattroff(game_win, COLOR_PAIR(WALL_PAIR));

    // display the map with an animation (row after row)
    unsigned int tick = 0;
    const unsigned int ANIM_PERIOD = 10;
    int row = 19;

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

    coin *iterator = map->coin_list;
	while (iterator!=NULL) {
		wmove(game_win, iterator->y, iterator->x);
		wattron(game_win, COLOR_PAIR(YELLOW_PAIR));
		waddch(game_win, '*');
		wattroff(game_win, COLOR_PAIR(YELLOW_PAIR));
		iterator = iterator->next;
	}

    wrefresh(game_win);
}

void destroy_map_with_animation(WINDOW *game_win) {
    // destroy the map with an animation (row after row)
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

void set_blank_char(WINDOW *game_win, int y, int x) {
    wmove(game_win, y, x);
    waddch(game_win, ' ');
}

/* Info window */

WINDOW *create_info_window(WINDOW *game_win) {
    // create info window by aligning it to game window
    int stdscr_maxy, stdscr_maxx;
    getmaxyx(stdscr, stdscr_maxy, stdscr_maxx);
    int game_win_begy = getbegy(game_win);
    int game_win_maxx = getmaxx(game_win);

    const int INFO_WIN_BEGY = game_win_begy;
    const int INFO_WIN_BEGX = game_win_maxx + 
        (stdscr_maxx - (GAME_WIN_WIDTH + INFO_WIN_WIDTH)) / 2 + 2;

    WINDOW *info_win = newwin(
        GAME_WIN_HEIGHT, INFO_WIN_WIDTH,
        INFO_WIN_BEGY, INFO_WIN_BEGX
    );

    box(info_win, 0, 0);

    // print dividers
    mvwprintw(info_win, 2, 1, "----------------");
    mvwprintw(info_win, 6, 1, "----------------");

    wrefresh(info_win);

    return info_win;
}

void refresh_title(WINDOW *info_win, int level, bool is_market_level) {
    if (is_market_level) mvwprintw(info_win, 1, 2, "MARKET LEVEL");
    else mvwprintw(info_win, 1, 2, "LEVEL %d", level);
    wrefresh(info_win);
}

void refresh_stats(WINDOW *info_win, int life, int shield, int coins) {
    // life
    wattron(info_win, COLOR_PAIR(RED_PAIR));
    mvwprintw(info_win, 3, 2, "LIFE: %d", life);
    wattroff(info_win, COLOR_PAIR(RED_PAIR));

    // shield
    wattron(info_win, COLOR_PAIR(CYAN_PAIR));
    mvwprintw(info_win, 4, 2, "SHIELD: %d", shield);
    wattroff(info_win, COLOR_PAIR(CYAN_PAIR));
    
    // coins
    wattron(info_win, COLOR_PAIR(YELLOW_PAIR));
    mvwprintw(info_win, 5, 2, "COINS: %d", coins);
    wattroff(info_win, COLOR_PAIR(YELLOW_PAIR));

    wrefresh(info_win);
}