/**
 * @file game.h
 * @author Glauber Portella (glauberportella@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-02-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _GAME_H_
#define _GAME_H_

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "../core/board.h"
#include "../core/piece.h"

#define GAME_TITLE "Tetris 2048"

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    Mix_Music* music;

    Board* board;
    Piece* current_piece;
    PieceType next_piece_type;

    int window_w;
    int window_h;

    int velocity;
    int level;
    int points;
    int paused;
} TetrisGame;

TetrisGame* create_game();
void game_play_music(TetrisGame* game);
void game_render(TetrisGame* game);
Piece* game_create_current_piece(TetrisGame* game);
PieceType game_next_piece_type(TetrisGame* game);
void game_update_points(TetrisGame* game, int total_lines_removed);
void game_check_level(TetrisGame* game);
void game_fix_piece(TetrisGame* game);
int game_is_over(TetrisGame* game);
void game_current_piece_render(TetrisGame* game, int x, int y);
void game_fix_piece_render(TetrisGame* game, int x, int y);
void destroy_game(TetrisGame* game);

#endif