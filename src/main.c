/**
 * @file main.c
 * @author Glauber Portella (glauberportella@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-02-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <stddef.h>
#include "game/game.h"

#define FPS 60
#define DELAY_TIME 1000.0f/FPS

int main() {
    // semente aleatoria
    srand((unsigned int)time(NULL));
    
    TetrisGame* game = create_game();
    Uint32 frameStart, frameTime;

    if (game != NULL) {
        game_play_music(game);

        Collision collision_with;
        SDL_Event event;
        int gameover = 0;
        int quit = 0;
        int loopCount = 0;
        int acceleration = 1;

        while (!quit) {
            frameStart = SDL_GetTicks();

            if (gameover) {
                // mostrar tela de game over
                // mostrar menu com opção
                // continuar no mesmo nível, reiniciar, sair do jogo
                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        quit = 1;
                    } else {
                        if (event.type == SDL_KEYDOWN) {
                            if (event.type == SDL_KEYDOWN) {
                                if (event.key.keysym.sym == SDLK_UP) {
                                    // seleciona opção do menu para cima
                                } else if (event.key.keysym.sym == SDLK_DOWN) {
                                    // seleciona opção do menu para baixo
                                }
                            }
                        }
                    }
                }
            } else {
                // jogo rolando
                board_init(game->board);
                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        quit = 1;
                    } else {
                        // teclado
                        if (event.type == SDL_KEYDOWN) {
                            if (event.key.keysym.sym == SDLK_UP) {
                                // Seta para cima
                                piece_rotate(game->current_piece);
                            } else if (event.key.keysym.sym == SDLK_DOWN) {
                                // Seta para baixo
                                // acelerar peça
                                acceleration = FPS;
                            } else if (event.key.keysym.sym == SDLK_LEFT) {
                                // Seta esquerda
                                collision_with = piece_move(LEFT, game->board, game->current_piece);
                            } else if (event.key.keysym.sym == SDLK_RIGHT) {
                                // Seta direita
                                collision_with = piece_move(RIGHT, game->board, game->current_piece);
                            }
                        } else if (event.type == SDL_KEYUP) {
                            if (event.key.keysym.sym == SDLK_DOWN) {
                                // restaurar aceleração
                                acceleration = 1;
                            }
                        }
                    }
                }
                
                SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
                SDL_RenderClear(game->renderer);

                loopCount++;
                if (loopCount % (int)(game->velocity / game->level / acceleration) == 0) {
                    collision_with = piece_move(DOWN, game->board, game->current_piece);
                    // SDL_Log("Collision with: %d", collision_with);
                    if (collision_with == PIECE && game_is_over(game)) {
                        SDL_Log("GAME OVER");
                        gameover = 1;
                    } else if (collision_with == BOTTOM_WALL) {
                        // fixa a peça encaixando no fundo
                        game_fix_piece(game);
                        SDL_Log("Pontos: %d", game->points);
                        SDL_Log("Level: %d", game->level);
                        SDL_Log("Aceleracao: %d", acceleration);
                        SDL_Log("Loop count control: %d", (int)(game->velocity / game->level / acceleration));
                    } else if (collision_with == PIECE) {
                        // fixa a peça
                        game_fix_piece(game);
                        SDL_Log("Pontos: %d", game->points);
                        SDL_Log("Level: %d", game->level);
                        SDL_Log("Aceleracao: %d", acceleration);
                        SDL_Log("Loop count control: %d", (int)(game->velocity / game->level / acceleration));
                    }
                    loopCount = 0;
                }

                board_add_piece(game->board, game->current_piece);
                game_render(game);

                SDL_RenderPresent(game->renderer);
            }

            frameTime = SDL_GetTicks() - frameStart;
            if (frameTime < DELAY_TIME) {
                SDL_Delay((int)(DELAY_TIME - frameTime));
            }
        }

        destroy_game(game);
    }

    return 0;
}