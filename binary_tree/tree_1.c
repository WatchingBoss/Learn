#include <stdio.h>
#include <stdlib.h>

typedef struct Tree
{
	int number;
	struct Tree *left;
	struct Tree *right;
} TREE;

void generate(TREE **, int);
void display(TREE *);
void freeAlloc(TREE **);

int main()
{
	TREE *head = NULL;
	int choice = 0,
		flag = 0,
		key,
		number;

	while(choice != 3)
	{
		printf("\nEnter your choice:"
			   "\n1. Addition"
			   "\n2. Display"
			   "\n3. Exit                  ");
		scanf("%d", &choice);

		switch(choice)
		{
			case 1:
				printf("Enter number for add: ");
				scanf("%d", &number);
				generate(&head, number);
				break;
			case 2:
				printf("\n");
				display(head);
				printf("\n");				
				break;
			case 3:
				freeAlloc(&head);
				printf("Program terminated");
				break;
			default:
				printf("Invalid input!");
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

		if(number >= prev->number)
			prev->right = temp;
		else
			prev->left = temp;
	}
}

void display(TREE *head)
{
	if(head)
	{
		if(head->left)
			display(head->left);
		if(head->right)
			display(head->right);

		printf("%d  ", head->number);
	}
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
