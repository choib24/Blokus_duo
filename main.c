#pragma warning(disable: 4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<Windows.h>
#include<math.h>

#define EMPTY 0
#define BLOCK 1
#define START 2
#define ORANGE 3
#define VIOLET 4
#define BOARD_SIZE 14

int board[BOARD_SIZE][BOARD_SIZE] = { EMPTY };

typedef struct _PIECES_INFO
{
	char key;
	int space;
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


void clearBoard()
{
	int i, j;
	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
			board[i][j] = 0;
	}
}

void initGame()
{
	board[4][4] = START;
	board[9][9] = START;
}

int isValidBlockKey(char key)
{
	if ((key >= '0' && key <= '9') || (key >= 'a' && key <= 'k'))
		return 1;
	else return 0;
}

int isValidCoordinate(char coordinate)
{
	if ((coordinate >= '1' && coordinate <= '9') || (coordinate >= 'A' && coordinate <= 'E'))
		return 1;
	else return 0;
}

int isAlreadyUsed(Player player, char blockKey)
{
	int i=0;

	while (i < 21)
	{
		if (player.playerBlock[i].piece.key == blockKey)
			break;
		else i++;
	}

	if (player.playerBlock[i].key != 1)
		return 1;
	else return 0;
}

int isInitialMove(Player player)
{
	if (player.leftover == 89)
		return 1;
	else return 0;
}

Piece findBlock(Player player, char key)
{
	int i;
	for (i = 0; i < 21; i++)
	{
		if (key == player.playerBlock[i].piece.key)
			return player.playerBlock[i].piece;
	}
}

int findBlockIndex(Player player, char key)
{
	int i;
	for (i = 0; i < 21; i++)
	{
		if (key == player.playerBlock[i].piece.key)
			return i;
	}

	return -1; //failure
}

int getLocation(char coordinate)
{
	int coordinateInt;
	switch (coordinate)
	{
	case 'A':
		coordinateInt = 9;
		break;
	case 'B':
		coordinateInt = 10;
		break;
	case 'C':
		coordinateInt = 11;
		break;
	case 'D':
		coordinateInt = 12;
		break;
	case 'E':
		coordinateInt = 13;
		break;
	default:
		coordinateInt = coordinate - '1';
		break;
	}

	return coordinateInt;
}

int findNearestStartingPoint(int blockAxisX, int blockAxisY)
{
	double distance1Exp = pow((blockAxisX - 4), 2) + pow((blockAxisY - 4), 2);
	double distance2Exp = pow((blockAxisX - 9), 2) + pow((blockAxisY - 9), 2);

	if (distance1Exp < distance2Exp)
		return 4;
	else return 9;
}

int isValidFirstMove(int blockAxisX, int blockAxisY)
{
	int startPoint = findNearestStartingPoint(blockAxisX, blockAxisY);

	if (board[startPoint][startPoint] != BLOCK)
		return 0;
	else return 1;
}

int isPlaceable(Piece piece, int blockAxisX, int blockAxisY)
{
	int i, j;
	int blockX = 0;
	int blockY = 0;
	int count = 0;

	for (i = blockAxisY - 2; i < blockAxisY + 3; i++)
	{
		for (j = blockAxisX - 2; j < blockAxisX + 3; j++)
		{
			if (piece.shape[blockY][blockX] == BLOCK)
			{
				if (board[i][j] != EMPTY && board[i][j] != START)
					count++;
			}
			blockX++;
		}
		blockY++;
		blockX = 0;
	}

	if (count == piece.space)
		return 1;
	else return 0;
}

int isEdge(int xCor, int yCor)
{
	int isHorizontallyOpen = 0;
	int isVerticallyOpen = 0;

	if (board[yCor - 1][xCor] == EMPTY || board[yCor + 1][xCor] == EMPTY)
		isVerticallyOpen = 1;

	if (board[yCor][xCor - 1] == EMPTY || board[yCor][xCor + 1] == EMPTY)
		isHorizontallyOpen = 1;

	if (isHorizontallyOpen && isVerticallyOpen)
		return 1;
	else return 0;
}

int isCornerTouching(int color, int xCor, int yCor)
{
	if (board[yCor - 1][xCor - 1] != color)
		return 0;
	if (board[yCor + 1][xCor - 1] != color)
		return 0;
	if (board[yCor - 1][xCor + 1] != color)
		return 0;
	if (board[yCor + 1][xCor + 1] != color)
		return 0;

	return 1;
}

int isAdjacent(int color, int xCor, int yCor)
{
	if (board[yCor - 1][xCor] == color)
		return 1;
	if (board[yCor + 1][xCor] == color)
		return 1;
	if (board[yCor][xCor - 1] == color)
		return 1;
	if (board[yCor][xCor + 1] == color)
		return 1;

	return 0;
}

int isValidMove(Player player, int blockAxisX, int blockAxisY)
{
	int boardYcor; 
	int boardXcor; 
	int blockXcor = 0;
	int blockYcor = 0;
	int isAtLeastOneCornerTouching = 0;

	for (boardYcor = blockAxisY - 2; boardYcor < blockAxisY + 3; boardYcor++)
	{
		for (boardXcor = blockAxisX - 2; boardXcor < blockAxisX + 3; boardXcor++)
		{
			if (board[blockYcor][blockXcor] == BLOCK)
			{
				if (isEdge(boardYcor, boardXcor))
				{
					if (isCornerTouching(player.color, boardXcor, boardYcor))
						isAtLeastOneCornerTouching = 1;
				}
				
				if (isAdjacent(player.color, boardXcor, boardYcor))
					return 0;
			}

			blockXcor++;
		}
		blockYcor++;
		blockXcor = 0;
	}

	if (isAtLeastOneCornerTouching)
		return 1;
	else return 0;
}

int isOutofBounds(int coordinate)
{
	if (coordinate < 0 || coordinate >= BOARD_SIZE)
		return 1;
	else return 0;
}

void putBlock(Player player, char key, int xCorChar, int yCorChar)
{
	int boardYcor, boardXcor;
	int blockXcor = 0;
	int blockYcor = 0;
	int axisX = getLocation(xCorChar);
	int axisY = getLocation(yCorChar);

	const int blockKey = findBlockIndex(player, key);

	for (boardYcor = axisY - 2; boardYcor < axisY + 3; boardYcor++)
	{
		for (boardXcor = axisX - 2; boardXcor < axisX + 3; boardXcor++)
		{

			if (player.playerBlock[blockKey].piece.shape[blockYcor][blockXcor] == BLOCK && (board[boardYcor][boardXcor] == EMPTY || board[boardYcor][boardXcor] == START))
			{
				if (isOutofBounds(boardYcor) || isOutofBounds(boardXcor))
				{
					blockXcor++;
					continue;
				}

				board[boardYcor][boardXcor] = BLOCK;
			}

			blockXcor++;
		}

		blockYcor++;
		blockXcor = 0;
	}
}

void moveRight(int blockAxisX, int blockAxisY)
{
	
}

int getAdditionalAction(int status)
{
	char userAction;
	int doItAgain = 1; //Enter(confirm): 0, otherwise 1

	if (status == -1)
		printf("Current move is invalid \n\n");
	else printf("Current move is valid \n\n");

	printf("¡æ:move right  ¡ç:move left ¡è:move up  ¡é:move down \n");
	printf("z:mirror  x:flip  c:rotate clockwise  v:rotate counterclockwise \n\n");
	printf("Choose your action. Press Enter to confirm your current move: ");
	userAction = getch();
	if (userAction == -32 || userAction == 0 || userAction == 0xE0) //for arrow keys
		userAction = getch();
	
	//userAction switch-case. Currently temporary.
	switch (userAction)
	{
	case 77: //right arrow
		printf("move right");
		break;
	case 75: //left arrow
		printf("move left");
		break;
	case 72: //up arrow
		printf("move up");
		break;
	case 80: //down arrow
		printf("move down");
		break;
	case 'z':
		printf("mirror");
		break;
	case 'x':
		printf("flip");
		break;
	case 'c':
		printf("rotate clockwise");
		break;
	case 'v':
		printf("rotate counterclockwise");
		break;
	case 13: //Enter
		printf("\nConfirm current action \n");
		doItAgain = 0;
		break;
	default:
		break;
	}

	return doItAgain;
}

char getBlockKeyInput(Player player)
{
	char blockKeyUserInput;

	printf("Enter block key: ");
	blockKeyUserInput = getch();
	while (!isValidBlockKey(blockKeyUserInput))
	{
		printf("\r%c: invalid block key. Enter valid block key: ", blockKeyUserInput);
		blockKeyUserInput = getch();
	}
	while (isAlreadyUsed(player, blockKeyUserInput))
	{
		printf("\r%c: Already used block. Enter unused block key: ", blockKeyUserInput);
		blockKeyUserInput = getch();
	}
	putch(blockKeyUserInput);
	printf("\n");

	return blockKeyUserInput;
}

char getXcorInput()
{
	char xCorUserInput;
	printf("Enter X Coordinate: ");
	xCorUserInput = getch();
	while (!isValidCoordinate(xCorUserInput))
	{
		printf("\r%c: invalid coordinate. Enter valid coordinate: ", xCorUserInput);
		xCorUserInput = getch();
	}
	putch(xCorUserInput);
	printf("\n");

	return xCorUserInput;
}

char getYcorInput()
{
	char yCorUserInput;
	printf("Enter Y Coordinate: ");
	yCorUserInput = getch();
	while (!isValidCoordinate(yCorUserInput))
	{
		printf("\r%c: invalid coordinate. Enter valid coordinate: ", yCorUserInput);
		yCorUserInput = getch();
	}
	putch(yCorUserInput);
	printf("\n");

	return yCorUserInput;
}

void printScr(int status)
{
	int i, j;

	system("cls");

	printf("--BLOCK KEY INFO-- \n");
	printf("F:0 I:1 L:2 N:3 P:4 T:5 U:6 \n");
	printf("V:7 W:8 X:9 Y:a Z:b i:c j:d \n");
	printf("o:e s:f t:g v:h three:i two:j one:k \n\n");
	printf("    1 2 3 4 5 6 7 8 9 A B C D E \n");

	for (i = 0; i < BOARD_SIZE; i++)
	{
		switch (i + 1)
		{
		case 10:
			printf(" A ");
			break;
		case 11:
			printf(" B ");
			break;
		case 12:
			printf(" C ");
			break;
		case 13:
			printf(" D ");
			break;
		case 14:
			printf(" E ");
			break;
		default:
			printf(" %d ", i + 1);
			break;
		}

		for (j = 0; j < BOARD_SIZE; j++)
		{
			switch (board[i][j])
			{
			case BLOCK:
				if(status == -1)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
				printf("¡á");
				break;
			case ORANGE:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				printf("¡á");
				break;
			case VIOLET:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
				printf("¡á");
				break;
			case START:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				printf("¡Ú");
				break;
			default:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				printf("¡à");
				break;
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		printf("\n");
	}
}

int main(void)
{
	char blockKeyChar, xCorChar, yCorChar;
	int move = 0;
	int turn;
	int status; //whether current move is valid or not
	Player orange, violet;
	Piece F, I, L, N, P, T, U, V, W, X, Y, Z, i, j, o, s, t, v, three, two, one;

	/* BLOCK INFO */

	F.space = 5;
	F.key = '0';
	F.shape[1][2] = BLOCK;
	F.shape[1][3] = BLOCK;
	F.shape[2][1] = BLOCK;
	F.shape[2][2] = BLOCK;
	F.shape[3][2] = BLOCK;

	I.space = 5;
	I.key = '1';
	I.shape[0][2] = BLOCK;
	I.shape[1][2] = BLOCK;
	I.shape[2][2] = BLOCK;
	I.shape[3][2] = BLOCK;
	I.shape[4][2] = BLOCK;

	L.space = 5;
	L.key = '2';
	L.shape[0][2] = BLOCK;
	L.shape[1][2] = BLOCK;
	L.shape[2][2] = BLOCK;
	L.shape[3][2] = BLOCK;
	L.shape[3][3] = BLOCK;

	N.space = 5;
	N.key = '3';
	N.shape[1][2] = BLOCK;
	N.shape[2][2] = BLOCK;
	N.shape[3][1] = BLOCK;
	N.shape[3][2] = BLOCK;
	N.shape[4][1] = BLOCK;

	P.space = 5;
	P.key = '4';
	P.shape[2][2] = BLOCK;
	P.shape[2][3] = BLOCK;
	P.shape[3][2] = BLOCK;
	P.shape[3][3] = BLOCK;
	P.shape[4][2] = BLOCK;

	T.space = 5;
	T.key = '5';
	T.shape[2][1] = BLOCK;
	T.shape[2][2] = BLOCK;
	T.shape[2][3] = BLOCK;
	T.shape[3][2] = BLOCK;
	T.shape[4][2] = BLOCK;

	U.space = 5;
	U.key = '6';
	U.shape[1][1] = BLOCK;
	U.shape[1][3] = BLOCK;
	U.shape[2][1] = BLOCK;
	U.shape[2][2] = BLOCK;
	U.shape[2][3] = BLOCK;

	V.space = 5;
	V.key = '7';
	V.shape[0][2] = BLOCK;
	V.shape[1][2] = BLOCK;
	V.shape[2][2] = BLOCK;
	V.shape[2][3] = BLOCK;
	V.shape[2][4] = BLOCK;

	W.space = 5;
	W.key = '8';
	W.shape[1][1] = BLOCK;
	W.shape[2][1] = BLOCK;
	W.shape[2][2] = BLOCK;
	W.shape[3][2] = BLOCK;
	W.shape[3][3] = BLOCK;

	X.space = 5;
	X.key = '9';
	X.shape[1][2] = BLOCK;
	X.shape[2][1] = BLOCK;
	X.shape[2][2] = BLOCK;
	X.shape[2][3] = BLOCK;
	X.shape[3][2] = BLOCK;

	Y.space = 5;
	Y.key = 'a';
	Y.shape[1][2] = BLOCK;
	Y.shape[2][1] = BLOCK;
	Y.shape[2][2] = BLOCK;
	Y.shape[3][2] = BLOCK;
	Y.shape[4][2] = BLOCK;

	Z.space = 5;
	Z.key = 'b';
	Z.shape[1][1] = BLOCK;
	Z.shape[2][1] = BLOCK;
	Z.shape[2][2] = BLOCK;
	Z.shape[2][3] = BLOCK;
	Z.shape[3][3] = BLOCK;

	i.space = 4;
	i.key = 'c';
	i.shape[1][2] = BLOCK;
	i.shape[2][2] = BLOCK;
	i.shape[3][2] = BLOCK;
	i.shape[4][2] = BLOCK;

	j.space = 4;
	j.key = 'd';
	j.shape[0][2] = BLOCK;
	j.shape[1][2] = BLOCK;
	j.shape[2][1] = BLOCK;
	j.shape[2][2] = BLOCK;

	o.space = 4;
	o.key = 'e';
	o.shape[1][1] = BLOCK;
	o.shape[1][2] = BLOCK;
	o.shape[2][1] = BLOCK;
	o.shape[2][2] = BLOCK;

	s.space = 4;
	s.key = 'f';
	s.shape[1][2] = BLOCK;
	s.shape[1][3] = BLOCK;
	s.shape[2][1] = BLOCK;
	s.shape[2][2] = BLOCK;

	t.space = 4;
	t.key = 'g';
	t.shape[1][2] = BLOCK;
	t.shape[2][1] = BLOCK;
	t.shape[2][2] = BLOCK;
	t.shape[2][3] = BLOCK;

	v.space = 4;
	v.key = 'h';
	v.shape[1][2] = BLOCK;
	v.shape[2][2] = BLOCK;
	v.shape[2][3] = BLOCK;

	three.space = 3;;
	three.key = 'i';
	three.shape[1][2] = BLOCK;
	three.shape[2][2] = BLOCK;
	three.shape[3][2] = BLOCK;

	two.space = 2;
	two.key = 'j';
	two.shape[1][2] = BLOCK;
	two.shape[2][2] = BLOCK;

	one.space = 1;
	one.key = 'k';
	one.shape[2][2] = BLOCK;

	move = 0;
	
	orange.color = ORANGE;
	violet.color = VIOLET;
	
	orange.leftover = 89;
	violet.leftover = 89;

	for (int i = 0; i < 21; i++)
	{
		orange.playerBlock[i].key = 1;
		violet.playerBlock[i].key = 1;
	}

	orange.playerBlock[0].piece = F;
	orange.playerBlock[1].piece = I;
	orange.playerBlock[2].piece = L;
	orange.playerBlock[3].piece = N;
	orange.playerBlock[4].piece = P;
	orange.playerBlock[5].piece = T;
	orange.playerBlock[6].piece = U;
	orange.playerBlock[7].piece = V;
	orange.playerBlock[8].piece = W;
	orange.playerBlock[9].piece = X;
	orange.playerBlock[10].piece = Y;
	orange.playerBlock[11].piece = Z;
	orange.playerBlock[12].piece = i;
	orange.playerBlock[13].piece = j;
	orange.playerBlock[14].piece = o;
	orange.playerBlock[15].piece = s;
	orange.playerBlock[16].piece = t;
	orange.playerBlock[17].piece = v;
	orange.playerBlock[18].piece = three;
	orange.playerBlock[19].piece = two;
	orange.playerBlock[20].piece = one;

	violet.playerBlock[0].piece = F;
	violet.playerBlock[1].piece = I;
	violet.playerBlock[2].piece = L;
	violet.playerBlock[3].piece = N;
	violet.playerBlock[4].piece = P;
	violet.playerBlock[5].piece = T;
	violet.playerBlock[6].piece = U;
	violet.playerBlock[7].piece = V;
	violet.playerBlock[8].piece = W;
	violet.playerBlock[9].piece = X;
	violet.playerBlock[10].piece = Y;
	violet.playerBlock[11].piece = Z;
	violet.playerBlock[12].piece = i;
	violet.playerBlock[13].piece = j;
	violet.playerBlock[14].piece = o;
	violet.playerBlock[15].piece = s;
	violet.playerBlock[16].piece = t;
	violet.playerBlock[17].piece = v;
	violet.playerBlock[18].piece = three;
	violet.playerBlock[19].piece = two;
	violet.playerBlock[20].piece = one;

	//Game process
	turn = ORANGE;
	status = 1;
	clearBoard();
	initGame();

	while (1)
	{
		printScr(status);

		blockKeyChar = getBlockKeyInput(orange);
		xCorChar = getXcorInput();
		yCorChar = getYcorInput();

		putBlock(orange, blockKeyChar, xCorChar, yCorChar);

		Sleep(700);

		if (isInitialMove(orange))
		{
			if (!isValidFirstMove(getLocation(xCorChar), getLocation(yCorChar)))
				status = -1;
		}
		else if (!isValidMove(orange, getLocation(xCorChar), getLocation(yCorChar)))
			status = -1;

		while (1)
		{
			printScr(status);

			if (!getAdditionalAction(status))
				break;
			else Sleep(700);
		}

		return 0; //temporary
	}

	return 0;
}