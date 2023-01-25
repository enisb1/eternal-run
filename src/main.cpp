/* Includes */

#include <ncursesw/ncurses.h>
#include <stdlib.h>
#include <cstring>

#include "graphics.hpp"
#include "map.hpp"

/* Vars */
WINDOW *game_win;
WINDOW *info_win;

map *maps[6];
char title[25];
int life;
int shield;
int money;

/* Main method */

void create_colors() {
    if (has_colors()) start_color();

    init_pair(WALL_PAIR, COLOR_WHITE, COLOR_BLUE);
    init_pair(RED_PAIR, COLOR_RED, 0);
    init_pair(CYAN_PAIR, COLOR_CYAN, 0);
    init_pair(YELLOW_PAIR, COLOR_YELLOW, 0);
}

void new_game() {
    // initialize vars
    strcpy(title, "LEVEL 1");
    life = 3;
    shield = 0;
    money = 0;

    // refresh
    refresh_title(info_win, title);
    refresh_stats(info_win, life, shield, money);

    // TODO: new level (replace with random level)
    display_map_with_anim(game_win, maps[0]);
}

void death() {
    life--;
    refresh_stats(info_win, life, shield, money);

    destroy_map_with_animation(game_win);
    if (life > 0) {
        // TODO: replace with random level
        display_map_with_anim(game_win, maps[1]);
    } else {
        // game over
        switch (show_game_over_screen(game_win)) {
            case 0:
                new_game();
                break;
            case 1:
                endwin();
                exit(0);
                break;
        }
    }
}

int main() {
    // start ncurses
    initscr();
    curs_set(0); // cursor invisible
    noecho(); // don't print input
    nodelay(stdscr, true); // don't stop the program on getch()
    create_colors(); // create color pairs

    // create the 6 maps and show splash screen
    create_maps(maps);

    show_splash_screen();

    // start game
    game_win = create_game_window();
    info_win = create_info_window(game_win);

    new_game();

    // game loop
    while (1) {
        char c = wgetch(game_win);
        
        if (c != -1) {
            switch (c) {
                case 27:
                    // esc
                    switch (show_esc_screen(game_win)) {
                        case 0:
                            endwin();
                            exit(0);
                            break;
                        case 1:
                            // resume_game();
                            break;
                    }
                    break;
            }
        }
    };

    return 0;
}