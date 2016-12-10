#ifndef PLAYER_H
#define PLAYER_H
#include "check.h"

int getLocation(char coordinate);
int getBlockIndexInput();
char getXCoordinateInput();
char getYCoordinateInput();
char getAdditionalAction();
void confirm(Player *player, int blockIndex, int blockAxisX, int blockAxisY);

#endif // !PLAYER_H
