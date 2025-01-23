#ifndef GAME_H
#define GAME_H

#include "board.h"

typedef struct {
    int rows;
    int cols;
    int mines;
} Difficulty;

void playGame(Difficulty difficulty);
void playGameFromFile(const char* filePath); // Dodaj tę deklarację

#endif

