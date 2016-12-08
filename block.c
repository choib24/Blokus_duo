#include "block.h"

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
				if (board[boardY][boardX] == EMPTY)
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
			if (board[boardY][boardX] == EMPTY)
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
			if (board[boardY][boardX] == EMPTY)
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
			if (board[boardY][boardX] == EMPTY)
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
			if (board[boardY][boardX] != ORANGE && board[boardY][boardX] != VIOLET)
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
			if (board[boardY][boardX] != ORANGE && board[boardY][boardX] != VIOLET)
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
			if (board[boardY][boardX] != ORANGE && board[boardY][boardX] != VIOLET)
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
			if (board[boardY][boardX] != ORANGE && board[boardY][boardX] != VIOLET)
				board[boardY][boardX] = (*block).shape[blockY][blockX];

			blockX++;
		}
		blockY++;
		blockX = 0;
	}
}