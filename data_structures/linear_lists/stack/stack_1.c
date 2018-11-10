#include <stdio.h>
#include <stdlib.h>

void push(int *, int *, int);
void pop(int *, int *);
void display(int *, int *);

int main()
{
	int top = -1,
		max = 0,
		*stack,
		choose = 0;

	printf("Enter size of the stack: ");
	scanf("%d", &max);

	stack = (int *)malloc(sizeof(int) * max);

	while(choose != 4)
	{
		printf("\nEnter your choose:"
			   "\n1. Push number"
			   "\n2. Pop number"
			   "\n3. Display"
			   "\n4. Exit"
			   "\nYour choose:  ");
		scanf("%d", &choose);

		switch(choose)
		{
			case 1:
				push(stack, &top, max);
				break;
			case 2:
				pop(stack, &top);
				break;
			case 3:
				display(stack, &top);
				break;
			case 4:
				printf("Program has been terminated\n");
				break;
			default:
				printf("Invalid input\n");
				break;
		}
	}
	
	free(stack);
	return(0);
}

void push(int *stack, int *top, int max)
{
	int number;

	if(*top == (max - 1))
		printf("\nStack is full\n");
	else
	{
		printf("\nEnter the number to push: ");
		scanf("%d", &number);
		stack[++*top] = number;
	}
}

void pop(int *stack, int *top)
{
	if(*top == -1)
		printf("\nNo elements in stack\n");
	else
		printf("\nPopped element: %d\n", stack[(*top)--]);
}

void display(int *stack, int *top)
{
	int top1 = *top;

	if(top1 == -1)
		printf("\nNo elements to display\n");
	else
	{
		printf("\nDisplayed stack: ");
		while(top1 >= 0)
			printf("%d  ", stack[top1--]);
		printf("\n");
	}
}
