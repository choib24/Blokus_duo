#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define EMPTY 0
#define BLOCK 1
#define START 2
#define ORANGE 1
#define VIOLET -1
#define BOARD_SIZE 14

typedef struct _PIECES_INFO
{
	char key;
	int height;
	int width;
	int shape[5][5];
}Piece;

typedef struct _HashMap
{
	int key;
	Piece piece;
}HashMap;

typedef struct _PLAYER_INFO
{
	int color; //1: orange. -1: violet
	int leftover; 
	HashMap playerBlock[21];
}Player;

typedef struct _GAME_INFO
{
	int move; //total move
	Player orange, violet; //player
	int board[14][14];
}Game;

int isValidBlockKey(char key)
{
	//need to implement
	return 1;
}

void printScr(int (*board)[BOARD_SIZE])
{
	int i,j;

	system("clear");

	printf("--BLOCK KEY INFO--\n");
	printf("F:0 I:1 L:2 N:3 P:4 T:5 U:6\n");
	printf("V:7 W:8 X:9 Y:a Z:b i:c j:d\n");
	printf("o:e s:f t:g v:h three:i two:j one:k\n\n");

	printf("  1 2 3 4 5 6 7 8 9 A B C D E \n");

	for(i=0; i<BOARD_SIZE; i++)
	{
		switch(i+1)
		{
			case 10:
				printf("A ");
				break;
			case 11:
				printf("B ");
				break;
			case 12:
				printf("C ");
				break;
			case 13:
				printf("D ");
				break;
			case 14:
				printf("E ");
				break;
			default:
				printf("%d ", i+1);
				break;
		}
		
		//NO spaces between blocks needed in windows. ONLY in terminal.
		for(j=0; j<BOARD_SIZE; j++)
		{
			switch(board[i][j])
			{
				case ORANGE:
					//set color to orange.
					//in Windows, use SetConSoleTextAttribute(Windows.h)
					printf("%c[1;33m",27);
					printf("◼︎ ");
					printf("%c[0m\n",27);
					break;
				case VIOLET:
					printf("%c[1;35m",27);
					printf("◼︎ ");
					printf("%c[0m\n",27);
					break;
				case START:
					printf("✩ ");
					break;
				default:
					printf("☐ ");
					break;
			}
		}
		printf("\n");
	}
	printf("\n");
}

int isValidKey(char key)
{
	if((key>='0' && key<=9) || (key>='a' && key<='k'))
		return 1;
	else return 0;
}

int isValidCoordinate(char coordinate)
{
	if((coordinate>='1' && coordinate<'9') || (coordinate>='A' && coordinate<='E'))
		return 1;
	else return 0;
}

void getUserInput(Player p)
{
	char blockKey, xCor, yCor;

	printf("Enter the block key: ");
	blockKey=getchar();
	while(!isValidKey(blockKey))
	{
		printf("Invalid block key. Enter valid block key: ");
		blockKey=getchar();
	}
	
	printf("Enter x coordinate: ");
	xCor=getchar();
	while(!isValidCoordinate(xCor))
	{
		printf("Invalid x coordinate. Enter valid coordinate: ");
		xCor=getchar();
	}

	printf("Enter y coordinate: ");
	yCor=getchar();
	while(!isValidCoordinate(yCor))
	{
		printf("Invalid y coordinate. Enter valid coordinate: ");
		yCor=getchar();
	}
}

int main(void)
{
	Game game;
	Piece F, I, L, N, P, T, U, V, W, X, Y, Z, i, j, o, s, t, v, three, two, one;

	/* BLOCK INFO */

	F.height = 3;
	F.width = 3;
	F.key = '0';
	F.shape[1][2] = BLOCK;
	F.shape[1][3] = BLOCK;
	F.shape[2][1] = BLOCK;
	F.shape[2][2] = BLOCK;
	F.shape[3][2] = BLOCK;

	I.height = 5;
	I.width = 1;
	I.key = '1';
	I.shape[0][2] = BLOCK;
	I.shape[1][2] = BLOCK;
	I.shape[2][2] = BLOCK;
	I.shape[2][3] = BLOCK;
	I.shape[2][4] = BLOCK;

	L.height = 4;
	L.width = 2;
	L.key = '2';
	L.shape[0][2] = BLOCK;
	L.shape[1][2] = BLOCK;
	L.shape[2][2] = BLOCK;
	L.shape[3][2] = BLOCK;
	L.shape[4][2] = BLOCK;

	N.height = 4;
	N.width = 2;
	N.key = '3';
	N.shape[1][2] = BLOCK;
	N.shape[2][2] = BLOCK;
	N.shape[3][1] = BLOCK;
	N.shape[3][2] = BLOCK;
	N.shape[4][1] = BLOCK;

	P.height = 3;
	P.width = 2;
	P.key = '4';
	P.shape[2][2] = BLOCK;
	P.shape[2][3] = BLOCK;
	P.shape[3][2] = BLOCK;
	P.shape[3][3] = BLOCK;
	P.shape[4][2] = BLOCK;

	T.height = 3;
	T.width = 3;
	T.key = '5';
	T.shape[2][1] = BLOCK;
	T.shape[2][2] = BLOCK;
	T.shape[2][3] = BLOCK;
	T.shape[3][2] = BLOCK;
	T.shape[4][2] = BLOCK;

	U.height = 2;
	U.width = 3;
	U.key = '6';
	U.shape[1][1] = BLOCK;
	U.shape[1][3] = BLOCK;
	U.shape[2][1] = BLOCK;
	U.shape[2][2] = BLOCK;
	U.shape[2][3] = BLOCK;

	V.height = 3;
	V.width = 3;
	V.key = '7';
	V.shape[0][2] = BLOCK;
	V.shape[1][2] = BLOCK;
	V.shape[2][2] = BLOCK;
	V.shape[2][3] = BLOCK;
	V.shape[2][4] = BLOCK;

	W.height = 3;
	W.width = 3;
	W.key = '8';
	W.shape[1][1] = BLOCK;
	W.shape[2][1] = BLOCK;
	W.shape[2][2] = BLOCK;
	W.shape[3][2] = BLOCK;
	W.shape[3][3] = BLOCK;

	X.height = 3;
	X.width = 3;
	X.key = '9';
	X.shape[1][2] = BLOCK;
	X.shape[2][1] = BLOCK;
	X.shape[2][2] = BLOCK;
	X.shape[2][3] = BLOCK;
	X.shape[3][2] = BLOCK;

	Y.height = 4;
	Y.width = 2;
	Y.key = 'a';
	Y.shape[1][2] = BLOCK;
	Y.shape[2][1] = BLOCK;
	Y.shape[2][2] = BLOCK;
	Y.shape[3][2] = BLOCK;
	Y.shape[4][2] = BLOCK;

	Z.height = 3;
	Z.width = 3;
	Z.key = 'b';
	Z.shape[1][1] = BLOCK;
	Z.shape[2][1] = BLOCK;
	Z.shape[2][2] = BLOCK;
	Z.shape[2][3] = BLOCK;
	Z.shape[3][3] = BLOCK;

	i.height = 4;
	i.width = 1;
	i.key = 'c';
	i.shape[1][2] = BLOCK;
	i.shape[2][2] = BLOCK;
	i.shape[3][2] = BLOCK;
	i.shape[4][2] = BLOCK;

	j.height = 3;
	j.width = 2;
	j.key = 'd';
	j.shape[0][2] = BLOCK;
	j.shape[1][2] = BLOCK;
	j.shape[2][1] = BLOCK;
	j.shape[2][2] = BLOCK;

	o.height = 2;
	o.width = 2;
	o.key = 'e';
	o.shape[1][1] = BLOCK;
	o.shape[1][2] = BLOCK;
	o.shape[2][1] = BLOCK;
	o.shape[2][2] = BLOCK;

	s.height = 2;
	s.width = 3;
	s.key = 'f';
	s.shape[1][2] = BLOCK;
	s.shape[1][3] = BLOCK;
	s.shape[2][1] = BLOCK;
	s.shape[2][2] = BLOCK;

	t.height = 2;
	t.width = 3;
	t.key = 'g';
	t.shape[1][2] = BLOCK;
	t.shape[2][1] = BLOCK;
	t.shape[2][2] = BLOCK;
	t.shape[2][3] = BLOCK;

	v.height = 2;
	v.width = 2;
	v.key = 'h';
	v.shape[1][2] = BLOCK;
	v.shape[2][2] = BLOCK;
	v.shape[2][3] = BLOCK;

	three.height = 3;
	three.width = 1;
	three.key = 'i';
	three.shape[1][2] = BLOCK;
	three.shape[2][2] = BLOCK;
	three.shape[3][2] = BLOCK;

	two.height = 2;
	two.width = 1;
	two.key = 'j';
	two.shape[1][2] = BLOCK;
	two.shape[2][2] = BLOCK;

	one.height = 1;
	one.width = 1;
	one.key = 'k';
	one.shape[2][2] = BLOCK;

	game.move = 0;
	
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
			game.board[i][j] = 0;
	}
	game.board[4][4] = START;
	game.board[9][9] = START;

	game.orange.color = 1;
	game.violet.color = -1;
	
	game.orange.leftover = 89;
	game.violet.leftover = 89;

	for (int i = 0; i < 21; i++)
	{
		game.orange.playerBlock[i].key = 1;
		game.violet.playerBlock[i].key = 1;
	}

	game.orange.playerBlock[0].piece = F;
	game.orange.playerBlock[1].piece = I;
	game.orange.playerBlock[2].piece = L;
	game.orange.playerBlock[3].piece = N;
	game.orange.playerBlock[4].piece = P;
	game.orange.playerBlock[5].piece = T;
	game.orange.playerBlock[6].piece = U;
	game.orange.playerBlock[7].piece = V;
	game.orange.playerBlock[8].piece = W;
	game.orange.playerBlock[9].piece = X;
	game.orange.playerBlock[10].piece = Y;
	game.orange.playerBlock[11].piece = Z;
	game.orange.playerBlock[12].piece = i;
	game.orange.playerBlock[13].piece = j;
	game.orange.playerBlock[14].piece = o;
	game.orange.playerBlock[15].piece = s;
	game.orange.playerBlock[16].piece = t;
	game.orange.playerBlock[17].piece = v;
	game.orange.playerBlock[18].piece = three;
	game.orange.playerBlock[19].piece = two;
	game.orange.playerBlock[20].piece = one;

	game.violet.playerBlock[0].piece = F;
	game.violet.playerBlock[1].piece = I;
	game.violet.playerBlock[2].piece = L;
	game.violet.playerBlock[3].piece = N;
	game.violet.playerBlock[4].piece = P;
	game.violet.playerBlock[5].piece = T;
	game.violet.playerBlock[6].piece = U;
	game.violet.playerBlock[7].piece = V;
	game.violet.playerBlock[8].piece = W;
	game.violet.playerBlock[9].piece = X;
	game.violet.playerBlock[10].piece = Y;
	game.violet.playerBlock[11].piece = Z;
	game.violet.playerBlock[12].piece = i;
	game.violet.playerBlock[13].piece = j;
	game.violet.playerBlock[14].piece = o;
	game.violet.playerBlock[15].piece = s;
	game.violet.playerBlock[16].piece = t;
	game.violet.playerBlock[17].piece = v;
	game.violet.playerBlock[18].piece = three;
	game.violet.playerBlock[19].piece = two;
	game.violet.playerBlock[20].piece = one;
	
	printScr(game.board);
	getUserInput(game.orange);

	return 0;
}
