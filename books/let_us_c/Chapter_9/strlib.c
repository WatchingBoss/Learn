#include <stdio.h>
#include <string.h>

void
first()
{
	char arr[] = "Bamboozled";
	int len1, len2;

	len1 = strlen(arr);
	len2 = strlen("Humpty Dumpty");

	printf("string = %s length = %d\n", arr, len1);
	printf("string = %s length = %d\n", "Humpty Dumpty", len2);
}

// Own function which finds length of string
int 
xstrlen(char *s)
{
	int length = 0;

	while(*s != '\0')
	{
		length++;
		s++;
	}
	return(length);
}


void
firstFirst()
{
	char arr[] = "Bamboozled";
	int len1, len2;

	len1 = xstrlen(arr);
	len2 = xstrlen("Humpty Dumpty");

	printf("string = %s length = %d\n", arr, len1);
	printf("string = %s length = %d\n", "Humpty Dumpty", len2);
}

void
second()
{
	char source[] = "Sayonara";
	char target[20];

	strcpy(target, source);
	printf("source string = %s\n", source);
	printf("target string = %s\n", target);	
}

// Own function which copies string to other array
int
xstrcpy(char *t, char *s)
{
	while(*s != '\0')
	{
		*t = *s;
		s++;
		t++;
	}
	*t = '\0';
}

void
secondSecond()
{
	char source[] = "Sayonara";
	char target[20];

	xstrcpy(target, source);
	printf("source string = %s\n", source);
	printf("target string = %s\n", target);	
}

void
third()
{
	char source[] = "Folks!";
	char target[30] = "Hello";

	strcat(target, source);

	printf("Source string = %s\n", source);
	printf("Target string = %s\n", target);
}

// Create own function which concatinate strings
int
xstrcat(char *t, char *s)
{
	while(*t != '\0')
	{
		t++;
	}
	
	while(*s != '\0')
	{
		*t = *s;
		s++;
		t++;
	}
	*t = '\0';
}

void
thirdThird()
{
	char source[] = "Folks!";
	char target[30] = "Hello";

	xstrcat(target, source);

	printf("Source string = %s\n", source);
	printf("Target string = %s\n", target);
	
}

void
fourth()
{
	char string1[] = "Jerry";
	char string2[] = "Ferry";

	int i, j, k;

	i = strcmp(string1, "Jerry");
	j = strcmp(string1, string2);     // ASCII value of 'J' - ASCII value of 'F'
	k = strcmp(string1, "jerry boy"); // ASCII value of '\0' - ASCII value of ' '

	printf("%d %d %d\n", i, j, k);
	
}

// Create own function which compares two strings and return 0 or difference between ASCII values
// of letters
int
xstrcmp(char *s1, char *s2)
{
	int cmp = 0;
	
	while(*s1 == *s2 && *s1 != '\0')
	{
		s1++;
		s2++;
	}

	if(*s1 != *s2)
	{
		cmp = *s1 - *s2;
		return(cmp);
	}

	return(cmp);
}

void fourthFourth()
{
	char string[] = "Hello";
	int i, j;

	i = xstrcmp(string, "Hello");
	j = xstrcmp(string, "Hola");

	printf("%d %d\n", i, j);
}

int main()
{

    return 0;
}
