#include "game.h"

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
	if (blockIndex >= 0 && blockIndex <= 21)
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
	printf("Enter block index. Enter 0 to skip your turn: ");
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

	printf("กๆ:move right  ก็:move left  ก่:move up  ก้:move down \n");
	printf("z:mirror  x:flip  c:rotate clockwise  v:rotate counterclockwise \n\n");
	printf("Choose your action. Press Enter to confirm your current move: ");
	userAction = getch();
	if (userAction == -32 || userAction == 0 || userAction == 0xE0) //for arrow keys
		userAction = getch();

	return userAction;
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
	move++;
}