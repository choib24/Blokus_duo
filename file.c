#include "file.h"

void writeReplayFile(FILE *fp)
{
	int boardY, boardX;
	fp = fopen("gameReplay.txt", "w");

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