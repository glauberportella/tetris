/**
 * @file piece.c
 * @author Glauber Portella (glauberportella@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-02-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "board.h"
#include "piece.h"

Block* create_block(int x, int y, int pivot) {
    Block* block = (Block*)malloc(sizeof(Block));
    block->x = x;
    block->y = y;
    block->width = BLOCK_WIDTH;
    block->height = BLOCK_HEIGHT;
    block->pivot = pivot;
    block->next = NULL;
    return block;
}

void piece_add_block(Piece* piece, int x, int y, int pivot) {
    Block* block = create_block(x, y, pivot);
    if (piece->blocks == NULL) {
        piece->blocks = block;
    } else {
        Block* current = piece->blocks;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = block;
    }
}

Piece* piece_create(PieceType type, Color color, int initial_x, int initial_y) {
    Piece* p = (Piece*)malloc(sizeof(Piece));
    p->color = color;
    p->type = type;
    p->blocks = NULL;

    switch (type) {
        case PIECE_1: 
            //
            // [1][2]
            // [3][4]
            //
            piece_add_block(p, initial_x, initial_y, NOT_PIVOT);
            piece_add_block(p, initial_x + 1, initial_y, NOT_PIVOT);
            piece_add_block(p, initial_x, initial_y + 1, NOT_PIVOT);
            piece_add_block(p, initial_x + 1, initial_y + 1, NOT_PIVOT);
            break;
        case PIECE_2:
            // [1]
            // [2]
            // [3]
            // [4]
            piece_add_block(p, initial_x, initial_y, NOT_PIVOT);
            piece_add_block(p, initial_x, initial_y + 1, IS_PIVOT);
            piece_add_block(p, initial_x, initial_y + 2, NOT_PIVOT);
            piece_add_block(p, initial_x, initial_y + 3, NOT_PIVOT);
            break;
        case PIECE_3:
            // 
            // [1][2]
            //    [3]
            //    [4]
            piece_add_block(p, initial_x, initial_y, NOT_PIVOT);
            piece_add_block(p, initial_x + 1, initial_y, IS_PIVOT);
            piece_add_block(p, initial_x + 1, initial_y + 1, NOT_PIVOT);
            piece_add_block(p, initial_x + 1, initial_y + 2, NOT_PIVOT);
            break;
        case PIECE_4:
            // 
            // [1][2]
            // [3]
            // [4]
            piece_add_block(p, initial_x, initial_y, IS_PIVOT);
            piece_add_block(p, initial_x + 1, initial_y, NOT_PIVOT);
            piece_add_block(p, initial_x, initial_y + 1, NOT_PIVOT);
            piece_add_block(p, initial_x, initial_y + 2, NOT_PIVOT);
            break;
        case PIECE_5:
            // 
            // [1][2][3]
            //    [4]
            // 
            piece_add_block(p, initial_x, initial_y, NOT_PIVOT);
            piece_add_block(p, initial_x + 1, initial_y, IS_PIVOT);
            piece_add_block(p, initial_x + 2, initial_y, NOT_PIVOT);
            piece_add_block(p, initial_x + 1, initial_y + 1, NOT_PIVOT);
            break;
        case PIECE_6:
            // 
            //    [1][2]
            // [3][4]
            // 
            piece_add_block(p, initial_x + 1, initial_y, IS_PIVOT);
            piece_add_block(p, initial_x + 2, initial_y, NOT_PIVOT);
            piece_add_block(p, initial_x, initial_y + 1, NOT_PIVOT);
            piece_add_block(p, initial_x + 1, initial_y + 1, NOT_PIVOT);
            break;
        case PIECE_7:
            // 
            // [1][2]
            //    [3][4]
            // 
            piece_add_block(p, initial_x, initial_y, NOT_PIVOT);
            piece_add_block(p, initial_x + 1, initial_y, IS_PIVOT);
            piece_add_block(p, initial_x + 1, initial_y + 1, NOT_PIVOT);
            piece_add_block(p, initial_x + 2, initial_y + 1, NOT_PIVOT);
            break;
        default:
            printf("Tipo de peça informada não reconhecida: %d", type);
            exit(1);
    }

    return p;
}

Block* piece_find_pivot(Piece* piece) {
    Block* current = piece->blocks;
    while (current != NULL) {
        if (current->pivot) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

int piece_can_rotate(Piece* piece, Block* pivot) {
    if (pivot == NULL) {
        return 0;
    }

    Block* current = piece->blocks;
    while (current != NULL) {
        int dx = current->x - pivot->x;
        int dy = current->y - pivot->y;
        int newX = pivot->x - dy;
        int newY = pivot->y + dx;
        if (newX < 0 || newY < 0) {
            return 0;
        }
        current = current->next;
    }

    return 1;
}

void piece_rotate(Piece* piece) {
    Block* pivot = piece_find_pivot(piece);
    if (pivot == NULL) {
        return;
    }

    if (piece_can_rotate(piece, pivot)) {    
        Block* current = piece->blocks;
        while (current != NULL) {
            // Calcula as diferenças em relação ao ponto de rotação
            int dx = current->x - pivot->x;
            int dy = current->y - pivot->y;

            // Realiza a rotação em torno do ponto de rotação
            current->x = pivot->x - dy;
            current->y = pivot->y + dx;

            current = current->next;
        }
    }
}

Collision piece_move(MoveDirection direction, Board* board, Piece* piece) {
    Block* current = piece->blocks;
    Collision collision_detected = NO_COLLISION;

    switch (direction) {
        case UP:
            // while (current != NULL) {
            //     if (collision(board, current->x - 1, current->y) == TOP_WALL) {
            //         collision_detected = TOP_WALL;
            //         break;
            //     }
            //     current = current->next;
            // }
            // if (collision_detected == NO_COLLISION) {
            //     current = piece->blocks;
            //     while (current != NULL) {
            //         current->x -= 1;
            //         current = current->next;
            //     }
            // }
            break;
        case DOWN:
            while (current != NULL) {
                // Primeiro verifica colisao com a parede do fundo
                if (collision(board, current->x + 1, current->y) == BOTTOM_WALL) {
                    collision_detected = BOTTOM_WALL;
                    break;
                }
                // Verifica colisao com peças no fundo
                if (collision(board, current->x + 1, current->y) == PIECE) {
                    collision_detected = PIECE;
                    break;
                }
                current = current->next;
            }
            if (collision_detected == NO_COLLISION) {
                current = piece->blocks;
                while (current != NULL) {
                    current->x += 1;
                    current = current->next;
                }
            }
            break;
        case LEFT:
            while (current != NULL) {
                if (collision(board, current->x, current->y - 1) == LEFT_WALL) {
                    collision_detected = LEFT_WALL;
                    break;
                }
                // Verifica colisao com peças na esquerda
                if (collision(board, current->x, current->y - 1) == PIECE) {
                    collision_detected = PIECE;
                    break;
                }
                current = current->next;
            }
            if (collision_detected == NO_COLLISION) {
                current = piece->blocks;
                while (current != NULL) {
                    current->y -= 1;
                    current = current->next;
                }
            }
            break;
        case RIGHT:
            while (current != NULL) {
                if (collision(board, current->x, current->y + 1) == RIGHT_WALL) {
                    collision_detected = RIGHT_WALL;
                    break;
                }
                // Verifica colisao com peças no fundo
                if (collision(board, current->x, current->y + 1) == PIECE) {
                    collision_detected = PIECE;
                    break;
                }
                current = current->next;
            }
            if (collision_detected == NO_COLLISION) {
                current = piece->blocks;
                while (current != NULL) {
                    current->y += 1;
                    current = current->next;
                }
            }
            break;
    }

    return collision_detected;
}

void block_destroy(Block* block) {
    while (block != NULL) {
        Block* temp = block;
        block = block->next;
        free(temp);
    }
}

void piece_destroy(Piece* piece) {
    block_destroy(piece->blocks);
    if (piece != NULL) {
        free(piece);
    }
}