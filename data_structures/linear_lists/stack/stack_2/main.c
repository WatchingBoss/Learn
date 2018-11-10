#include <stdio.h>
#include "stack.h"

int main()
{
	STACK *stack = newStack();

	char *string[] = {"string", "test", "is", "this"};

	for(int i = 0; i < 4; ++i)
	{
		stackPush(stack, string[i]);
		stackPrint(stack);
	}

	printf("___________________\n\n");

	for(int i = 0; i < 4; ++i)
	{
		stackPop(stack);
		stackPrint(stack);
	}

	return(0);
}
