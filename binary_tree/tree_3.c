/*
 * Search in tree recursively
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
int search(NODE *, int);
void freeAlloc(NODE **);

int main()
{
	NODE *head = NULL;
	int choice = 0,
		number,
		flag = 0,
		keySearch;

	while(choice != 3)
	{
		printf("\nEnter your choice:"
			   "\n1. Add number"
			   "\n2. Search in tree"
			   "\n3. Exit"
			   "\nYour choice:  ");
		scanf("%d", &choice);

		switch(choice)
		{
			case 1:
				printf("\nEnter number to adding: ");
				scanf("%d", &number);
				generate(&head, number);
				break;
			case 2:
				printf("\nEnter number to search: ");
				scanf("%d", &keySearch);
				flag = search(head, keySearch);
				if(flag)
					printf("Number has been found\n");
				else
					printf("Number not found\n");
				break;
			case 3:
				freeAlloc(&head);
				printf("\nProgram has been terminated\n");
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
			if(number > temp -> number)
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

int search(NODE *head, int keySearch)
{
	while(head != NULL)
	{
		if(keySearch > head->number)
			return(search(head->right, keySearch));
		else if(keySearch < head->number)
			return(search(head->left, keySearch));
		else
			return(1);
	}

	return(0);
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
