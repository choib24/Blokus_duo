#pragma warning(disable:4996)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<Windows.h>
#include<math.h>

#define EMPTY 0
#define BLOCK 1
#define ORANGE 3
#define VIOLET 4
#define BOARD_SIZE 14

char board[24][24] = { EMPTY };

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
	char color; //orange or violet
	int leftoverSpaces; //initial value is 89
	HashMap blockList[21];
}Player;

void printScr(int status)
{
	int i, j;
	system("cls");
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
			switch (board[i + 5][j + 5])
			{
			case BLOCK:
				if (status == -1) //Invalid move
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
			default:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				//start point
				if ((i + 5 == 9 && j + 5 == 9) || (i + 5 == 14 && j + 5 == 14))
					printf("¡Ú");
				else printf("¡à");
				break;
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		printf("\n");
	}
	printf("\n");
}

int getLocation(char coordinate)
{
	int location;
	switch (coordinate)
	{
	case 'A':
		location = 14;
		break;
	case 'a':
		location = 14;
		break;
	case 'B':
		location = 15;
		break;
	case 'b':
		location = 15;
		break;
	case 'C':
		location = 16;
		break;
	case 'c':
		location = 16;
		break;
	case 'D':
		location = 17;
		break;
	case 'd':
		location = 17;
		break;
	case 'E':
		location = 18;
		break;
	case 'e':
		location = 18;
		break;
	default:
		location = coordinate - '1' + 5;
		break;
	}
	return location;
}

int isValidBlockIndex(int blockIndex)
{
	if (blockIndex > 0 && blockIndex <= 21)
		return 1;
	else return 0;
}

int isAlreadyUsed(Player player, int index)
{
	if (player.blockList[index].isAvailable != 1)
		return 1;
	else return 0;
}

int getBlockIndexInput()
{
	int input;
	printf("Enter block index: ");
	scanf("%d", &input);

	while (!isValidBlockIndex(input))
	{
		printf("Invalid block index. Enter valid block index: ");
		scanf("%d", &input);
	}

	return input;
}

int isValidCoordinate(char coordinate)
{
	if ((coordinate >= '1' && coordinate <= '9') || (coordinate >= 'A' && coordinate <= 'E') || (coordinate >= 'a' && coordinate <= 'e'))
		return 1;
	else return 0;
}

char getXCoordinateInput()
{
	char input;
	printf("Enter X coordinate: ");
	input = getch();

	while (!isValidCoordinate(input))
	{
		printf("\r%c: Invalid X coordinate. Enter valid coordinate: ", input);
		input = getch();
	}

	putch(input);
	printf("\n");

	return input;
}

char getYCoordinateInput()
{
	char input;
	printf("Enter Y coordinate: ");
	input = getch();

	while (!isValidCoordinate(input))
	{
		printf("\r%c: Invalid Y coordinate. Enter valid coordinate: ", input);
		input = getch();
	}

	putch(input);
	printf("\n");

	return input;
}

void putBlock(Block block, int xCor, int yCor)
{
	int boardX, boardY;
	int blockX = 0;
	int blockY = 0;

	for (boardY = yCor - 2; boardY < yCor + 3; boardY++)
	{
		for (boardX = xCor - 2; boardX < xCor + 3; boardX++)
		{
			if (block.shape[blockY][blockX] == BLOCK && board[boardY][boardX] == EMPTY)
				board[boardY][boardX] = BLOCK;

			blockX++;
		}
		blockY++;
		blockX = 0;
	}
}

int findNearestStartingPoint(int blockAxisX, int blockAxisY)
{
	double distance1Exp = pow((blockAxisX - 9), 2) + pow((blockAxisY - 9), 2);
	double distance2Exp = pow((blockAxisX - 14), 2) + pow((blockAxisY - 14), 2);

	if (distance1Exp < distance2Exp)
		return 9;
	else return 14;
}

int isInitialMove(Player player)
{
	if (player.leftoverSpaces == 89)
		return 1;
	else return 0;
}

int isValidFirstMove(int blockAxisX, int blockAxisY)
{
	int startPoint = findNearestStartingPoint(blockAxisX, blockAxisY);

	if (board[startPoint][startPoint] != BLOCK)
		return 0;
	else return 1;
}

int isPlaceable(Block block, int blockAxisX, int blockAxisY)
{
	int i, j;
	int blockX = 0;
	int blockY = 0;
	int count = 0;

	for (i = blockAxisY - 2; i < blockAxisY + 3; i++)
	{
		for (j = blockAxisX - 2; j < blockAxisX + 3; j++)
		{
			if (block.shape[blockY][blockX] == BLOCK)
			{
				if (board[i][j] != EMPTY)
					count++;
			}
			blockX++;
		}
		blockY++;
		blockX = 0;
	}

	if (count == block.space)
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
	if (board[yCor - 1][xCor - 1] == color)
		return 1;
	if (board[yCor + 1][xCor - 1] == color)
		return 1;
	if (board[yCor - 1][xCor + 1] == color)
		return 1;
	if (board[yCor + 1][xCor + 1] == color)
		return 1;

	return 0;
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
	int isAtLeastOneCornerTouching = 0;

	for (boardYcor = blockAxisY - 2; boardYcor < blockAxisY + 3; boardYcor++)
	{
		for (boardXcor = blockAxisX - 2; boardXcor < blockAxisX + 3; boardXcor++)
		{
			if (board[boardYcor][boardXcor] == BLOCK)
			{
				if (isEdge(boardYcor, boardXcor))
				{
					if (isCornerTouching(player.color, boardXcor, boardYcor))
						isAtLeastOneCornerTouching = 1;
				}

				if (isAdjacent(player.color, boardXcor, boardYcor))
					return 0;
			}
		}
	}

	if (isAtLeastOneCornerTouching)
		return 1;
	else return 0;
}

char getAdditionalAction(int status)
{
	char userAction;
	int doItAgain = 1; //Enter(confirm): 0, otherwise 1

	if (status == -1)
		printf("Current move is invalid \n\n");
	else printf("Current move is valid \n\n");

	printf("¡æ:move right  ¡ç:move left  ¡è:move up  ¡é:move down \n");
	printf("z:mirror  x:flip  c:rotate clockwise  v:rotate counterclockwise \n\n");
	printf("Choose your action. Press Enter to confirm your current move: ");
	userAction = getch();
	if (userAction == -32 || userAction == 0 || userAction == 0xE0) //for arrow keys
		userAction = getch();

	return userAction;
}

void moveRight(Block block, int *blockAxisX, int *blockAxisY)
{
	int boardX;
	int boardY;
	int blockX = 0;
	int blockY = 0;

	for (boardY = *blockAxisY - 2; boardY < *blockAxisY + 3; boardY++)
	{
		for (boardX = *blockAxisX - 2; boardX < *blockAxisX + 3; boardX++)
		{
			if (board[boardY][boardX] == BLOCK)
				board[boardY][boardX] = EMPTY;
		}
	}

	*blockAxisX = *blockAxisX + 1;
	
	for (boardY = *blockAxisY - 2; boardY < *blockAxisY + 3; boardY++)
	{
		for (boardX = *blockAxisX - 2; boardX < *blockAxisX + 3; boardX++)
		{
			if (block.shape[blockY][blockX] == BLOCK)
			{
				if (board[boardY][boardX] < 2)
					board[boardY][boardX] = block.shape[blockY][blockX];
			}

			blockX++;
		}
		blockY++;
		blockX = 0;
	}
}

void moveLeft(Block block, int *blockAxisX, int *blockAxisY)
{
	int boardX;
	int boardY;
	int blockX = 0;
	int blockY = 0;

	for (boardY = *blockAxisY - 2; boardY < *blockAxisY + 3; boardY++)
	{
		for (boardX = *blockAxisX - 2; boardX < *blockAxisX + 3; boardX++)
		{
			if (board[boardY][boardX] == BLOCK)
				board[boardY][boardX] = EMPTY;
		}
	}

	*blockAxisX = *blockAxisX - 1;

	for (boardY = *blockAxisY - 2; boardY < *blockAxisY + 3; boardY++)
	{
		for (boardX = *blockAxisX - 2; boardX < *blockAxisX + 3; boardX++)
		{
			if (board[boardY][boardX] < 2)
				board[boardY][boardX] = block.shape[blockY][blockX];

			blockX++;
		}
		blockY++;
		blockX = 0;
	}
}

void moveDown(Block block, int *blockAxisX, int *blockAxisY)
{
	int boardX;
	int boardY;
	int blockX = 0;
	int blockY = 0;

	for (boardY = *blockAxisY - 2; boardY < *blockAxisY + 3; boardY++)
	{
		for (boardX = *blockAxisX - 2; boardX < *blockAxisX + 3; boardX++)
		{
			if (board[boardY][boardX] == BLOCK)
				board[boardY][boardX] = EMPTY;
		}
	}

	*blockAxisY = *blockAxisY + 1;

	for (boardY = *blockAxisY - 2; boardY < *blockAxisY + 3; boardY++)
	{
		for (boardX = *blockAxisX - 2; boardX < *blockAxisX + 3; boardX++)
		{
			if (board[boardY][boardX] < 2)
				board[boardY][boardX] = block.shape[blockY][blockX];

			blockX++;
		}
		blockY++;
		blockX = 0;
	}
}

void moveUp(Block block, int *blockAxisX, int *blockAxisY)
{
	int boardX;
	int boardY;
	int blockX = 0;
	int blockY = 0;

	for (boardY = *blockAxisY - 2; boardY < *blockAxisY + 3; boardY++)
	{
		for (boardX = *blockAxisX - 2; boardX < *blockAxisX + 3; boardX++)
		{
			if (board[boardY][boardX] == BLOCK)
				board[boardY][boardX] = EMPTY;
		}
	}

	*blockAxisY = *blockAxisY - 1;

	for (boardY = *blockAxisY - 2; boardY < *blockAxisY + 3; boardY++)
	{
		for (boardX = *blockAxisX - 2; boardX < *blockAxisX + 3; boardX++)
		{
			if (board[boardY][boardX] < 2)
				board[boardY][boardX] = block.shape[blockY][blockX];

			blockX++;
		}
		blockY++;
		blockX = 0;
	}
}

void mirror(Block *block, int blockAxisX, int blockAxisY)
{
	int boardX;
	int boardY;
	int blockX;
	int blockY;

	for (blockY = 0; blockY < 5; blockY++)
	{
		for (blockX = 0; blockX < 2; blockX++)
		{
			int temp = (*block).shape[blockY][blockX];
			(*block).shape[blockY][blockX] = (*block).shape[blockY][4 - blockX];
			(*block).shape[blockY][4 - blockX] = temp;
		}
	}

	blockX = 0;
	blockY = 0;

	for (boardY = blockAxisY - 2; boardY < blockAxisY + 3; boardY++)
	{
		for (boardX = blockAxisX - 2; boardX < blockAxisX + 3; boardX++)
		{
			if (board[boardY][boardX] <= 2)
				board[boardY][boardX] = (*block).shape[blockY][blockX];

			blockX++;
		}
		blockY++;
		blockX = 0;
	}
}

void flip(Block *block, int blockAxisX, int blockAxisY)
{
	int boardX;
	int boardY;
	int blockX;
	int blockY;

	for (blockY = 0; blockY < 2; blockY++)
	{
		for (blockX = 0; blockX < 5; blockX++)
		{
			int temp = (*block).shape[blockY][blockX];
			(*block).shape[blockY][blockX] = (*block).shape[4 - blockY][blockX];
			(*block).shape[4 - blockY][blockX] = temp;
		}
	}

	blockX = 0;
	blockY = 0;

	for (boardY = blockAxisY - 2; boardY < blockAxisY + 3; boardY++)
	{
		for (boardX = blockAxisX - 2; boardX < blockAxisX + 3; boardX++)
		{
			if (board[boardY][boardX] <= 2)
				board[boardY][boardX] = (*block).shape[blockY][blockX];

			blockX++;
		}
		blockY++;
		blockX = 0;
	}
}

void rotateClockwise(Block *block, int blockAxisX, int blockAxisY)
{
	int boardX;
	int boardY;
	int blockX;
	int blockY;
	int temp[5][5] = { EMPTY };

	for (blockY = 0; blockY < 5; blockY++)
	{
		for (blockX = 0; blockX < 5; blockX++)
			temp[blockY][blockX] = (*block).shape[blockY][blockX];
	}

	for (blockY = 0; blockY < 5; blockY++)
	{
		for (blockX = 0; blockX < 5; blockX++)
			(*block).shape[blockX][4 - blockY] = temp[blockY][blockX];
	}

	blockY = 0;
	blockX = 0;

	for (boardY = blockAxisY - 2; boardY < blockAxisY + 3; boardY++)
	{
		for (boardX = blockAxisX - 2; boardX < blockAxisX + 3; boardX++)
		{
			if (board[boardY][boardX] <= 2)
				board[boardY][boardX] = (*block).shape[blockY][blockX];

			blockX++;
		}
		blockY++;
		blockX = 0;
	}
}

void rotateCounterClockwise(Block *block, int blockAxisX, int blockAxisY)
{
	int boardX;
	int boardY;
	int blockX;
	int blockY;
	int temp[5][5] = { EMPTY };

	for (blockY = 0; blockY < 5; blockY++)
	{
		for (blockX = 0; blockX < 5; blockX++)
			temp[blockY][blockX] = (*block).shape[blockY][blockX];
	}

	for (blockY = 0; blockY < 5; blockY++)
	{
		for (blockX = 0; blockX < 5; blockX++)
			(*block).shape[blockY][blockX] = temp[blockX][4 - blockY];
	}

	blockY = 0;
	blockX = 0;

	for (boardY = blockAxisY - 2; boardY < blockAxisY + 3; boardY++)
	{
		for (boardX = blockAxisX - 2; boardX < blockAxisX + 3; boardX++)
		{
			if (board[boardY][boardX] <= 2)
				board[boardY][boardX] = (*block).shape[blockY][blockX];

			blockX++;
		}
		blockY++;
		blockX = 0;
	}
}

int canConfirm(int status)
{
	if (status == 1)
		return 1;
	else return 0;
}

void confirm(Player *player, int blockIndex, int blockAxisX, int blockAxisY)
{
	int boardX;
	int boardY;

	for (boardY = blockAxisY - 2; boardY < blockAxisY + 3; boardY++)
	{
		for (boardX = blockAxisX - 2; boardX < blockAxisX + 3; boardX++)
		{
			if (board[boardY][boardX] == BLOCK)
				board[boardY][boardX] = (*player).color;
		}
	}

	(*player).blockList[blockIndex].isAvailable = 0;
	(*player).leftoverSpaces -= (*player).blockList[blockIndex].block.space;
}

int main(void)
{
	Player orange, violet;
	Block F, I, L, N, P, T, U, V, W, X, Y, Z, i, j, o, s, t, v, three, two, one;
	int status; //1: valid -1: error
	int blockIndex;
	char xCoordinate;
	char yCoordinate;
	int xCoordinateInt;
	int yCoordinateInt;
	char action;
	int doItAgain = 1; //additional action
	int playAgain = 1; //game

	/* BLOCK AND PLAYER INFO */
	F.space = 5;
	F.shape[1][2] = BLOCK;
	F.shape[1][3] = BLOCK;
	F.shape[2][1] = BLOCK;
	F.shape[2][2] = BLOCK;
	F.shape[3][2] = BLOCK;

	I.space = 5;
	I.shape[0][2] = BLOCK;
	I.shape[1][2] = BLOCK;
	I.shape[2][2] = BLOCK;
	I.shape[3][2] = BLOCK;
	I.shape[4][2] = BLOCK;

	L.space = 5;
	L.shape[0][2] = BLOCK;
	L.shape[1][2] = BLOCK;
	L.shape[2][2] = BLOCK;
	L.shape[3][2] = BLOCK;
	L.shape[3][3] = BLOCK;

	N.space = 5;
	N.shape[1][2] = BLOCK;
	N.shape[2][2] = BLOCK;
	N.shape[3][1] = BLOCK;
	N.shape[3][2] = BLOCK;
	N.shape[4][1] = BLOCK;

	P.space = 5;
	P.shape[2][2] = BLOCK;
	P.shape[2][3] = BLOCK;
	P.shape[3][2] = BLOCK;
	P.shape[3][3] = BLOCK;
	P.shape[4][2] = BLOCK;

	T.space = 5;
	T.shape[2][1] = BLOCK;
	T.shape[2][2] = BLOCK;
	T.shape[2][3] = BLOCK;
	T.shape[3][2] = BLOCK;
	T.shape[4][2] = BLOCK;

	U.space = 5;
	U.shape[1][1] = BLOCK;
	U.shape[1][3] = BLOCK;
	U.shape[2][1] = BLOCK;
	U.shape[2][2] = BLOCK;
	U.shape[2][3] = BLOCK;

	V.space = 5;
	V.shape[0][2] = BLOCK;
	V.shape[1][2] = BLOCK;
	V.shape[2][2] = BLOCK;
	V.shape[2][3] = BLOCK;
	V.shape[2][4] = BLOCK;

	W.space = 5;
	W.shape[1][1] = BLOCK;
	W.shape[2][1] = BLOCK;
	W.shape[2][2] = BLOCK;
	W.shape[3][2] = BLOCK;
	W.shape[3][3] = BLOCK;

	X.space = 5;
	X.shape[1][2] = BLOCK;
	X.shape[2][1] = BLOCK;
	X.shape[2][2] = BLOCK;
	X.shape[2][3] = BLOCK;
	X.shape[3][2] = BLOCK;

	Y.space = 5;
	Y.shape[1][2] = BLOCK;
	Y.shape[2][1] = BLOCK;
	Y.shape[2][2] = BLOCK;
	Y.shape[3][2] = BLOCK;
	Y.shape[4][2] = BLOCK;

	Z.space = 5;
	Z.shape[1][1] = BLOCK;
	Z.shape[2][1] = BLOCK;
	Z.shape[2][2] = BLOCK;
	Z.shape[2][3] = BLOCK;
	Z.shape[3][3] = BLOCK;

	i.space = 4;
	i.shape[1][2] = BLOCK;
	i.shape[2][2] = BLOCK;
	i.shape[3][2] = BLOCK;
	i.shape[4][2] = BLOCK;

	j.space = 4;
	j.shape[0][2] = BLOCK;
	j.shape[1][2] = BLOCK;
	j.shape[2][1] = BLOCK;
	j.shape[2][2] = BLOCK;

	o.space = 4;
	o.shape[1][1] = BLOCK;
	o.shape[1][2] = BLOCK;
	o.shape[2][1] = BLOCK;
	o.shape[2][2] = BLOCK;

	s.space = 4;
	s.shape[1][2] = BLOCK;
	s.shape[1][3] = BLOCK;
	s.shape[2][1] = BLOCK;
	s.shape[2][2] = BLOCK;

	t.space = 4;
	t.shape[1][2] = BLOCK;
	t.shape[2][1] = BLOCK;
	t.shape[2][2] = BLOCK;
	t.shape[2][3] = BLOCK;

	v.space = 4;
	v.shape[1][2] = BLOCK;
	v.shape[2][2] = BLOCK;
	v.shape[2][3] = BLOCK;

	three.space = 3;;
	three.shape[1][2] = BLOCK;
	three.shape[2][2] = BLOCK;
	three.shape[3][2] = BLOCK;

	two.space = 2;
	two.shape[1][2] = BLOCK;
	two.shape[2][2] = BLOCK;

	one.space = 1;
	one.shape[2][2] = BLOCK;

	orange.color = ORANGE;
	violet.color = VIOLET;

	orange.leftoverSpaces = 89;
	violet.leftoverSpaces = 89;

	for (int i = 0; i < 21; i++)
	{
		orange.blockList[i].isAvailable = 1;
		violet.blockList[i].isAvailable = 1;
	}

	orange.blockList[0].block = F;
	orange.blockList[1].block = I;
	orange.blockList[2].block = L;
	orange.blockList[3].block = N;
	orange.blockList[4].block = P;
	orange.blockList[5].block = T;
	orange.blockList[6].block = U;
	orange.blockList[7].block = V;
	orange.blockList[8].block = W;
	orange.blockList[9].block = X;
	orange.blockList[10].block = Y;
	orange.blockList[11].block = Z;
	orange.blockList[12].block = i;
	orange.blockList[13].block = j;
	orange.blockList[14].block = o;
	orange.blockList[15].block = s;
	orange.blockList[16].block = t;
	orange.blockList[17].block = v;
	orange.blockList[18].block = three;
	orange.blockList[19].block = two;
	orange.blockList[20].block = one;

	violet.blockList[0].block = F;
	violet.blockList[1].block = I;
	violet.blockList[2].block = L;
	violet.blockList[3].block = N;
	violet.blockList[4].block = P;
	violet.blockList[5].block = T;
	violet.blockList[6].block = U;
	violet.blockList[7].block = V;
	violet.blockList[8].block = W;
	violet.blockList[9].block = X;
	violet.blockList[10].block = Y;
	violet.blockList[11].block = Z;
	violet.blockList[12].block = i;
	violet.blockList[13].block = j;
	violet.blockList[14].block = o;
	violet.blockList[15].block = s;
	violet.blockList[16].block = t;
	violet.blockList[17].block = v;
	violet.blockList[18].block = three;
	violet.blockList[19].block = two;
	violet.blockList[20].block = one;

	status = 1;

	//Game process
	while (1)
	{
		doItAgain = 1;
		printScr(status);

		//turn=orange
		blockIndex = getBlockIndexInput();
		while (isAlreadyUsed(orange, blockIndex))
		{
			printf("Block already used. Select unused block \n");
			blockIndex = getBlockIndexInput();
		}
		xCoordinate = getXCoordinateInput();
		yCoordinate = getYCoordinateInput();

		xCoordinateInt = getLocation(xCoordinate);
		yCoordinateInt = getLocation(yCoordinate);

		putBlock(orange.blockList[blockIndex - 1].block, xCoordinateInt, yCoordinateInt);
		Sleep(700);

		while (doItAgain)
		{
			if (isInitialMove(orange))
			{
				if (isValidFirstMove(xCoordinateInt, yCoordinateInt))
					status = 1;
				else status = -1;
			}
			else if (isValidMove(orange, xCoordinateInt, yCoordinateInt))
				status = 1;
			else status = -1;

			printScr(status);

			action = getAdditionalAction(status);

			switch (action)
			{
			case 77: //right arrow
				printf("move right");
				moveRight(orange.blockList[blockIndex - 1].block, &xCoordinateInt, &yCoordinateInt);
				break;
			case 75: //left arrow
				printf("move left");
				moveLeft(orange.blockList[blockIndex - 1].block, &xCoordinateInt, &yCoordinateInt);
				break;
			case 80: //down arrow
				printf("move down");
				moveDown(orange.blockList[blockIndex - 1].block, &xCoordinateInt, &yCoordinateInt);
				break;
			case 72: //up arrow
				printf("move up");
				moveUp(orange.blockList[blockIndex - 1].block, &xCoordinateInt, &yCoordinateInt);
				break;
			case 'z':
				printf("mirror");
				mirror(&orange.blockList[blockIndex - 1].block, xCoordinateInt, yCoordinateInt);
				break;
			case 'x':
				printf("flip");
				flip(&orange.blockList[blockIndex - 1].block, xCoordinateInt, yCoordinateInt);
				break;
			case 'c':
				printf("rotate clockwise");
				rotateClockwise(&orange.blockList[blockIndex - 1].block, xCoordinateInt, yCoordinateInt);
				break;
			case 'v':
				printf("rotate counterclockwise");
				rotateCounterClockwise(&orange.blockList[blockIndex - 1].block, xCoordinateInt, yCoordinateInt);
				break;
			case 13: //enter
				printf("confirm current move");
				if (canConfirm(status))
				{
					confirm(&orange, blockIndex, xCoordinateInt, yCoordinateInt);
					doItAgain = 0;
				}
				else printf("\nCurrent move is Invalid. Cannot confirm \n");

				break;
			default:
				printf("\nInvalid action");
				break;
			}
			Sleep(700);
		}

		doItAgain = 1;
		printScr(status);

		//turn=violet
		blockIndex = getBlockIndexInput();
		while (isAlreadyUsed(violet, blockIndex))
		{
			printf("Block already used. Select unused block \n");
			blockIndex = getBlockIndexInput();
		}
		xCoordinate = getXCoordinateInput();
		yCoordinate = getYCoordinateInput();

		xCoordinateInt = getLocation(xCoordinate);
		yCoordinateInt = getLocation(yCoordinate);

		putBlock(violet.blockList[blockIndex - 1].block, xCoordinateInt, yCoordinateInt);
		Sleep(700);

		while (doItAgain)
		{
			if (isInitialMove(violet))
			{
				if (isValidFirstMove(xCoordinateInt, yCoordinateInt))
					status = 1;
				else status = -1;
			}
			else if (isValidMove(violet, xCoordinateInt, yCoordinateInt))
				status = 1;
			else status = -1;

			printScr(status);

			action = getAdditionalAction(status);

			switch (action)
			{
			case 77: //right arrow
				printf("move right");
				moveRight(violet.blockList[blockIndex - 1].block, &xCoordinateInt, &yCoordinateInt);
				break;
			case 75: //left arrow
				printf("move left");
				moveLeft(violet.blockList[blockIndex - 1].block, &xCoordinateInt, &yCoordinateInt);
				break;
			case 80: //down arrow
				printf("move down");
				moveDown(violet.blockList[blockIndex - 1].block, &xCoordinateInt, &yCoordinateInt);
				break;
			case 72: //up arrow
				printf("move up");
				moveUp(violet.blockList[blockIndex - 1].block, &xCoordinateInt, &yCoordinateInt);
				break;
			case 'z':
				printf("mirror");
				mirror(&violet.blockList[blockIndex - 1].block, xCoordinateInt, yCoordinateInt);
				break;
			case 'x':
				printf("flip");
				flip(&violet.blockList[blockIndex - 1].block, xCoordinateInt, yCoordinateInt);
				break;
			case 'c':
				printf("rotate clockwise");
				rotateClockwise(&violet.blockList[blockIndex - 1].block, xCoordinateInt, yCoordinateInt);
				break;
			case 'v':
				printf("rotate counterclockwise");
				rotateCounterClockwise(&violet.blockList[blockIndex - 1].block, xCoordinateInt, yCoordinateInt);
				break;
			case 13: //enter
				printf("confirm current move");
				if (canConfirm(status))
				{
					confirm(&violet, blockIndex, xCoordinateInt, yCoordinateInt);
					doItAgain = 0;
				}
				else printf("\nCurrent move is Invalid. Cannot confirm \n");
				break;
			default:
				printf("\nInvalid action");
				break;
			}
			Sleep(700);
		}
	}

	return 0;
}