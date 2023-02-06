#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

/* Includes */

#include <ncursesw/ncurses.h>

#include "map.hpp"
#include "entities.hpp"

/* Vars */

const int WALL_PAIR = 1;
const int RED_PAIR = 2;
const int CYAN_PAIR = 3;
const int YELLOW_PAIR = 4;

/* Standard screen */

void show_splash_screen();

/* Game window */

// create and return the window for the game
WINDOW *create_game_window();

// show the game over screen,
// returns the index of the option selected from the menu
int show_game_over_screen(WINDOW *game_win);

// ask the user if want to exit
int show_esc_screen(WINDOW *game_win);

// display coins in map
void display_coins(WINDOW *game_win, coin_node *coin_list);

// display map without animation
void display_map(WINDOW *game_win, map *map, coin_node *coin_list);

// display map with animation (row after row)
void display_map_with_anim(WINDOW *game_win, map *map, coin_node *coin_list);

// destroy current map with animation (row after row)
void destroy_map_with_animation(WINDOW *game_win);

// set a blank char to a certain position of the map
void set_blank_char(WINDOW *game_win, int y, int x);

// display player in game window
void display_player(WINDOW *game_win, Player player);

// display enemies in game window
void display_enemies(WINDOW *game_win, enemy_node *current_enemy_list);

/* Info window */

// create and return the window for the info of the game
WINDOW *create_info_window(WINDOW *game_win);

// refresh the text that shows the title of the game
void refresh_title(WINDOW *info_win, int level, bool is_market_level);

// refresh the text that shows the stats of the game
void refresh_stats(WINDOW *info_win, Player player, int coins);

#endif