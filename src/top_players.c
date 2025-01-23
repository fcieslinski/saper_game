#include "top_players.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOP_PLAYERS 5

typedef struct {
    char name[50];
    int score;
} Player;

Player topPlayers[MAX_TOP_PLAYERS];

void loadTopPlayersFromFile() {
    FILE* file = fopen("top_players.txt", "r");
    if (!file) return;

    for (int i = 0; i < MAX_TOP_PLAYERS; i++) {
        if (fscanf(file, "%49s %d", topPlayers[i].name, &topPlayers[i].score) != 2) break;
    }
    fclose(file);
}

void saveTopPlayersToFile() {
    FILE* file = fopen("top_players.txt", "w");
    if (!file) return;

    for (int i = 0; i < MAX_TOP_PLAYERS && topPlayers[i].score > 0; i++) {
        fprintf(file, "%s %d\n", topPlayers[i].name, topPlayers[i].score);
    }
    fclose(file);
}

void addNewTopPlayer(const char* name, int score) {
    for (int i = 0; i < MAX_TOP_PLAYERS; i++) {
        if (topPlayers[i].score < score) {
            for (int j = MAX_TOP_PLAYERS - 1; j > i; j--) {
                topPlayers[j] = topPlayers[j - 1];
            }
            strncpy(topPlayers[i].name, name, sizeof(topPlayers[i].name) - 1);
            topPlayers[i].name[sizeof(topPlayers[i].name) - 1] = '\0';
            topPlayers[i].score = score;
            break;
        }
    }
}

void printTopPlayers() {
    printf("Top %d Graczy:\n", MAX_TOP_PLAYERS);
    for (int i = 0; i < MAX_TOP_PLAYERS && topPlayers[i].score > 0; i++) {
        printf("%d. %s - %d points\n", i + 1, topPlayers[i].name, topPlayers[i].score);
    }
}
