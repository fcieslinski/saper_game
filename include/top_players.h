#ifndef TOP_PLAYERS_H
#define TOP_PLAYERS_H

void loadTopPlayersFromFile();
void saveTopPlayersToFile();
void addNewTopPlayer(const char* name, int score);
void printTopPlayers();

#endif

