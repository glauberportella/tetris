/**
 * @file board.h
 * @author Glauber Portella (glauberportella@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-02-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _BOARD_H_
#define _BOARD_H_

#include "types.h"

Board* board_create(int w, int h);
void board_init(Board* board);
void board_add_piece(Board* board, Piece* piece);
void board_place_piece(Board* board, Piece* piece);
void board_clear_lines(Board* board);
Collision collision(Board* board, int x, int y);
void board_destroy(Board* board);

void board_log(Board* board);

#endif