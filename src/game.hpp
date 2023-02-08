#ifndef GAME_HPP
#define GAME_HPP

// create the array of the game's maps
void create_maps();

// start the new game
void new_game(WINDOW *game_win, WINDOW *info_win);

// start the game's main loop
void start_game_loop(WINDOW *game_win, WINDOW *info_win);

#endif