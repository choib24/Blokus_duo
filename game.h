#ifndef GAME_H
#define GAME_H

#pragma warning(disable:4996)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<Windows.h>
#include<math.h>

#define EMPTY 0
#define BLOCK 2
#define ORANGE 1
#define VIOLET -1
#define BOARD_SIZE 14

int board[24][24];
int move;
int status; //1: valid -1: error
int turn;

typedef struct _BLOCK_INFO
{
	int space;
	int shape[5][5];
}Block;

typedef struct _HASHMAP
{
	int isAvailable; //1=available 0=used
	Block block;
}HashMap;

typedef struct _PLAYER_INFO
{
	int isOver; //if 1, player cannot place blocks anymore
	char color; //orange or violet
	int leftoverSpaces; //initial value is 89
	HashMap blockList[21];
}Player;

int selectMode();
void setLeftSpacesZero(int(*board)[5]);
void clearBoard();
void initGame(Player *orange, Player *violet);
void printScr(Player orange, Player violet);
int endGame(Player orange, Player violet);

#endif