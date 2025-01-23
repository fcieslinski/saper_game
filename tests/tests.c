#include "board.h"
#include "game.h"
#include "top_players.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void testCreateBoard() {
    Board* board = createBoard(9, 9, 10);
    assert(board != NULL);
    assert(board->rows == 9);
    assert(board->cols == 9);
    assert(board->mines == 10);
    freeBoard(board);
    printf("Test tworzenia planszy zakończony sukcesem\n");
}

void testPlaceMines() {
    Board* board = createBoard(5, 5, 5);
    placeMines(board, 0, 0);
    int mineCount = 0;
    for (int i = 0; i < board->rows; i++) {
        for (int j = 0; j < board->cols; j++) {
            mineCount += board->cells[i][j];
        }
    }
    assert(mineCount == 5);
    freeBoard(board);
    printf("Test rozmieszczania min zakończony sukcesem\n");
}

void testPlayGameFromFile() {
    const char* filePath = "test_plansza.txt";
    FILE* file = fopen(filePath, "w");
    fprintf(file, "5 5 3\n");
    fprintf(file, "0 0 1 0 0\n");
    fprintf(file, "0 0 0 0 0\n");
    fprintf(file, "1 0 0 0 0\n");
    fprintf(file, "0 0 0 1 0\n");
    fprintf(file, "0 0 0 0 0\n");
    fprintf(file, "r 0 0\n");
    fprintf(file, "f 0 2\n");
    fprintf(file, "r 4 4\n");
    fclose(file);

    playGameFromFile(filePath);

    remove(filePath);
    printf("Test wczytywania planszy i ruchów z pliku zakończony sukcesem\n");
}

int main() {
    printf("Uruchamianie testów\n");
    testCreateBoard();
    testPlaceMines();
    testPlayGameFromFile();
    printf("Wszystkie testy zakończone sukcesem\n");
    return 0;
}

