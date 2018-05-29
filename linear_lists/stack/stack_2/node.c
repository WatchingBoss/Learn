#include <stdlib.h>
#include "node.h"

NODE * newNode(char *str)
{
	NODE *n = (NODE *)malloc(sizeof(NODE *));
	n->next = NULL;
	n->val = str;

	return(n);
}
