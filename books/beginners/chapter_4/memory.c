#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

void
memory()
{
	char cYesNo = '\0';
	int iResp1 = 0,
		iResp2 = 0,
		iResp3 = 0;
	int iElaspedTime = 0,
		iCurrentTime = 0;
	int iRandomNum = 0;
	int i1 = 0,
		i2 = 0,
		i3 = 0,
		iCounter = 0;

	WINDOW *w;

	srand(time(NULL));

	printf("Play a game of Concentration? (y or n): ");
	cYesNo = getchar();

	if(cYesNo == 'y' || cYesNo == 'Y')
	{
		i1 = rand() % 100;
		i2 = rand() % 100;
		i3 = rand() % 100;

		puts("Concentrate on the next three numbers");
		printf("%d\t%d\t%d\n", i1, i2, i3);

		iCurrentTime = time(NULL);

		do
		{
			iElaspedTime = time(NULL);
		} while((iElaspedTime - iCurrentTime) < 3);

		system("clear");

		printf("Enter each # separated with one space: ");
		scanf("%d %d %d", &iResp1, &iResp2, &iResp3);

		if(i1 == iResp1 && i2 == iResp2 && i3 == iResp3)
			puts("Congratulations!");
		else
			printf("Sorry, correct numbers were %d %d %d", i1, i2, i3);
	}
}

int main()
{
    memory(); 

    return 0;
}
