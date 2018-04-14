#include <stdio.h>
#include <stdlib.h>

void displayBoard();
int verifySelection(int, int);
void checkForWin();

char board[8], 
	 cWhoWon = ' ';
int iCurrentPlayer = 0;

int main()
{
    int x,
		iSquareNum = 0;

	for(x = 0; x < 9; x++)
		board[x] = ' ';

	displayBoard();

	while(cWhoWon == ' ')
	{
		printf("\n%c\n", cWhoWon);

		if(iCurrentPlayer == 1 || iCurrentPlayer == 0)
		{
			printf("\nPLAYER X\n");
			printf("Enter an available square number (1-9): ");
			scanf("%d", &iSquareNum);

			if(verifySelection(iSquareNum, iCurrentPlayer) == 1)
				iCurrentPlayer = 1;
			else
				iCurrentPlayer = 2;
		}
		else
		{
			printf("\nPLAYER O\n");
			printf("Enter an available square number (1-9): ");
			scanf("%d", &iSquareNum);

			if(verifySelection(iSquareNum, iCurrentPlayer) == 1)
				iCurrentPlayer = 2;
			else
				iCurrentPlayer = 1;			
		}

		displayBoard();
		checkForWin();
	}

    return 0;
}

void displayBoard()
{
	system("clear");
	printf("\n\t\t\n");
	printf("\t|\t|\n");
	printf("    %c   |   %c   |   %c\n", board[0], board[1], board[2]);
	printf("--------|-------|--------\n");
	printf("\t|\t|\n");
	printf("    %c   |   %c   |   %c\n", board[3], board[4], board[5]);
	printf("--------|-------|--------\n");
	printf("\t|\t|\n");
	printf("    %c   |   %c   |   %c\n", board[6], board[7], board[8]);
	printf("\t|\t|\n");
}

int verifySelection(int iSquare, int iPlayer)
{
	if(board[iSquare - 1] == ' ' && (iPlayer == 1 || iPlayer == 0))
	{
		board[iSquare - 1] = 'X';
		return(0);
	}
	else if(board[iSquare - 1] == ' ' && iPlayer == 2)
	{
		board[iSquare - 1] = 'O';
		return(0);
	}
	else
		return(1);
}

void checkForWin()
{
	int catTotal,
		x;

	if(board[0] == 'X' && board[1] == 'X' && board[2] == 'X')
		cWhoWon = 'X';
	else if(board[3] == 'X' && board[4] == 'X' && board[5] == 'X')
		cWhoWon = 'X';
	else if(board[6] == 'X' && board[7] == 'X' && board[8] == 'X')
		cWhoWon = 'X';
	else if(board[0] == 'X' && board[3] == 'X' && board[6] == 'X')
		cWhoWon = 'X';
	else if(board[1] == 'X' && board[4] == 'X' && board[7] == 'X')
		cWhoWon = 'X';
	else if(board[2] == 'X' && board[5] == 'X' && board[8] == 'X')
		cWhoWon = 'X';
	else if(board[0] == 'X' && board[4] == 'X' && board[8] == 'X')
		cWhoWon = 'X';
	else if(board[2] == 'X' && board[4] == 'X' && board[6] == 'X')
		cWhoWon = 'X';
	else if(board[0] == 'O' && board[1] == 'O' && board[2] == 'O')
		cWhoWon = 'O';
	else if(board[3] == 'O' && board[4] == 'O' && board[5] == 'O')
		cWhoWon = 'O';
	else if(board[6] == 'O' && board[7] == 'O' && board[8] == 'O')
		cWhoWon = 'O';
	else if(board[0] == 'O' && board[3] == 'O' && board[6] == 'O')
		cWhoWon = 'O';
	else if(board[1] == 'O' && board[4] == 'O' && board[7] == 'O')
		cWhoWon = 'O';
	else if(board[2] == 'O' && board[5] == 'O' && board[8] == 'O')
		cWhoWon = 'O';
	else if(board[0] == 'O' && board[4] == 'O' && board[8] == 'O')
		cWhoWon = 'O';
	else if(board[2] == 'O' && board[4] == 'O' && board[6] == 'O')
		cWhoWon = 'O';

	if(cWhoWon == 'X')
	{
		puts("X Wins");
		return;
	}

	if(cWhoWon == 'O')
	{
		puts("O Wins");
		return;
	}

	// check fo CAT / draw game
	for(x = 0; x < 9; x++)
	{
		if(board[x] != ' ')
			catTotal += 1;
	}

	if(catTotal == 9)
	{
		cWhoWon = 'C';
		puts("CAT Game!");
		return;
	}
}
