#include <stdio.h>

int
loopFor(int x)
{
	int f = 1, i;
	for (i = x; i >= 1; --i)
	{
		f = f * i;	
	}
	return(f);
}

int
recursion(int x)
{
	if (x == 1)
	{
		return(1);
	}
	else
	{
		x = x * recursion(x - 1);
	}
	return(x);
}

int
main()
{
	int num;
	puts("Enter number: ");
	scanf("%d", &num);
    printf("Loop for:  the factorial of %d is %d\n", num, loopFor(num));
	printf("Recursion: the factorial of %d is %d\n", num, recursion(num));
    return(0);
}
