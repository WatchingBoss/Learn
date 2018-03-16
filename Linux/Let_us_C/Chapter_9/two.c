#include <stdio.h>
#include <string.h>

#define FOUND 1
#define NOTFOUND 0

void
twoDimensional()
{
	char masterlist[6][10] =
		{
			"akshay",
			"parag",
			"raman",
			"srinivas",
			"gopal",
			"rajesh"
		};

	int i, flag, a;
	char yourname[10];

	printf("Enter your name");
	scanf("%s", yourname);

	flag = NOTFOUND;
	for (i = 0; i <= 5 ; i++)
	{
		a = strcmp(&masterlist[i][0], yourname);
		if(a == 0)
		{
			printf("Welcoma, you can enter the palace\n");
			flag = FOUND;
			break;
		}
	}
	if(flag == NOTFOUND)
		printf("Sorry, you are a trespasser\n");
}

void
scanNames()
{
	char names[3][15];
	int i = 0;
	for(; i < 3; i++)
	{
		scanf("%s", &names[i][0]);
	}
	puts("");
	for(i = 2; i >= 0; i--)
	{
		printf("%s\n", &names[i][0]);
	}
}


// Array of Pointer to Strings
void
aopts()
{
	char *names[] =
		{
			"akshay",
			"parag",
			"raman",
			"srinivas",
			"gopal",
			"rajesh"
		};
			
}


// Exchange names using 2-D array of characters
void
First()
{
	char names[][10] = 
		{
			"akshay",
			"parag",
			"raman",
			"srinivas",
			"gopal",
			"rajesh"
		};
	int i;
	char t;

	printf("Original: %s %s\n", &names[2][0], &names[3][0]);

	for(i = 0; i <= 9; i++)
	{
		t = names[2][i];
		names[2][i] = names[3][i];
		names[3][i] = t;
	}
	
	printf("Original: %s %s\n", &names[2][0], &names[3][0]);
}


// Exchange names using array of points
void
Second()
{
	char *names[] =
		{
			"akshay",
			"parag",
			"raman",
			"srinivas",
			"gopal",
			"rajesh"
		};
	char *temp;
	printf("Original: %s %s\n", names[2], names[3]);

	temp = names[2];
	names[2] = names[3];
	names[3] = temp;

	printf("Original: %s %s\n", names[2], names[3]);	
}




int
main()
{
	First();
	Second();	
	return(0);
}
