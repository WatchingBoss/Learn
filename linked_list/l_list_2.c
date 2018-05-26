/*
 * Create linked list and read it straight and reverse
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct List
{
	int number;
	struct List *next;
} LIST;

void create(LIST **);
void display(LIST *);
void displayReverse(LIST *);
void freeAlloc(LIST **);

int main()
{
	LIST *p    = NULL;

	printf("Enter data into the list\n");
	create(&p);

	printf("Displaying list\n");
	display(p);

	printf("Displaying reverse list\n");
	displayReverse(p);
	puts("");

	freeAlloc(&p);

	return(0);
}

void create(LIST **p)
{
	int number,
		choose = 1;
	LIST *temp, *rear;

	while(choose != 0)
	{
		printf("\nEnter number: ");
		scanf("%d", &number);

		temp = (LIST *)malloc(sizeof(LIST));
		temp->number = number;
		temp->next = NULL;

		if(*p == NULL)
			*p = temp;
		else
			rear->next = temp;

		rear = temp;
		printf("Want to continue? 1 or 0: ");
		scanf("%d", &choose);
	}
	puts("");
}

void display(LIST *p)
{
	while(p != NULL)
	{
		printf("%d ", p->number);
		p = p->next;
	}
	puts("");
}

void displayReverse(LIST *p)
{
	if(p != NULL)
	{
		displayReverse(p->next);
		printf("%d ", p->number);
	}
}

void freeAlloc(LIST **p)
{
	LIST *temp = *p;
	*p = (*p)->next;
	while((*p) != NULL)
	{
		free(temp);
		temp = *p;
		(*p) = (*p)->next;
	}
}
