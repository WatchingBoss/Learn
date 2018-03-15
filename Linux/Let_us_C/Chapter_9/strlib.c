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

int main()
{
	second();
	secondSecond();
    return 0;
}
