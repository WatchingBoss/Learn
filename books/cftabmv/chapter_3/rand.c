#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void
first()
{
	int iRandom = 0;

	iRandom = rand() % 10 + 1;

	printf("This is random number without srand(): %d\n", iRandom);
}

void
second()
{
	int iRandom = 0;

	srand(time(NULL));

	iRandom = rand() % 10 + 1;

	printf("This is random number with srand(): %d\n", iRandom);
}

void
fortun()
{
	int iRandomNum = 0;
	srand(time(NULL));

	iRandomNum = (rand() % 4) + 1;

	puts("Fortune Cookie - Chapter 3");

	switch(iRandomNum)
	{
		case 1:
			puts("You wiil meet a new friend today");
			break;
		case 2:
			puts("You will enjoy a long and happy life");
			break;
		case 3:
			puts("Opportunity knocks softly. Can you hear it?");
			break;
		case 4:
			puts("You will be financially rewarded for your good deeds");
			break;
		default:
			break;
 	}

	printf("\nLuchy lotto numbers: ");
	for(int i = 0; i < 6; i++)
		printf("%d ", (rand() % 49) + 1);
	printf("\n");
}


int main()
{
 	fortun();
    return 0;
}
