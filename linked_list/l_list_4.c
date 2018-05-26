/*
 * Create linked list and search in it 
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct List
{
	int number;
	struct List *next;
} LIST;

void create(LIST **, int);
void search(LIST *, int, int);
void freeAlloc(LIST **);

int main()
{
	LIST *head = NULL;
	int keySearch, numberNodes;

	srand(time(NULL));

	printf("Enter the number of nodes: ");
	scanf("%d", &numberNodes);

	printf("\nOutput the list\n");
	create(&head, numberNodes);

	printf("\nEnter key to search: ");
	scanf("%d", &keySearch);

	search(head, keySearch, numberNodes);

	freeAlloc;

	return(0);
}

void create(LIST **head, int number)
{
	LIST *temp;

	for(int i = 0; i < number; ++i)
	{
		temp = (LIST *)malloc(sizeof(LIST));
		temp->number = rand() % number;

		if(*head == NULL)
		{
			*head = temp;
			temp->next = NULL;
		}
		else
		{
			temp->next = *head;
			*head = temp;
		}
		printf("%d  ", temp->number);
	}
}

void search(LIST *head, int key, int number)
{
	int position = number,
		find_key = 0;
	
	while(head != NULL)
	{
		if(head->number == key)
		{
			printf("Key found on position %d\n", position);
			find_key = 1;
		}
		head = head->next;
		--position;		
	}

	if(find_key == 0)
		printf("Key not found\n");
}

void freeAlloc(LIST **head)
{
	LIST *temp;

	while(*head != NULL)
	{
		temp = *head;
		*head = (*head)->next;
		free(temp);
	}
}
