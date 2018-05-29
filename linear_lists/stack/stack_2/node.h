#ifndef NODE_H
#define NODE_H

typedef struct Node
{
	struct Node *next;
	char *val;
} NODE;

NODE *newNode(char *);

#endif
