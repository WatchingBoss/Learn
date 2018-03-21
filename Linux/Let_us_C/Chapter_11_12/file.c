#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
first()
{
	FILE *fp, *f;
	char ch;
	int a, b = 0;

	fp = fopen("file.txt", "r");
	f = fopen("new.txt", "w");

	while(1)
	{
		ch = fgetc(fp);
 
		if (ch == EOF)
			break;
		for(a = 0; a < b; a++)
		{
			fprintf(f, " ");
		}
		fprintf(f, "%c\n", ch);
		b++;
	}

	fclose(fp);
	fclose(f);
}

// Count chars, spaces, tabs and newlines in a file
void
second(char *name)
{
	FILE *fp;
	char ch;
	int nol = 0, not = 0, nob = 0, noc = 0;

	fp = fopen(name, "r");

	while(1)
	{
		ch = fgetc(fp);

		if(ch == EOF)
			break;

		noc++;

		if(ch == ' ')
			nob++;
		if(ch == '\n')
			nol++;
		if(ch =='\t')
			not++;
	}

	fclose(fp);
	printf("\nNumber of characters = %d\n", noc);
	printf("Number of blank = %d\n", nob);
	printf("Number of tabs = %d\n", not);
	printf("Number of lines = %d\n", nol);
	printf("Number of characters without spaces = %d\n", noc - nob);
}

//Copy text
void
third()
{
	FILE *fs, *ft;
	char ch;

	fs = fopen("file.txt", "r");
	if(fs == NULL)
	{
		puts("Cannot open source file");
		exit(0);
	}

	ft = fopen("copy.txt", "w");
	if(ft == NULL)
	{
		puts("Cannot open target file");
		fclose(fs);
		exit(0);
	}

	while(1)
	{
		ch = fgetc(fs);

		if(ch == EOF)
			break;

		else
			fputc(ch, ft);
	}

	fclose(fs);
	fclose(ft);
}

// Receives strings from keyboard and writes them to file
void
fourth()
{
	FILE *fp;
	char s[80];

	fp = fopen("new1.txt", "w");
	if(fp == NULL)
	{
		puts("Cannot open file");
		exit(0);
	}

	printf("Enter a few lines of text\n");
	while(strlen(fgets(s, sizeof(s), stdin)) > 1)
	{
		fputs(s, fp);
	}

	fclose(fp);
}

// Reads strings from the file and displays them on screen
void
fifth()
{
	FILE *fp;
	char s[80];

	fp = fopen("new1.txt", "r");
	if(fp == NULL)
	{
		puts("Cannot opne file");
		exit(0);
	}

	while(fgets(s, 79, fp) != NULL)
		printf("%s", s);

	fclose(fp);
}


int main()
{

    return 0;
}
