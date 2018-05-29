#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

static int sz = 512;
static char *stack;
static int top = 0;

void initStack(int size)
{
	if(size == 0)
		size = sz;
	else
		sz = size;

	stack = (char *)malloc(sz);
}

void destroyStack()
{
	free(stack);
}

void push(char ch)
{
	if(top == sz)
	{
		sz += sz;
		stack = (char *)realloc(stack, sz);
	}

	stack[top++] = ch;
}

char pop()
{
	return(stack[--top]);
}

int isEmpty()
{
	return(top == 0);
}

int isFull()
{
	return(top == sz);
}
