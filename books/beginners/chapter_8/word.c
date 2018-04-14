#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void checkAnswer(char *, char[]);

int main()
{
    char *strGame[5] = {"ADELANGUAGEFERVZOPIBMOU",
						"ZBPOINTERSKLMLOOPMNOCOT",
						"PODSTRINGGDIWHIEEICERLS",
						"YVCPROGRAMMERWQKNULTHMD",
						"UKUNIXFIMWXIZEQZINPUTEX"};
	char answer[80] = {0};

	int displayed = 0,
		x,
		startTime =0;

	system("clear");
	printf("\n\n\tWord Find\n\n");

	startTime = time(NULL);

	for(x = 0; x < 2; x++)
	{
		while(startTime + 3 > time(NULL))
		{
			if(displayed == 0)
			{
				printf("\nFind a word in: \n\n");
				printf("%s\n\n", strGame[x]);
				displayed = 1;
			}
		}
	
		system("clear");
		printf("\nEnter word found: ");
		gets(answer);

		checkAnswer(strGame[x], answer);

		displayed = 0;
		startTime = time(NULL);
	}
	
    return 0;
}

void checkAnswer(char *string1, char string2[])
{
	int x;

	for(x = 0; x <= strlen(string2); x++)
		string2[x] = toupper(string2[x]);

	if(strstr(string1, string2) != 0 && string2[0] != 0)
		puts("Great job!");
	else
		puts("Sorry, word not found!");
}
