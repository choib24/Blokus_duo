#ifndef FILE_H
#define FILE_H
#include "game.h"
#include "check.h"

FILE *fp;

void createReplayFile(FILE *fp);
void updateReplayFile(FILE *fp);
void printFromFile(FILE *fp);

#endif