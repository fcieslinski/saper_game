#include "game.h"
#include "board.h"
#include "top_players.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <getopt.h>

Difficulty difficultyLevels[] = {
    {9, 9, 10},    // Easy
    {16, 16, 40},  // Medium
    {16, 30, 99}   // Hard
};

void printUsage(const char* programName) {
    printf("Usage: %s [options]\n", programName);
    printf("Opcje:\n");
    printf("  -d [1|2|3]   Wybierz poziom trudnosci (1: Latwy, 2: Sredni, 3: Trudny)\n");
    printf("  -f <file>    Zaladuj plansze i ruchy z pliku\n");
    printf("  -c           Wlasna plansza (rows, cols, mines)\n");
    printf("  -h           Informacje (tzw. help)\n");
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    loadTopPlayersFromFile();

    int difficultyIndex = -1;
    char* inputFile = NULL;
    int customBoard = 0;

    int opt;
    while ((opt = getopt(argc, argv, "d:f:ch")) != -1) {
        switch (opt) {
        case 'd':
            difficultyIndex = atoi(optarg) - 1;
            if (difficultyIndex < 0 || difficultyIndex > 2) {
                fprintf(stderr, "Niepoprawny poziom trudnosci.\n");
                return 1;
            }
            break;
        case 'f':
            inputFile = optarg;
            break;
        case 'c':
            customBoard = 1;
            break;
        case 'h':
        default:
            printUsage(argv[0]);
            return 0;
        }
    }

    if (inputFile) {
        printf("Odtwarzanie gry z planszy: %s\n", inputFile);
        playGameFromFile(inputFile);
    } else if (customBoard) {
        int rows, cols, mines;
        printf("Zdefiniuj wlasna plansze:\n");
        printf("Podaj liczbe wierszy: ");
        scanf("%d", &rows);
        printf("Podaj liczbe kolumn: ");
        scanf("%d", &cols);
        printf("Podaj liczbe min: ");
        scanf("%d", &mines);

        if (rows <= 0 || cols <= 0 || mines <= 0 || mines >= rows * cols) {
            fprintf(stderr, "Bledne parametry planszy.\n");
            return 1;
        }

        Difficulty customDifficulty = {rows, cols, mines};
        playGame(customDifficulty);
    } else if (difficultyIndex != -1) {
        printf("Rozpoczynanie nowej gry na poziomie: %d\n", difficultyIndex + 1);
        playGame(difficultyLevels[difficultyIndex]);
    } else {
        printUsage(argv[0]);
        return 1;
    }

    printf("Koniec gry! Ranking najlepszych graczy:\n");
    printTopPlayers();
    saveTopPlayersToFile();

    return 0;
}

