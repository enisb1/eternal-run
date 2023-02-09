/* Includes */

#include <ncursesw/ncurses.h>
#include <cstring>

#include "graphics.hpp"
#include "entities.hpp"
#include "map.hpp"

/* Vars */

const int GAME_WIN_HEIGHT = 20;
const int GAME_WIN_WIDTH = 60;
const int INFO_WIN_WIDTH = 18;

/* Structs */

struct menu_option {
    char name[50];
    bool valid;
};

/* Standard screen */

void print_game_name_text() {
    int x = (getmaxx(stdscr) - 87) / 2;
    int y = (getmaxy(stdscr) - 10) / 2;

    attron(COLOR_PAIR(CYAN_PAIR));
    mvprintw(y, x, "    dMMMMMP dMMMMMMP dMMMMMP dMMMMb  dMMMMb  .aMMMb  dMP         dMMMMb  dMP dMP dMMMMb");
    mvprintw(y + 1, x, "   dMP        dMP   dMP     dMP.dMP dMP dMP dMP\"dMP dMP         dMP.dMP dMP dMP dMP dMP");
    mvprintw(y + 2, x, "  dMMMP      dMP   dMMMP   dMMMMK\" dMP dMP dMMMMMP dMP         dMMMMK\" dMP dMP dMP dMP");
    mvprintw(y + 3, x, " dMP        dMP   dMP     dMP\"AMF dMP dMP dMP dMP dMP         dMP\"AMF dMP.aMP dMP dMP");
    mvprintw(y + 4, x, "dMMMMMP    dMP   dMMMMMP dMP dMP dMP dMP dMP dMP dMMMMMP     dMP dMP  VMMMP\" dMP dMP");
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
        char input_char = getch();
        
        // if char entered exit the loop, otherwise blink the text
        if (input_char != -1) exit_splash_screen = true;
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
    menu_option options[], 
    int options_length, 
    int start_y, 
    int selected_option,
    bool separate_last_option
) {
    // get max strlen() of options
    int max_option_length = strlen(options[0].name);
    for (int i = 1; i < options_length; i++) {
        int current_option_length = strlen(options[i].name);
        if (current_option_length > max_option_length)
            max_option_length = current_option_length;
    }

    // get start x for all the options
    int x = (getmaxx(game_win) - max_option_length) / 2 - 1;

    // print options
    int y = start_y;
    for (int i = 0; i < options_length; i++) {
        if (i == options_length - 1 && separate_last_option) {
            y += 3;
            x = (getmaxx(game_win) - strlen(options[i].name)) / 2;
        }
        else y += 2;
        
        if (i == selected_option) {
            wattron(game_win, A_REVERSE);
            mvwprintw(game_win, y, x, "%s", options[i].name);
            wattroff(game_win, A_REVERSE);
        } else if (!options[i].valid) {
            wattron(game_win, A_DIM);
            mvwprintw(game_win, y, x, "%s", options[i].name);
            wattroff(game_win, A_DIM);
        } else mvwprintw(game_win, y, x, "%s", options[i].name);
    }

    wrefresh(game_win);
}

int get_next_valid_option(
    menu_option menu_options[], 
    int options_num, 
    int selected_option
) {
    int next_valid_option = selected_option;

    while (!menu_options[next_valid_option].valid) {
        if (next_valid_option < options_num - 1) next_valid_option++;
        else next_valid_option = 0;
    }

    return next_valid_option;
}

int get_previous_valid_option(
    menu_option menu_options[], 
    int options_num, 
    int selected_option
) {
    int previous_valid_option = selected_option;

    while (!menu_options[previous_valid_option].valid) {
        if (previous_valid_option > 0) previous_valid_option--;
        else previous_valid_option = options_num - 1;
    }

    return previous_valid_option;
}

void refresh_market_options(menu_option market_options[], Player player, int coins) {
    // life option
    if (coins >= 30 && player.get_life() < 3)
        market_options[0].valid = true;
    else market_options[0].valid = false;

    // shield option
    if (coins >= 40) market_options[1].valid = true;
    else  market_options[1].valid = false;

    // pistol option
    if (coins >= 50 && !player.get_has_pistol())
        market_options[2].valid = true;
    else  market_options[2].valid = false;

    // faster bullet speed option
    if (coins >= 100 && player.get_has_pistol()
        && !player.get_faster_bullet_speed())
        market_options[3].valid = true;
    else  market_options[3].valid = false;

    // bullet damage option
    if (coins >= 120 && player.get_has_pistol())
        market_options[4].valid = true;
    else  market_options[4].valid = false;
}

void show_market_screen(
    WINDOW *game_win, 
    WINDOW *info_win, 
    Player *player, 
    int &coins, 
    bool is_next_level
) {
    wclear(game_win);
    box(game_win, 0, 0);

    // create menu options array
    menu_option option_1;
    strcpy(option_1.name, "- Pozione vita (+1)       30M");

    menu_option option_2;
    strcpy(option_2.name, "- Pozione scudo (+1)      40M");

    menu_option option_3;
    strcpy(option_3.name, "- Pistola                 50M");

    menu_option option_4;
    strcpy(option_4.name, "- Velocita' proiettili    100M");

    menu_option option_5;
    strcpy(option_5.name, "- Danno proiettili    120M");

    menu_option option_6;
    option_6.valid = true;
    if (is_next_level) strcpy(option_6.name, "Prossimo livello ->");
    else strcpy(option_6.name, "Livello precedente ->");


    menu_option market_options[6] = {
        option_1, option_2, option_3,
        option_4,option_5, option_6
    };

    refresh_market_options(market_options, *player, coins);
    
    // show menu and start menu loop
    int selected_option = get_next_valid_option(market_options, 6, 0);
    show_menu(game_win, market_options, 
        6, 2, selected_option, true);

    bool exit_market_screen = false;
    while (!exit_market_screen) {
        char input_char = wgetch(game_win);

        // check if key entered
        if (input_char != -1) {
            switch (input_char) {
                case 2:
                    // increment selected option
                    // only valid options are selectable
                    int next_option;
                    if (selected_option < 5)
                        next_option = selected_option + 1;
                    else next_option = 0;

                    selected_option = get_next_valid_option(
                        market_options, 6, next_option
                    );
                    
                    show_menu(game_win, market_options, 
                        6, 2, selected_option, true);
                    break;
                case 3:
                    // decrease selected option
                    // only valid options are selectable
                    int previous_option;
                    if (selected_option > 0)
                        previous_option = selected_option - 1;
                    else previous_option = 5;

                    selected_option = get_previous_valid_option(
                        market_options, 6, previous_option
                    );

                    show_menu(game_win, market_options, 
                        6, 2, selected_option, true);
                    break;
                case 10:
                    // enter option
                    switch (selected_option) {
                        case INCREMENT_LIFE:
                            coins -= 30;
                            player->increment_life();
                            break;
                        case INCREMENT_SHIELD:
                            coins -= 40;
                            player->increment_shield();
                            break;
                        case PISTOL:
                            coins -= 50;
                            player->set_has_pistol();
                            break;
                        case BULLET_SPEED:
                            coins -= 100;
                            player->set_faster_bullet_speed();
                            break;
                        case BULLET_DAMAGE:
                            coins -= 120;
                            player->increment_bullet_damage();
                            break;
                        case NEXT_LEVEL:
                            exit_market_screen = true;
                            break;
                    }

                    // refresh info win
                    wclear(info_win);
                    refresh_stats(info_win, *player, coins);
                    refresh_title(info_win, -1, true);
                    mvwprintw(info_win, 2, 1, "----------------");
                    mvwprintw(info_win, 6, 1, "----------------");

                    // refresh market
                    refresh_market_options(market_options, *player, coins);
                    selected_option = get_next_valid_option(
                        market_options, 6, selected_option
                    );

                    show_menu(game_win, market_options, 
                        6, 2, selected_option, true);
            }
        }

        napms(10);
    }
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
    menu_option menu_options[2] = {
        {"- Nuova partita", true}, 
        {"- Esci dal gioco", true}
    };

    // show menu and start menu loop
    int selected_option = 0;
    show_menu(game_win, menu_options, 
        2, 10, selected_option, false);

    bool exit_game_over_screen = false;
    while (!exit_game_over_screen) {
        char input_char = wgetch(game_win);

        // check if key entered
        if (input_char != -1) {
            switch (input_char) {
                case 2:
                    // increase selected option
                    if (selected_option < 1) selected_option++;
                    else selected_option = 0;
                    show_menu(game_win, menu_options, 
                        2, 10, selected_option, false);
                    break;
                case 3:
                    // decrease selected option
                    if (selected_option > 0) selected_option--;
                    else selected_option = 1;
                    show_menu(game_win, menu_options, 
                        2, 10, selected_option, false);
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
    menu_option menu_options[2] = {
        {"- Si", true}, 
        {"- No", true}
    };

    // show menu and start menu cicle
    int selected_option = 0;
    show_menu(game_win, menu_options, 
        2, 10, selected_option, false);

    int exit_esc_screen = 0;
    while (!exit_esc_screen) {
        char input_char = wgetch(game_win);

        // check if key entered
        if (input_char != -1) {
            switch (input_char) {
                case 2:
                    // increase selected option
                    if (selected_option < 1) selected_option++;
                    else selected_option = 0;
                    show_menu(game_win, menu_options, 
                        2, 10, selected_option, false);
                    break;
                case 3:
                    // decrease selected option
                    if (selected_option > 0) selected_option--;
                    else selected_option = 1;
                    show_menu(game_win, menu_options, 
                        2, 10, selected_option, false);
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

void display_coins(WINDOW *game_win, coin_node *coin_list) {
    while (coin_list!=NULL) {
		wmove(game_win, coin_list->y, coin_list->x);
		wattron(game_win, COLOR_PAIR(YELLOW_PAIR));
		waddch(game_win, '*');
		wattroff(game_win, COLOR_PAIR(YELLOW_PAIR));
		
        coin_list = coin_list->next;
	}
}

void display_map(WINDOW *game_win, map *map, coin_node *coin_list) {
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

    display_coins(game_win, coin_list);
}

void display_map_with_anim(WINDOW *game_win, map *map, coin_node *coin_list) {
    // display map border
    wclear(game_win);
    wattron(game_win, COLOR_PAIR(WALL_PAIR));
    wborder(game_win, '#', '#', '#', '#', '#', '#', '#', '#');
    wattroff(game_win, COLOR_PAIR(WALL_PAIR));

    // display the map with an animation (row after row)
    int row = 19;

    while (row >= 0) {
        // display current row
        for (int col = 0; col < 60; col++) {
            int current_block = (map -> blocks)[row][col];

            if (current_block != EMPTY_BLOCK) {
                switch (current_block) {
                    case WALL_BLOCK:
                        wattron(game_win, COLOR_PAIR(WALL_PAIR));
                        mvwaddch(game_win, row, col, '#');
                        wattroff(game_win, COLOR_PAIR(WALL_PAIR));
                        break;
                    case ENTRANCE_BLOCK:
                        set_blank_char(game_win, row, col);
                        break;
                    case EXIT_BLOCK:
                        set_blank_char(game_win, row, col);
                        break;
                }
            }
        }

        wrefresh(game_win);

        row--;

        napms(150);
    }
    
    display_coins(game_win, coin_list);
}

void destroy_map_with_animation(WINDOW *game_win) {
    // destroy the map with an animation (row after row)
    int row = 1;

    while (row < 19) {
        // destroy current line
        mvwprintw(game_win, row, 1, "                                                          ");
        wrefresh(game_win);

        row++;

        napms(150);
    }
}

void set_blank_char(WINDOW *game_win, int y, int x) {
    mvwaddch(game_win, y, x, ' ');
}

void display_player(WINDOW *game_win, Player player) {
    char player_char;

    switch (player.get_direction()) {
        case LEFT:
            player_char = '<';
            break;
        case RIGHT:
            player_char = '>';
            break;
        case UP:
            player_char = '^';
            break;
        case DOWN:
            player_char = 'v';
            break;
    }

    mvwaddch(game_win, player.get_y(), player.get_x(), player_char);
}

void display_enemy(WINDOW *game_win, Enemy enemy) {
    wattron(game_win, COLOR_PAIR(RED_PAIR));
    mvwaddch(
        game_win, 
        enemy.get_y(), 
        enemy.get_x(), 
        enemy.get_level() + '0'
    );
    wattroff(game_win, COLOR_PAIR(RED_PAIR));
}

void display_enemies(WINDOW *game_win, enemy_node *current_enemy_list) {
    enemy_node *iterator = current_enemy_list;
    
    while (iterator!=NULL) {
        wattron(game_win, COLOR_PAIR(RED_PAIR));
        mvwaddch(
            game_win, 
            iterator->current_enemy.get_y(), 
            iterator->current_enemy.get_x(), 
            iterator->current_enemy.get_level() + '0'
        );
        wattroff(game_win, COLOR_PAIR(RED_PAIR));
        iterator = iterator->next;
    }
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
    if (is_market_level) mvwprintw(info_win, 1, 2, "MERCATO  ");
    else mvwprintw(info_win, 1, 2, "LIVELLO %d", level);
    wrefresh(info_win);
}

void refresh_stats(WINDOW *info_win, Player player, int coins) {
    // life
    wattron(info_win, COLOR_PAIR(RED_PAIR));
    mvwprintw(info_win, 3, 2, "VITA: %d", player.get_life());
    wattroff(info_win, COLOR_PAIR(RED_PAIR));

    // shield
    wattron(info_win, COLOR_PAIR(CYAN_PAIR));
    mvwprintw(info_win, 4, 2, "SCUDO: %d", player.get_shield());
    wattroff(info_win, COLOR_PAIR(CYAN_PAIR));
    
    // coins
    wattron(info_win, COLOR_PAIR(YELLOW_PAIR));
    mvwprintw(info_win, 5, 2, "MONETE: %d", coins);
    wattroff(info_win, COLOR_PAIR(YELLOW_PAIR));

    // market upgrades
    wmove(info_win, 7, 0);

    if (player.get_has_pistol()) {
        wprintw(info_win, "  - Pistola\n  equipaggiata\n\n");
        wprintw(
            info_win, 
            "  - Danno\n  proiettili: %d\n\n", 
            player.get_bullet_damage()
        );
    }
    if (player.get_faster_bullet_speed())
        wprintw(info_win, "  - Velocita'\n  proiettili\n  aumentata\n\n");
    
    box(info_win, 0, 0);

    wrefresh(info_win);
}