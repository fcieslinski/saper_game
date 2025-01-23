#ifndef BOARD_H
#define BOARD_H

typedef struct {
    int rows;
    int cols;
    int mines;
    int** cells;
    int** visible;
} Board;

Board* createBoard(int rows, int cols, int mines);
void freeBoard(Board* board);
void printBoard(const Board* board, int revealMines);
int countAdjacentMines(const Board* board, int row, int col);
void placeMines(Board* board, int firstX, int firstY); // Deklaracja dla placeMines

#endif

