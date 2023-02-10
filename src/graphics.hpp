#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

/* Includes */

#include <ncursesw/ncurses.h>

#include "map.hpp"
#include "entities.hpp"

/* Constants */

// pairs
const int WALL_PAIR = 1;
const int RED_PAIR = 2;
const int CYAN_PAIR = 3;
const int YELLOW_PAIR = 4;

// market
const int INCREMENT_LIFE = 0;
const int INCREMENT_SHIELD = 1;
const int PISTOL = 2;
const int BULLET_SPEED = 3;
const int BULLET_DAMAGE = 4;
const int NEXT_LEVEL = 5;

/* General */

// start colors and create color pairs
void create_colors();

/* Standard screen */

// show splash screen in stardard screen
void show_splash_screen();

/* Game window */

// create and return the window for the game
WINDOW *create_game_window();

// show the market screen
void show_market_screen(
    WINDOW *game_win, 
    WINDOW *info_win, 
    Player *player, 
    int &coins,
    bool is_next_level
);

// show the game over screen,
// returns the index of the selected option from the menu
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

// display a single enemy in game window
void display_enemy(WINDOW *game_win, Enemy enemy);

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