#include <stdio.h>

void sw(int i)
{
    switch(i)
    {
		case 1:
            printf("I am in case 1\n");
            break;
        case 2:
            printf("I am in case 2\n");
            break;
        case 3:
            printf("I am in case 3\n");
            break;
        default:
            printf("I am in default\n");
    }
}

void sc(char ch)
{
	switch(ch)
	{
		case 'a':
		case 'A':
			printf("a as in ashar");
			break;
		case 'b':
		case 'B':
			printf("b as in brain");
			break;
		case 'c':
		case 'C':
			printf("c as in cookie");
			break;
		default:
			printf("wish you knew what are alphabets");
	}
}

int main()
{

    return 0;
}
