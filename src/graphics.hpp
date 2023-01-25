#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

/* Includes */

#include <ncursesw/ncurses.h>

#include "map.hpp"

/* Vars */

const int WALL_PAIR = 1;
const int RED_PAIR = 2;
const int YELLOW_PAIR = 3;

/* Game window */

// create and return the window for the game
WINDOW *create_game_window();

// move the game win by centering it in terminal (considering info win)
void move_game_window(WINDOW *game_win);

void show_splash_screen(WINDOW *game_win);

// show the game over screen,
// returns the index of the option selected from the menu
int show_game_over_screen(WINDOW *game_win);

// shwo the exit screen, ask the user if want to exit
int show_esc_screen(WINDOW *game_win);

// destroy current map with animation
void destroy_map(WINDOW *game_win);

// display map with animation
void display_map(WINDOW *game_win, map *map);

/* Info window */

// refresh the text that shows the title of the game
void refresh_title(WINDOW *info_win, char *title);

// refresh the text that shows the stats of the game
void refresh_stats(WINDOW *info_win, int life, int money);

// create and return the window for the info of the game
WINDOW *create_info_window(WINDOW *game_win);

#endif