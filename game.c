#include "game.h"

int selectMode()
{
	int userSelectedMode;
	printf("1. Play game 2. Replay last played game \n");
	printf("Enter mode. Enter anything else to exit: ");
	scanf("%d", &userSelectedMode);

	return userSelectedMode;
}

void setLeftSpacesZero(int(*board)[5])
{
	int i, j;
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 5; j++)
		{
			if (board[i][j] != BLOCK)
				board[i][j] = 0;
		}
	}
}

void clearBoard()
{
	int boardX, boardY;
	for (boardX = 0; boardX < 24; boardX++)
	{
		for (boardY = 0; boardY < 24; boardY++)
			board[boardY][boardX] = EMPTY;
	}
}

void initGame(Player *orange, Player *violet)
{
	int i;

	clearBoard();
	status = 1;
	move = 0;
	turn = ORANGE;

	(*orange).isOver = 0;
	(*violet).isOver = 0;
	(*orange).leftoverSpaces = 89;
	(*violet).leftoverSpaces = 89;

	for (i = 0; i < 21; i++)
	{
		(*orange).blockList[i].isAvailable = 1;
		(*violet).blockList[i].isAvailable = 1;
	}
}

void printScr(Player orange, Player violet)
{
	int i, j;

	Sleep(700);
	system("cls");
	printf("===BLOCK INDEX INFO=== \n");
	printf("1:F 2:I 3:L 4:N 5:P 6:T 7:U \n");
	printf("8:V 9:W 10:X 11:Y 12:Z 13:i 14:j \n");
	printf("15:o 16:s 17:t 18:v 19:three 20:two 21:one \n\n");

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
				printf("◼︎");
				break;
			case ORANGE:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				printf("◼︎");
				break;
			case VIOLET:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
				printf("◼︎");
				break;
			default:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				//start point
				if ((i + 5 == 9 && j + 5 == 9) || (i + 5 == 14 && j + 5 == 14))
					printf("★");
				else printf("☐");
				break;
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}

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
		printf("\n");
	}
	printf("    1 2 3 4 5 6 7 8 9 A B C D E \n");

	printf("Moves: %d    ", move);
	printf("       Turn: ");
	if (move % 2 == 0)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		printf("ORANGE \n");
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
		printf("VIOLET \n");
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); //set color to orange
	printf("ORANGE: ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //set color to white
	printf("%d spaces left \n", orange.leftoverSpaces);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5); //set color to violet
	printf("VIOLET: ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //set color to white
	printf("%d spaces left \n\n", violet.leftoverSpaces);
}

int determineWinner(int orangeLeftover, int violetLeftover)
{
	if (orangeLeftover < violetLeftover)
		return ORANGE;
	else return VIOLET;
}

int askPlayAgain()
{
	int userPlayAgainInput;
	printf("Want to play again? Enter 1 if yes, anything else if no: ");
	scanf("%d", &userPlayAgainInput);
	return userPlayAgainInput;
}

int endGame(Player orange, Player violet)
{
	printScr(orange, violet);
	if (determineWinner(orange.leftoverSpaces, violet.leftoverSpaces))
		printf("Orange win! \n");
	else printf("Violet win! \n");

	return askPlayAgain();
}
