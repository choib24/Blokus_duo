#include "game.h"
#include "player.h"
#include "check.h"
#include "block.h"
#include "file.h"

int main(void)
{
	Player orange, violet;
	Player *isPlaying;
	Block F, I, L, N, P, T, U, V, W, X, Y, Z, i, j, o, s, t, v, three, two, one;
	int mode;
	int blockIndex;
	char xCoordinate;
	char yCoordinate;
	int xCoordinateInt;
	int yCoordinateInt;
	char action;
	int keepGetAction = 1; //additional action
	int playAgain = 1; //game

	/* BLOCK AND PLAYER INFO */
	F.space = 5;
	F.shape[1][2] = BLOCK;
	F.shape[1][3] = BLOCK;
	F.shape[2][1] = BLOCK;
	F.shape[2][2] = BLOCK;
	F.shape[3][2] = BLOCK;
	setLeftSpacesZero(F.shape);

	I.space = 5;
	I.shape[0][2] = BLOCK;
	I.shape[1][2] = BLOCK;
	I.shape[2][2] = BLOCK;
	I.shape[3][2] = BLOCK;
	I.shape[4][2] = BLOCK;
	setLeftSpacesZero(I.shape);

	L.space = 5;
	L.shape[0][2] = BLOCK;
	L.shape[1][2] = BLOCK;
	L.shape[2][2] = BLOCK;
	L.shape[3][2] = BLOCK;
	L.shape[3][3] = BLOCK;
	setLeftSpacesZero(L.shape);

	N.space = 5;
	N.shape[1][2] = BLOCK;
	N.shape[2][2] = BLOCK;
	N.shape[3][1] = BLOCK;
	N.shape[3][2] = BLOCK;
	N.shape[4][1] = BLOCK;
	setLeftSpacesZero(N.shape);

	P.space = 5;
	P.shape[2][2] = BLOCK;
	P.shape[2][3] = BLOCK;
	P.shape[3][2] = BLOCK;
	P.shape[3][3] = BLOCK;
	P.shape[4][2] = BLOCK;
	setLeftSpacesZero(P.shape);

	T.space = 5;
	T.shape[2][1] = BLOCK;
	T.shape[2][2] = BLOCK;
	T.shape[2][3] = BLOCK;
	T.shape[3][2] = BLOCK;
	T.shape[4][2] = BLOCK;
	setLeftSpacesZero(T.shape);

	U.space = 5;
	U.shape[1][1] = BLOCK;
	U.shape[1][3] = BLOCK;
	U.shape[2][1] = BLOCK;
	U.shape[2][2] = BLOCK;
	U.shape[2][3] = BLOCK;
	setLeftSpacesZero(U.shape);

	V.space = 5;
	V.shape[0][2] = BLOCK;
	V.shape[1][2] = BLOCK;
	V.shape[2][2] = BLOCK;
	V.shape[2][3] = BLOCK;
	V.shape[2][4] = BLOCK;
	setLeftSpacesZero(V.shape);

	W.space = 5;
	W.shape[1][1] = BLOCK;
	W.shape[2][1] = BLOCK;
	W.shape[2][2] = BLOCK;
	W.shape[3][2] = BLOCK;
	W.shape[3][3] = BLOCK;
	setLeftSpacesZero(W.shape);

	X.space = 5;
	X.shape[1][2] = BLOCK;
	X.shape[2][1] = BLOCK;
	X.shape[2][2] = BLOCK;
	X.shape[2][3] = BLOCK;
	X.shape[3][2] = BLOCK;
	setLeftSpacesZero(X.shape);

	Y.space = 5;
	Y.shape[1][2] = BLOCK;
	Y.shape[2][1] = BLOCK;
	Y.shape[2][2] = BLOCK;
	Y.shape[3][2] = BLOCK;
	Y.shape[4][2] = BLOCK;
	setLeftSpacesZero(Y.shape);

	Z.space = 5;
	Z.shape[1][1] = BLOCK;
	Z.shape[2][1] = BLOCK;
	Z.shape[2][2] = BLOCK;
	Z.shape[2][3] = BLOCK;
	Z.shape[3][3] = BLOCK;
	setLeftSpacesZero(Z.shape);

	i.space = 4;
	i.shape[1][2] = BLOCK;
	i.shape[2][2] = BLOCK;
	i.shape[3][2] = BLOCK;
	i.shape[4][2] = BLOCK;
	setLeftSpacesZero(i.shape);

	j.space = 4;
	j.shape[0][2] = BLOCK;
	j.shape[1][2] = BLOCK;
	j.shape[2][1] = BLOCK;
	j.shape[2][2] = BLOCK;
	setLeftSpacesZero(j.shape);

	o.space = 4;
	o.shape[1][1] = BLOCK;
	o.shape[1][2] = BLOCK;
	o.shape[2][1] = BLOCK;
	o.shape[2][2] = BLOCK;
	setLeftSpacesZero(o.shape);

	s.space = 4;
	s.shape[1][2] = BLOCK;
	s.shape[1][3] = BLOCK;
	s.shape[2][1] = BLOCK;
	s.shape[2][2] = BLOCK;
	setLeftSpacesZero(s.shape);

	t.space = 4;
	t.shape[1][2] = BLOCK;
	t.shape[2][1] = BLOCK;
	t.shape[2][2] = BLOCK;
	t.shape[2][3] = BLOCK;
	setLeftSpacesZero(t.shape);

	v.space = 3;
	v.shape[1][2] = BLOCK;
	v.shape[2][2] = BLOCK;
	v.shape[2][3] = BLOCK;
	setLeftSpacesZero(v.shape);

	three.space = 3;;
	three.shape[1][2] = BLOCK;
	three.shape[2][2] = BLOCK;
	three.shape[3][2] = BLOCK;
	setLeftSpacesZero(three.shape);

	two.space = 2;
	two.shape[1][2] = BLOCK;
	two.shape[2][2] = BLOCK;
	setLeftSpacesZero(two.shape);

	one.space = 1;
	one.shape[2][2] = BLOCK;
	setLeftSpacesZero(one.shape);

	orange.color = ORANGE;
	violet.color = VIOLET;

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

	while (1)
	{
		mode = selectMode();

		if (mode == 1) //game playing mode
		{
			while (1)
			{
				initGame(&orange, &violet);
				createReplayFile(fp);

				//game-playing phase
				while (1)
				{
					if (orange.isOver == 1 && violet.isOver == 1)
						break;

					if (turn == ORANGE)
						isPlaying = &orange;
					else isPlaying = &violet;
					
					keepGetAction = 1;

					printScr(orange, violet);

					blockIndex = getBlockIndexInput();
					if (blockIndex == 0)
					{
						printf("Player cannot place block. Turn skipped \n");
						(*isPlaying).isOver = 1;
						move++;
						turn *= -1; //orange->violet violet->orange					
						continue;
					}
					while (isAlreadyUsed(*isPlaying, blockIndex - 1))
					{
						printf("Block already used. Select unused block \n");
						blockIndex = getBlockIndexInput();
					}
					xCoordinate = getXCoordinateInput();
					yCoordinate = getYCoordinateInput();
					xCoordinateInt = getLocation(xCoordinate);
					yCoordinateInt = getLocation(yCoordinate);

					putBlock(isPlaying->blockList[blockIndex - 1].block, xCoordinateInt, yCoordinateInt);

					while (keepGetAction)
					{
						if (!isPlaceable(isPlaying->blockList[blockIndex - 1].block, xCoordinateInt, yCoordinateInt))
							status = -1;
						else if (isInitialMove(*isPlaying))
						{
							if (isValidFirstMove(xCoordinateInt, yCoordinateInt))
								status = 1;
							else status = -1;
						}
						else if (isValidMove(*isPlaying, xCoordinateInt, yCoordinateInt))
							status = 1;
						else status = -1;

						printScr(orange, violet);

						action = getAdditionalAction(status);
						switch (action)
						{
						case 77: //right arrow
							printf("move right");
							moveRight((*isPlaying).blockList[blockIndex - 1].block, &xCoordinateInt, &yCoordinateInt);
							break;
						case 75: //left arrow
							printf("move left");
							moveLeft((*isPlaying).blockList[blockIndex - 1].block, &xCoordinateInt, &yCoordinateInt);
							break;
						case 80: //down arrow
							printf("move down");
							moveDown((*isPlaying).blockList[blockIndex - 1].block, &xCoordinateInt, &yCoordinateInt);
							break;
						case 72: //up arrow
							printf("move up");
							moveUp((*isPlaying).blockList[blockIndex - 1].block, &xCoordinateInt, &yCoordinateInt);
							break;
						case 'z':
							printf("mirror");
							mirror(&(*isPlaying).blockList[blockIndex - 1].block, xCoordinateInt, yCoordinateInt);
							break;
						case 'x':
							printf("flip");
							flip(&(*isPlaying).blockList[blockIndex - 1].block, xCoordinateInt, yCoordinateInt);
							break;
						case 'c':
							printf("rotate clockwise");
							rotateClockwise(&(*isPlaying).blockList[blockIndex - 1].block, xCoordinateInt, yCoordinateInt);
							break;
						case 'v':
							printf("rotate counterclockwise");
							rotateCounterClockwise(&(*isPlaying).blockList[blockIndex - 1].block, xCoordinateInt, yCoordinateInt);
							break;
						case 13: //enter
							printf("confirm current move");
							if (canConfirm(status))
							{
								confirm(isPlaying, blockIndex - 1, xCoordinateInt, yCoordinateInt);
								keepGetAction = 0;
							}
							else printf("\nCurrent move is Invalid. Cannot confirm \n");
							break;
						default:
							printf("\nInvalid action");
							break;
						}
					}

					updateReplayFile(fp);
					turn *= -1;
				}

				//end of game
				if (endGame(orange, violet) != 1)
				{
					system("cls"); //temporary
					break;
				}
			}
		}
		else if (mode == 2) //replay mode
		{
			printFromFile(fp);
		}
		else break;
	}

	return 0;
}
