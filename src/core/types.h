/**
 * @file types.h
 * @author Glauber Portella (glauberportella@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-02-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _TYPES_H_
#define _TYPES_H_

#define WIDTH  10
#define HEIGHT 20

typedef struct {
    int matrix[HEIGHT][WIDTH];
    int width;
    int height;
} Board;

typedef enum {
    NO_COLLISION,
    PIECE,
    TOP_WALL,
    LEFT_WALL,
    RIGHT_WALL,
    BOTTOM_WALL
} Collision;

// Tipos de peças
typedef enum {
    PIECE_1, // Quadrado
    PIECE_2, // Coluna
    PIECE_3, // r invertido
    PIECE_4, // r
    PIECE_5, // T
    PIECE_6, // s
    PIECE_7  // z
} PieceType;

typedef struct {
    int r;
    int g;
    int b;
    int a;
} Color;

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT
} MoveDirection;

// Estrutura para representar um bloco
typedef struct Block {
    int x, y;  // Posição do bloco na grade
    int pivot; // indicar bloco pivo
    int width;
    int height;
    struct Block* next;  // Ponteiro para o próximo bloco na lista
} Block;

// Estrutura para representar uma peça
typedef struct {
    Color color;        // Cor da peça
    PieceType type;     // piecetype
    Block* blocks;      // Lista encadeada de blocos
} Piece;

#endif