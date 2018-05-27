/*
 * Create and traverse the tree recursively
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	int number;
	struct Node *left;
	struct Node *right;
} NODE;

void generate(NODE **, int);
void infix(NODE *);
void postfix(NODE *);
void prefix(NODE *);
void freeAlloc(NODE **);

int main()
{
	NODE *head = NULL;
	int choice = 0,
		number,
		flag = 0,
		key;

	while(choice != 5)
	{
		printf("\nEnter your choice:"
			   "\n1. Add"
			   "\n2. Traverse via infix"
			   "\n3. Traverse via prefix"
			   "\n4. Traverse via postfix"
			   "\n5. Exit"
			   "\nChoice:  ");
		scanf("%d", &choice);

		switch(choice)
		{
			case 1:
				printf("Enter number to additing: ");
				scanf("%d", &number);
				generate(&head, number);
				break;
			case 2:
				printf("Travese via infix:\n");
				infix(head);
				break;
			case 3:
				printf("Travese via prefix:\n");
				prefix(head);
				break;
			case 4:
				printf("Travese via postfix:\n");
				postfix(head);
				break;
			case 5:
				freeAlloc(&head);
				printf("Program has been terminated\n");
				break;
			default:
				printf("Invalid input\n");
				break;
		}
	}

	return(0);
}

void generate(NODE **head, int number)
{
	NODE *temp = *head,
		 *prev = *head;

	if(*head == NULL)
	{
		*head = (NODE *)malloc(sizeof(NODE));
		(*head)->number = number;
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

		temp = (NODE *)malloc(sizeof(NODE));
		temp->number = number;

		if(number >= prev->number)
			prev->right = temp;
		else
			prev->left = temp;
	}
}

void infix(NODE *head)
{
	if(head)
	{
		infix(head->left);
		printf("%d  ", head->number);
		infix(head->right);
	}
}

void postfix(NODE *head)
{
	if(head)
	{
		printf("%d  ", head->number);
		prefix(head->left);
		prefix(head->right);
	}
}

void prefix(NODE *head)
{
	if(head)
	{
		postfix(head->left);
		postfix(head->right);
		printf("%d  ", head->number);
	}
}

void freeAlloc(NODE **head)
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
