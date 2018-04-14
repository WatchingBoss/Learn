#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void encrypt(char [], int);
void decrypt(char [], int);

int 
main()
{
	char myString[21] = {0};
	int iSelection = 0,
		iRand;

	srand(time(NULL));

	iRand = (rand() % 4) + 1;

	while(iSelection != 4)
	{
		printf("\n\n1\tEncrypt Clear Text\n");
		printf("2\tDecrypt Cipher Text\n");
		printf("3\tGenerate New Key\n");
		printf("4\tQuit\n");
		printf("Select a Cryptography Option: ");
		scanf("%d", &iSelection);

		switch(iSelection)
		{
			case 1:
			{
				printf("Enter one word as clear text to encrypt: ");
				scanf("%s", myString);
				encrypt(myString, iRand);
			} break;
			case 2:
			{
				printf("Enter cipher text to decrypt: ");
				scanf("%s", myString);
				decrypt(myString, iRand);
			} break;
			case 3:
			{
				iRand = (rand() % 4) + 1;
				puts("New Key Generated");
			} break;
			default:
				break;
		}
	}

	return(0);
}

void encrypt(char sMessage[], int random)
{
	int x = 0;
	
	while(sMessage[x])
	{
		sMessage[x] += random;
		x++;
	}

	x = 0;
	
	printf("\nEntered Message is: ");
	while(sMessage[x])
	{
		printf("%c", sMessage[x]);
		x++;
	}
}


void decrypt(char sMessage[], int random)
{
	int x = 0;
	
	while(sMessage[x])
	{
		sMessage[x] -= random;
		x++;
	}

	x = 0;
	
	printf("\nEntered Message is: ");
	while(sMessage[x])
	{
		printf("%c", sMessage[x]);
		x++;
	}
}
