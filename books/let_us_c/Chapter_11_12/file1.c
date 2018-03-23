#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void
first()
{
	FILE *fp;
	char another = 'Y';
	struct emp
	{
		char name[40];
		int age;
		float bs;
	};
	struct emp e;
 
	fp = fopen("emp.dat", "w");

	if(fp == NULL)
	{
		puts("Cannot open file");
		exit(0);
	}
  
	while(another == 'Y')
	{
		printf("Enter name, age and basic salary  ");
		scanf("%s %d %f", e.name, &e.age, &e.bs);
		fprintf(fp, "%-10s %-3d %-6.2f\n", e.name, e.age, e.bs);

		printf("Add another record (Y/N)  ");
//		getc(stdin);
		while(getchar() != '\n');
		another = getchar();
	}

	fclose(fp);
}

void
second()
{
	FILE *fp;
	struct emp
	{
		char name[40];
		int age;
		float bs;
	};
	struct emp e;
 
	fp = fopen("emp.dat", "r");

	if(fp == NULL)
	{
		puts("Cannot open file");
		exit(0);
	}

	while(fscanf(fp, "%s %d %f", e.name, &e.age, &e.bs) != EOF)
	{
		printf("%-10s %-3d %-6.1f\n", e.name, e.age, e.bs);
	}
	
	fclose(fp);
}

// Receives records from keyboard and writes them to a file in binary mode
void
third()
{
	FILE *fp;
	char another = 'y';
	struct emp
	{
		char name[40];
		int age;
		float bs;
	};

	struct emp e;

	fp = fopen("newb.dat", "wb");

	if(fp == NULL)
	{
		puts("Cannot open file");
		exit(0);
	}

	while(another == 'y')
	{
		printf("Enter name, age and basic salary  ");
		scanf("%s %d %f", e.name, &e.age, &e.bs);
		fwrite(&e, sizeof(e), 1, fp);

		printf("Add another record (y/n)  ");
		while(getchar() != '\n');
		another = getchar();
	}

	fclose(fp);
}

//
void
fourth()
{
	FILE *fp;
	struct emp
	{
		char name[40];
		int age;
		float bs;
	};

	struct emp e;

	fp = fopen("newb.dat", "rb");

	if(fp == NULL)
	{
		puts("Cannot open file");
		exit(0);
	}

	while(fread(&e, sizeof(e), 1, fp) == 1)
	{
		printf("%-10s %-3d %-4.1f\n", e.name, e.age, e.bs);
	}
	
	fclose(fp);
}

int
main()
{
	third();
	fourth();
	return(0);
}
