/*
 * This program creates a linked list and display element of this list
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Links
{
	int number;
	struct Links *ptr;
} LINKS;

void list();

int main()
{
	list();

	return(0);
}

void list()
{
	LINKS *head, *first, *temp = 0;
	int count = 0;
	int choice = 1;
	first = 0;

	while(choice)
	{
		head = (LINKS *)malloc(sizeof(LINKS));
		printf("Enter the data item: ");
		scanf("%d", &head->number);

		if(first != 0)
		{
			temp->ptr = head;
			temp = head;
		}
		else
			first = temp = head;

		fflush(stdin);
		printf("Do you want to continue? 0 or 1: ");
		scanf("%d", &choice);
	}

	temp->ptr = 0;

	temp = first;

	printf("Status of the linked list: ");
	while(temp != 0)
	{
		printf("%d => ", temp->number);
		++count;
		temp = temp->ptr;
	}
	printf("NULL\n");

	printf("\nNo nodes in the list = %d\n", count);
}
