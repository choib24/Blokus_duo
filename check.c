#include "check.h"

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

int isValidCoordinate(char coordinate)
{
	if ((coordinate >= '1' && coordinate <= '9') || (coordinate >= 'A' && coordinate <= 'E') ||
	    (coordinate >= 'a' && coordinate <= 'e'))
		return 1;
	else return 0;
}

int isInitialMove(Player player)
{
	if (player.leftoverSpaces == 89)
		return 1;
	else return 0;
}

int findNearestStartingPoint(int blockAxisX, int blockAxisY)
{
	double distance1Exp = pow((blockAxisX - 9), 2) + pow((blockAxisY - 9), 2);
	double distance2Exp = pow((blockAxisX - 14), 2) + pow((blockAxisY - 14), 2);

	if (distance1Exp < distance2Exp)
		return 9;
	else return 14;
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
				if (board[i][j] == BLOCK)
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

	if (board[yCor - 1][xCor] != BLOCK || board[yCor + 1][xCor] != BLOCK)
		isVerticallyOpen = 1;

	if (board[yCor][xCor - 1] != BLOCK || board[yCor][xCor + 1] != BLOCK)
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

int canConfirm()
{
	if (status == 1)
		return 1;
	else return 0;
}
