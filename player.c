#include "player.h"

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

char getAdditionalAction()
{
	char userAction;

	if (status == -1)
		printf("Current move is invalid \n\n");
	else printf("Current move is valid \n\n");

	printf("→:move right  ←:move left  ↑:move up  ↓:move down \n");
	printf("z:mirror  x:flip  c:rotate clockwise  v:rotate counterclockwise \n\n");
	printf("Choose your action. Press Enter to confirm your current move: ");
	userAction = getch();
	if (userAction == -32 || userAction == 0 || userAction == 0xE0) //for arrow keys
		userAction = getch();

	return userAction;
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
