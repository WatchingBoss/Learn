/* 
 * Sample of binary tree
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	int data;
	struct Node *left;
	struct Node *right;
} NODE;

NODE* newNode();

int main()
{
	NODE *root = newNode();

	root->left = newNode();
	root->right = newNode();

	root->left->left = newNode();

	return(0);
}

NODE* newNode()
{
	int data;

	NODE *node = (NODE *)malloc(sizeof(NODE));

	printf("Enter your number: ");
	scanf("%d", &data);

	node->data = data;

	node->left = node->right = NULL;

	return(node);
}
