#ifndef BLOCK_H
#define BLOCK_H
#include "game.h"
#include "check.h"

void putBlock(Block block, int xCor, int yCor);	
int findNearestStartingPoint(int blockAxisX, int blockAxisY);
void moveRight(Block block, int *blockAxisX, int *blockAxisY);
void moveLeft(Block block, int *blockAxisX, int *blockAxisY);
void moveDown(Block block, int *blockAxisX, int *blockAxisY);
void moveUp(Block block, int *blockAxisX, int *blockAxisY);	
void mirror(Block *block, int blockAxisX, int blockAxisY);
void flip(Block *block, int blockAxisX, int blockAxisY);
void rotateClockwise(Block *block, int blockAxisX, int blockAxisY);
void rotateCounterClockwise(Block *block, int blockAxisX, int blockAxisY);


#endif // !BLOCK_H
