#include <stdio.h>

/*
 * Range A - Z, a - z for switch case
 */

int main()
{
	for(char i = 'A'; i <= 'z'; ++i)
		printf("case \'%c\': \n", i);

	return(0);
}
