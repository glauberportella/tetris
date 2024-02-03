/**
 * @file game.c
 * @author Glauber Portella (glauberportella@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-02-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <stdlib.h>
#include <stddef.h>
#include <time.h>

#include "game.h"
#include "../core/piece.h"

TetrisGame* create_game() {
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        SDL_Log("Erro ao inicializar o SDL: %s", SDL_GetError());
        return NULL;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) != 0) {
        SDL_Log("Erro ao abrir audio: %s", Mix_GetError());
        return NULL;
    }

    TetrisGame* game = (TetrisGame*)malloc(sizeof(TetrisGame));

    // game->music = Mix_LoadMUS("music/01-Title.mp3");
    // if (!game->music) {
    //     SDL_Log("Erro ao carregar música: %s", Mix_GetError());
    // }
    // Mix_VolumeMusic(20);

    game->velocity = 60;
    game->level = 1;
    game->points = 0;
    game->paused = 0;
    game->board = board_create(WIDTH, HEIGHT);
    game->window_w = game->board->width * BLOCK_WIDTH * 2;
    game->window_h = game->board->height * BLOCK_HEIGHT * 2;
    game->current_piece = game_create_current_piece(game);
    game->next_piece_type = game_next_piece_type(game);

    game->window = SDL_CreateWindow(
        GAME_TITLE, 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        game->window_w,
        game->window_h,
        SDL_WINDOW_SHOWN
    );

    game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!game->renderer) {
        SDL_Log("Erro ao criar o renderizador: %s", SDL_GetError());
        return NULL;
    }

    return game;
}

void game_play_music(TetrisGame* game) {
    Mix_PlayMusic(game->music, 1);
}

PieceType game_next_piece_type(TetrisGame* game) {
    int random = rand() % 7;
    PieceType pieceType = (PieceType)random;
    return pieceType;
}

Piece* game_create_current_piece(TetrisGame* game) {
    PieceType pieceType = game_next_piece_type(game);
    // color
    Color color = { 255, 255, 0, 255 };
    // position
    int x = 0;
    int y = (int)(game->board->width - 1) / 2; ;
    return piece_create(pieceType, color, x, y);
}

void game_render(TetrisGame* game) {
    int width = game->board->width;
    int height = game->board->height;
    int block_height = (int)(game->window_h / HEIGHT);
    int block_width = (int)(game->window_w / WIDTH);
    for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++) {
            if (game->board->matrix[x][y] == 1) {
                // Peça atual descendo
                SDL_Rect rect = { 
                    y * block_width, 
                    x * block_height, 
                    block_height, 
                    block_width
                };
                SDL_SetRenderDrawColor(
                    game->renderer, 
                    game->current_piece->color.r, 
                    game->current_piece->color.g, 
                    game->current_piece->color.b, 
                    game->current_piece->color.a
                );
                SDL_RenderFillRect(game->renderer, &rect);
            } else if (game->board->matrix[x][y] == 2) {
                // Peça fixada
                SDL_Rect rect = { 
                    y * block_width, 
                    x * block_height, 
                    block_height, 
                    block_width
                };
                SDL_SetRenderDrawColor(
                    game->renderer, 
                    0,
                    255,
                    0, 
                    255
                );
                SDL_RenderFillRect(game->renderer, &rect);
            }
        }
    }
}

void game_update_points(TetrisGame* game, int total_lines_removed) {
    game->points += total_lines_removed * 100;
}

void game_check_level(TetrisGame* game) {
    int next_level = game->level;
    if (game->points == game->level * 1000) {
        next_level++;
    }
    game->level = next_level;
}

void destroy_game(TetrisGame* game) {
    // SDL destroy
    Mix_FreeMusic(game->music);
    Mix_CloseAudio();
    Mix_Quit();
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    SDL_Quit();
    // destroy current piece
    piece_destroy(game->current_piece);
    // destroy board
    board_destroy(game->board);
    // destroy game
    if (game != NULL) {
        free(game);
    }
}
