#ifndef CHECK_H
#define CHECK_H
#include "game.h"

int isValidBlockIndex(int blockIndex);
int isAlreadyUsed(Player player, int index);
int isValidCoordinate(char coordinate);
int isInitialMove(Player player);
int isValidFirstMove(int blockAxisX, int blockAxisY);
int isPlaceable(Block block, int blockAxisX, int blockAxisY);
int isEdge(int xCor, int yCor);	
int isCornerTouching(int color, int xCor, int yCor);
int isAdjacent(int color, int xCor, int yCor);
int isValidMove(Player player, int blockAxisX, int blockAxisY);
int canConfirm(int status);


#endif // !CHECK_H

