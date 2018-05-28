/*
 * Depth-first search traversal in binary tree
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Tree
{
	int number,
		visited;
	struct Tree *left;
	struct Tree *right;
} TREE;

void generate(TREE **, int);
void display(TREE *);
void freeAlloc(TREE **);

int main()
{
	TREE *head = NULL;
	int number = 0,
		choice = 0;

	while(choice != 3)
	{
		printf("\nEnter you choice:"
			   "\n1. Add number"
			   "\n2. Display numbers"
			   "\n3. Exit"
			   "\nYour choice:  ");
		scanf("%d", &choice);

		switch(choice)
		{
			case 1:
				printf("Enter number to adding: ");
				scanf("%d", &number);
				generate(&head, number);
				break;
			case 2:
				display(head);
				break;
			case 3:
				freeAlloc(&head);
				printf("Program has been terminated\n");
				break;
			default:
				printf("Invalid input\n");
		}
	}


	return(0);
}

void generate(TREE **head, int number)
{
	TREE *temp = *head,
 		 *prev = *head;

	if(*head == NULL)
	{
		*head = (TREE *)malloc(sizeof(TREE));
		(*head)->number = number;
		(*head)->visited = 0;
		(*head)->left = (*head)->right = NULL;
	}
	else
	{
		while(temp != NULL)
		{
			if(number > temp->number)
			{
				prev = temp;
				temp = temp->right;
			}
			else
			{
				prev = temp;
				temp = temp->left;				
			}
		}

		temp = (TREE *)malloc(sizeof(TREE));
		temp->number = number;
		temp->visited = 0;

		if(temp->number >= prev->number)
			prev->right = temp;
		else
			prev->left = temp;
	}
}

void display(TREE *head)
{
	TREE *temp = head,
		 *prev;

	printf("\nOn depth-first search traversal we have:\n");
	while(temp && !temp->visited)
	{
		if(temp->left && !temp->left->visited)
			temp = temp->left;
		else if(temp->right && !temp->right->visited)
			temp = temp->right;
		else
		{
			printf("%d  ", temp->number);
			temp->visited = 1;
			temp = head;
		}
	}
	printf("\n");
}

void freeAlloc(TREE **head)
{
	if(*head != NULL)
	{
		if((*head)->left)
			freeAlloc(&(*head)->left);
		if((*head)->right)
			freeAlloc(&(*head)->right);

		free(*head);
	}
}
