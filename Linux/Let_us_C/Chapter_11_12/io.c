#include <stdio.h>

void
first()
{
	int weight = 63;

	printf("weight is %d kg\n", weight);
	printf("weight is %2d kg\n", weight);
	printf("weight is %4d kg\n", weight);
	printf("weight is %6d kg\n", weight);
	printf("weight is %-6d kg\n", weight);
}

void
second()
{
	char firstname1[] = "Sandy";
	char surname1[] = "Malya";
	char firstname2[] = "AjayKumar";
	char surname2[] = "Gurubaxani";

	printf("%-20s%-20s\n%-20s%-20s\n",
		   firstname1, surname1, firstname2, surname2);
}

void
third()
{
	int i = 10;
	char ch = 'A';
	float a = 3.14;
	char str[20];

	int y;
	char hh;
	float b;
	
	printf("%d %c %f\n", i, ch, a);
	sprintf(str, "%d %c %f\n", i, ch, a);
	printf("%s\n", str);

	sscanf(str, "%d %c %f", &y, &hh, &b);
	printf("%d %c %f\n", y, hh, b);
}

int main()
{
    third();
    return 0;
}
