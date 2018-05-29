#ifndef STACK_H
#define STACK_H

#include "node.h"

typedef struct Stack
{
	NODE *tail;
} STACK;

STACK * newStack();
void stackPush(STACK *, char *);
char * stackPop(STACK *);
void stackPrint(STACK *);

#endif
