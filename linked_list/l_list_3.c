/*
 * Search for an element in linked list
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Link
{
	int number;
	struct Link *next;
} LINK;

void create(LINK **, int);
void search(LINK *, int, int);
void freeAlloc(LINK **, int);

int main()
{
	LINK *head;
	int keySearch, numNodes;

	srand(time(NULL));

	printf("Enter the number of nodes: ");
	scanf("%d", &numNodes);

	create(&head, numNodes);

	printf("\nEnter key to search: ");
	scanf("%d", &keySearch);

	search(head, keySearch, numNodes);

	freeAlloc(&head, numNodes);

	return(0);
}

void create(LINK **head, int numNodes)
{
	LINK *temp;

	for(int i = 0; i < numNodes; ++i)
	{
		temp = ((LINK *)malloc(sizeof(LINK)));
		temp->number = rand() % numNodes;
		printf("%d  ", temp->number);

		if(*head == NULL)
		{
			*head = temp;
			(*head)->next = NULL;
		}
		else
		{
			temp->next = *head;
			*head = temp;
		}
	}
}

void search(LINK *head, int keySearch, int index)
{
	if(head->number == keySearch)
		printf("Key found at Prosition: %d\n", index);
	
	if(index == 0)
		return;

	search(head->next, keySearch, index - 1);
}

void freeAlloc(LINK **head, int numNodes)
{
	LINK *temp;

	while(numNodes)
	{
		temp = *head;
		*head = (*head)->next;
		free(temp);

		--numNodes;
	}
}
