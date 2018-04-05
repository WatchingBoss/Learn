#include <stdio.h>

void
showbits(int n)
{
	int i, k, andmask;

	for(i = 15; i >= 0; i--)
	{
		andmask = 1 << i;
		k = n & andmask;

		k == 0 ? printf("0") : printf("1");
	}
}

void
first()
{
	int a, b;
	a = 128;
	b = a >> 1;
	printf("%d\n", b);
	b = a << 1;
	printf("%d\n", b);
}

void
second()
{
	int i = 0, n = 10;
	for(; i < n; i++)
	{
		printf("%d = ", i);
		showbits(i);
		printf("\n");
	}
}


int main()
{
    second();

    return 0;
}
