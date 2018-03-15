#include <stdio.h>

void
first()
{
	char name[] = "Anastasia";
	int i = 0;

	while(i <= 9)
	{
		printf("%c", name[i]);
		++i;
	}
	printf("\n");

	i = 0;
	while(name[i] != '\0')
	{
		printf("%c", name[i]);
		++i;
	}
	printf("\n");
}

void
second()
{
	char name[] = "Anastasia";
	char *ptr;

	ptr = name; // store base address of string

	while(*ptr != '\0')
	{
		printf("%c", *ptr);
		++ptr;
	}
	printf("\n");
}

void
third()
{
	char name[] = "Anastasia";
	printf("%s\n", name);

	char name1[25];

	printf("Enter your name\n");
	scanf("%s", name1);
	printf("Hello, %s\n", name1);

	char nameFull[30];
	puts("Enter your full name");
	getc(stdin);
	scanf("%[^\n]s", nameFull);

	printf("Hello, %s\n", nameFull);
}

void
fourth()
{
	char *st = "ELephone";
	int i = 0;
	while(i < 8)
	{
		printf("%c", *(st + i));
		++i;
	}
	puts("");
}	

int main()
{
    return 0;
}




