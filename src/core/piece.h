/**
 * @file piece.h
 * @author Glauber Portella (glauberportella@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-02-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _PIECE_H_
#define _PIECE_H_

#include "types.h"

#define BLOCK_WIDTH  16
#define BLOCK_HEIGHT 16
#define IS_PIVOT     1
#define NOT_PIVOT    0


/**
 * @brief Cria um bloco
 * 
 * @return Block* 
 */
Block* create_block(int x, int y, int pivot);

/**
 * @brief Adicona bloco a uma Piece
 * 
 */
void piece_add_block(Piece* piece, int x, int y, int pivot);

Color piece_color(PieceType type);

/**
 * @brief Cria uma Piece do tipo informado
 * 
 * @return Piece* 
 */
Piece* piece_create(PieceType type, Color color, int initial_x, int initial_y);

/**
 * @brief Encontra o bloco pivot de uma Piece
 * 
 * @return Block* 
 */
Block* piece_find_pivot(Piece* piece);

/**
 * @brief Verifica se uma Piece pode rotacionar
 * 
 * @return int 
 */
int piece_can_rotate(Piece* piece, Block* pivot);

/**
 * @brief Rotaciona uma Piece
 * 
 */
void piece_rotate(Piece* piece);

/**
 * @brief Move uma Piece
 * 
 */
Collision piece_move(MoveDirection direction, Board* board, Piece* piece);

/**
 * @brief Destroi blocos da memória
 * 
 */
void block_destroy(Block* block);

/**
 * @brief Destroi Piece da memória
 * 
 */
void piece_destroy(Piece* piece);

#endif