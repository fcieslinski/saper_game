#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Board* createBoard(int rows, int cols, int mines) {
    Board* board = malloc(sizeof(Board));
    board->rows = rows;
    board->cols = cols;
    board->mines = mines;
    // ALOKUJEMY PAMIĘĆ DLA KOMÓREK 
    board->cells = malloc(rows * sizeof(int*));
    board->visible = malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        board->cells[i] = calloc(cols, sizeof(int));
        board->visible[i] = calloc(cols, sizeof(int));
    }

    return board;
}

void freeBoard(Board* board) {
    for (int i = 0; i < board->rows; i++) {
        free(board->cells[i]);
        free(board->visible[i]);
    }
    free(board->cells);
    free(board->visible);
    free(board);
}

void printBoard(const Board* board, int revealMines) {
    printf("  ");
    for (int col = 0; col < board->cols; col++) {
        printf("%2d ", col);
    }
    printf("\n");

    for (int row = 0; row < board->rows; row++) {
        printf("%2d ", row);
        for (int col = 0; col < board->cols; col++) {
            if (board->visible[row][col] == 1) {
                printf("%2d ", countAdjacentMines(board, row, col));
            }
            else if (board->visible[row][col] == 2) {
                printf(" F ");
            }
            else if (revealMines && board->cells[row][col] == 1) {
                printf(" M ");
            }
            else {
                printf(" . ");
            }
        }
        printf("\n");
    }
}

int countAdjacentMines(const Board* board, int row, int col) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int r = row + i, c = col + j;
            if (r >= 0 && r < board->rows && c >= 0 && c < board->cols) {
                count += board->cells[r][c];
            }
        }
    }
    return count;
}

void placeMines(Board* board, int firstX, int firstY) {
    int placedMines = 0;
    while (placedMines < board->mines) {
        int row = rand() % board->rows;
        int col = rand() % board->cols;
        if (board->cells[row][col] == 0 && !(row == firstX && col == firstY)) {
            board->cells[row][col] = 1;
            placedMines++;
        }
    }
}