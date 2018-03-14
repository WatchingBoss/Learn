#include <stdio.h>

/////////////////////
int
arr ()
{
    int arr[] = {10, 20, 30, 45, 67, 56, 74};
	int *i, *j;

	i = &arr[1];
	j = &arr[5];

	printf("%ld %d\n", j - i, *j - *i);
}
//////////////////////////////////////
void
call(int *j, int n)
{
	int i;
	for(i = 0; i < n; i++)
	{
		printf("element = %d\n", *j);
		j++; // increment pointer to point to next element 
	}
}
void
first()
{
	int num[] = {24, 34, 12, 44, 56, 17};
	call(&num[0], 6);
}
/////////////////////////////////////////////

void
pointToArray()
{
	int s[5][2] =
		{
			{1234, 56},
			{1212, 33},
			{1434, 80},
			{1312, 78}
		};
	int (*p)[2];
	int i, j, *pint;

	for(i = 0; i <= 3; i++)
	{
		p = &s[i];
		pint = p;
		for(j = 0; j <= 1; j++)
		{
			printf("%d ", *(pint + j));
		}
		printf("\n");
	}
}

////////////////////////////////////////////

void
display(int *q, int row, int col)
{
	int i, j;

	for(i = 0; i < row; i++)
	{
		for(j = 0; j < col; j++)
		{
			printf("%d", *(q + i * col + j)); // *(base address + row no. * no. of columns + column no.))
		}
		printf("\n");
	}
	printf("\n");
}

void
show(int (*q)[4], int row, int col)
{
	int i, j;
	int *p;

	for(i = 0; i < row; i++)
	{
		p = q + i;
		for(j = 0; j < col; j++)
		{
			printf("%d", *(p + j));
		}
		printf("\n");
	}
	printf("\n");
}

void
print(int q[][4], int row, int col) // q[][4] == (*q)[4]
{
	int i, j;

	for(i = 0; i < row; i++)
	{
		for(j = 0; j < col; j++)
		{
			printf("%d", q[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}


void
mainHere()
{
	int a[3][4] =
	{
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 0, 1, 6}
	};

	display(a, 3, 4);
	show(a, 3, 4);
	print(a, 3, 4);
}

///////////////////////////////////////////

void
threeDA()
{
	int arr[3][4][2] =
		{
			{
				{2, 4},
				{7, 8},
				{3, 5},
				{5, 6}
			},
			{
				{7, 6},
				{3, 4},
				{5, 3},
				{2, 3}
			
			},
			{
				{8, 9},
				{7, 2},
				{3, 4},
				{5, 1}
			
			}
		}
}

//////////////////////////////////////////
int main()
{

    return 0;
}
