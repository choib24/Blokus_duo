#include "file.h"

void createReplayFile(FILE *fp)
{
	fp = fopen("gameReplay.txt", "w");
	fclose(fp);
}

void updateReplayFile(FILE *fp)
{
	int boardY, boardX;
	fp = fopen("gameReplay.txt", "a");

	for (boardY = 0; boardY < BOARD_SIZE; boardY++)
	{
		for (boardX = 0; boardX < BOARD_SIZE; boardX++)
		{
			fprintf(fp, "%d ", board[boardY + 5][boardX + 5]);
		}
		fprintf(fp, "\n");
	}
	fprintf(fp, "\n");
	fclose(fp);
}

void printFromFile(FILE *fp)
{
	int i, j;
	int value;
	long fileSize;

	fp = fopen("gameReplay.txt", "r");

	fseek(fp, 0, SEEK_END);
	fileSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	while (!feof(fp))
	{
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
				fscanf(fp, "%d", &value);
				switch (value)
				{
				case BLOCK:
					if (status == -1) //Invalid move
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
					else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					printf("бс");
					break;
				case ORANGE:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
					printf("бс");
					break;
				case VIOLET:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
					printf("бс");
					break;
				default:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					//start point
					if ((i + 5 == 9 && j + 5 == 9) || (i + 5 == 14 && j + 5 == 14))
						printf("б┌");
					else printf("бр");
					break;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				}
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
		printf("    1 2 3 4 5 6 7 8 9 A B C D E \n\n");

		if (ftell(fp) == fileSize - 5)
			break;

		Sleep(1000);
	}

	fclose(fp);
}