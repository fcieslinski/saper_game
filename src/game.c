#include "game.h"
#include "board.h"
#include "top_players.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void playGame(Difficulty difficulty) {
    Board* board = createBoard(difficulty.rows, difficulty.cols, difficulty.mines);
    placeMines(board, -1, -1); // Miny powstaja dopiero po ruchu gracza

    int gameOver = 0;
    int firstMove = 1;
    int revealedCells = 0;

    while (!gameOver) {
        printBoard(board, 0);
        printf("Aktualny wynik: %d\n", revealedCells * difficulty.mines); // Wyświetlanie wyniku

        printf("Podaj swoj ruch (r x y aby odkryc pole, f x y aby oznaczyc flaga): ");
        char command;
        int x, y;
        if (scanf(" %c %d %d", &command, &x, &y) != 3 || x < 0 || x >= board->rows || y < 0 || y >= board->cols) {
            printf("Niepoprawne. Sprobuj ponownie.\n");
            continue;
        }

        if (firstMove) {
            placeMines(board, x, y);
            firstMove = 0;
        }

        if (command == 'r') {
            if (board->cells[x][y] == 1) {
                printf("Koniec gry! Trafiles w mine.\n");
                gameOver = 1;
                printBoard(board, 1); // Pokazuje miny
            } else if (board->visible[x][y] == 0) {
                board->visible[x][y] = 1;
                revealedCells++;
            }
        } else if (command == 'f') {
            board->visible[x][y] = board->visible[x][y] == 2 ? 0 : 2;
        } else {
            printf("Niepoprawna komenda. Uzyj 'r' aby odkryc lub 'f' aby dodac flage.\n");
        }

        // Sprawdz warunek wygranje
        if (revealedCells == (board->rows * board->cols - board->mines)) {
            printf("Gratulacje! Wyczysciles cala plansze!\n");
            gameOver = 1;
        }
    }

    // Pytanie o imię gracza i zapis wyniku
    if (gameOver) {
        char playerName[50];
        printf("Podaj swoje imie: ");
        scanf("%s", playerName);

        int finalScore = revealedCells * difficulty.mines;
        addNewTopPlayer(playerName, finalScore);

        printf("Koniec gry! Twoj finalny wynik: %d\n", finalScore);
        printTopPlayers();
    }

    freeBoard(board);
}

void playGameFromFile(const char* filePath) {
    FILE* file = fopen(filePath, "r");
    if (!file) {
        printf("Nie udalo sie otworzyc pliku: %s\n", filePath);
        return;
    }

    int rows, cols, mines;
    fscanf(file, "%d %d %d", &rows, &cols, &mines);

    Board* board = createBoard(rows, cols, mines);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fscanf(file, "%d", &board->cells[i][j]);
        }
    }

    char command;
    int x, y;
    int correctMoves = 0;
    int gameResult = 0; // 0 - przegrana, 1 - wygrana

    while (fscanf(file, " %c %d %d", &command, &x, &y) == 3) {
        if (x < 0 || x >= rows || y < 0 || y >= cols) {
            printf("Niepoprawny ruch: (%d, %d)\n", x, y);
            continue;
        }

        if (command == 'r') {
            if (board->cells[x][y] == 1) {
                printf("Koniec gry! Trafiles w mine.\n");
                gameResult = 0; // Przegrana
                break;
            } else {
                board->visible[x][y] = 1;
                correctMoves++;
            }
        } else if (command == 'f') {
            board->visible[x][y] = board->visible[x][y] == 2 ? 0 : 2;
        }
    }

    if (correctMoves == (rows * cols - mines)) {
        printf("Gratulacje! Wyczysciles plansze!\n");
        gameResult = 1; // Wygrana
    }

    printBoard(board, 1); // Final state of the board
    printf("Podsumowanie: Poprawne ruchy: %d, Punkty: %d, Wynik gry: %d\n", correctMoves, correctMoves * mines, gameResult);

    fclose(file);
    freeBoard(board);
}

