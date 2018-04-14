#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef enum {false, true} bool;

typedef struct deck
{
	char type[10];
	int value;
	bool used;
} aDeck;

void shuffle(aDeck *);

int
main()
{
	int x, y;
	aDeck myDeck[52];

	srand(time(NULL));

	for(x = 0; x <= 3; x++)
	{
		for(y = 0; y < 13; y++)
		{
			switch(x)
			{
				case 0:
				{
					strcpy(myDeck[y].type, "diamonds");
					myDeck[y].value = y;
					myDeck[y].used = false;
				} break;
				case 1:
				{
					strcpy(myDeck[y + 13].type, "clubs");
					myDeck[y + 13].value = y;
					myDeck[y + 13].used = false;					
				} break;
				case 2:
				{
					strcpy(myDeck[y + 26].type, "hearts");
					myDeck[y + 26].value = y;
					myDeck[y + 26].used = false;
				} break;
				case 3:
				{
					strcpy(myDeck[y + 39].type, "spades");
					myDeck[y + 39].value = y;
					myDeck[y + 39].used = false;					
				} break;
				default:
					break;
			}
		}
		
	}

	shuffle(myDeck);

	return(0);
}

void shuffle(aDeck *thisDeck)
{
	int x, iRand, found = 0;

	system("clear");
	printf("\nYour five cards are: \n\n");

	while(found < 5)
	{
		iRand = rand() % 51;

		if(thisDeck[iRand].used == false)
		{
			switch(thisDeck[iRand].value)
			{
				case 12:
					printf("Ace of %s\n", thisDeck[iRand].type);
					break;
				case 11:
					printf("King of %s\n", thisDeck[iRand].type);
					break;
				case 10:
					printf("Queen of %s\n", thisDeck[iRand].type);
					break;
				case 9:
					printf("Jack of %s\n", thisDeck[iRand].type);
					break;
				default:
				{
					printf("%d of ", thisDeck[iRand].value + 2);
					printf("%s\n", thisDeck[iRand].type);
				} break;
			}

			thisDeck[iRand].used = true;
			found++;
		}
	}
}
