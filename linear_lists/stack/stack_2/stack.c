#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "node.h"

STACK * newStack()
{
	STACK *s = (STACK *)malloc(sizeof(STACK*));
	s->tail = NULL;

	return(s);
}

void stackPush(STACK *stack, char *val)
{
	NODE *n = newNode(val);
	NODE *temp = stack->tail;

	n->next = temp;
	stack->tail = n;
}

char * stackPop(STACK *stack)
{
	char *val;

	if(stack->tail == NULL)
	{
		perror("Stack is empty");
		exit(-1);
	}

	val = stack->tail->val;
	stack->tail = stack->tail->next;

	return(val);
}

void stackPrint(STACK *stack)
{
	printf("Stack: ");
	for(NODE *temp = stack->tail; temp != NULL; temp = temp->next)
		printf("%s ", temp->val);
	printf("\n");
}
