/* 
 * Binary tree implementation
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TEST_NUMBER 25
#define LIMIT 150

typedef struct Node
{
	struct Node *left;
	struct Node *right;
	int value;
} NODE;

void in(NODE *);
void pre(NODE *);
void post(NODE *);
NODE* new(int);
void insert(NODE **, NODE *);
NODE* search(NODE *, int);
void searchByPointer(NODE *, int, NODE **);

int main()
{
	int test,
		c,
		success;
	test = c = success = 0;

	srand(time(NULL));

	NODE *root = NULL;

	// insetrion test
	while(c++ < TEST_NUMBER)
		insert(&root, new(rand() % LIMIT));

	// print test
	printf("\n > in order -> ");
	in(root);

	printf("\n > pre order -> ");
	pre(root);

	printf("\n > post order -> ");
	post(root);
	
	// search test

	printf("\n\n > test search: \n");

	while(test++ < LIMIT)
	{
		if(search(root, test) > 0)
		{
			printf("  - %d\n", test);
			success++;
		}
	}

	printf("\n <success> = %d <faild> == %d>\n", success, LIMIT - success);
	printf(" <duble> = %d\n", TEST_NUMBER - success);

	return(0);
}

// [left, visit, right]
void in(NODE *n)
{
	if(n->left)
		in(n->left);

	printf("%d ", n->value);

	if(n->right)
		in(n->right);
}

// [visit, left, right]
void pre(NODE *n)
{
	printf("%d ", n->value);

	if(n->left)
		pre(n->left);

	if(n->right)
		pre(n->right);
}

// [left, right, visit]
void post(NODE *n)
{
	if(n->left)
		post(n->left);

	if(n->right)
		post(n->right);

	printf("%d ", n->value);
}

// create a new node and set default nodes
NODE* new(int value)
{
	NODE *n = (NODE *)malloc(sizeof(NODE));

	n->value = value;
	n->left = n->right = NULL;
	return(n);
}

void insert(NODE **root, NODE *child)
{
	if(!*root)
		*root = child;
	else
	{
		if(child-> value <= (*root)->value)
			insert(&(*root)->left, child);  // child value is minor/equal to current node
                                            // call insertion on left node
		else
			insert(&(*root)->right, child); // call insertion on right node
	}
}

NODE* search(NODE *root, int value)
{
	if(root == NULL)
		return(NULL);               // node not found
	else if(root->value == value)
		return(root);               // first node address found
	else if(value > root->value)
		search(root->right, value); // recursive search on right side of tree
	else
		search(root->left, value);  // recursive search on left side of tree
}

void searchByPointer(NODE *root, int value, NODE **save)
{
	*save = search(root, value);
}
