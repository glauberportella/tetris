/**
 * @file board.c
 * @author Glauber Portella (glauberportella@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-02-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#include "board.h"
#include "piece.h"

Board* board_create(int w, int h) {
    Board* board = (Board*)malloc(sizeof(Board));
    board->width = w;
    board->height = h;
    return board;
}

void board_init(Board* board) {
    for (int x = 0; x < board->height; ++x) {
        for (int y = 0; y < board->width; ++y) {
            if (board->matrix[x][y] < 2) {
                board->matrix[x][y] = 0; // 0 representa célula vazia
            }
        }
    }
}

void board_add_piece(Board* board, Piece* piece) {
    Block* current = piece->blocks;
    while (current != NULL) {
        board->matrix[current->x][current->y] = 1; // 1 representa célula ocupada por um bloco
        current = current->next;
    }
}

void board_place_piece(Board* board, Piece* piece) {
    Block* current = piece->blocks;
    while (current != NULL) {
        board->matrix[current->x][current->y] = piece->type + 2;
        current = current->next;
    }
    piece_destroy(piece);
}

/**
 * @brief Limpa as linhas completas e retorna o total de linhas removidas
 * 
 * @param board 
 * @return int 
 */
int board_clear_lines(Board* board) {
    int total = 0;
    for (int i = board->height - 1; i >= 0; --i) {
        int count = 0;
        for (int j = 0; j < board->width; ++j) {
            if (board->matrix[i][j] >= 2) {
                count++;
            }
        }

        if (count == board->width) {
            total++;
            // Linha completa, mova todas as linhas acima para baixo
            for (int k = i; k > 0; --k) {
                for (int j = 0; j < board->width; ++j) {
                    board->matrix[k][j] = board->matrix[k - 1][j];
                }
            }

            // Preencha a linha superior com células vazias
            for (int j = 0; j < WIDTH; ++j) {
                board->matrix[0][j] = 0;
            }

            // Continue verificando a mesma linha, pois ela foi movida para baixo
            i++;
        }
    }
    return total;
}

/**
 * @brief Verifica colisão
 * 
 * @param board 
 * @param piece 
 * @return Collision 
 */
Collision collision(Board* board, int x, int y) {
    // colisão com as paredes (topo, esquerda, direita, fundo)
    if (y < 0) {
        return LEFT_WALL;
    }
    if (y > WIDTH - 1) {
        return RIGHT_WALL;
    }
    if (x < 0) {
        return TOP_WALL;
    }
    if (x > HEIGHT - 1) {
        return BOTTOM_WALL;
    }

    // colisão com blocos fixados no tabuleiro
    if (board->matrix[x][y] >= 2) {
        return PIECE;
    }

    return NO_COLLISION;
}

void board_destroy(Board* board) {
    if (board != NULL) {
        free(board);
    }
}

void board_log(Board* board) {
    printf("\n===========BOARD===============\n");
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            printf("%d ", board->matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n===========END BOARD===========\n");
}
