#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum {false, true} bool;

void game();

int main()
{
	srand(time(NULL));

	game();
    
    return 0;
}

void game()
{
	int response,
		*answer,
		*op1,
		*op2,
		x;
	bool *result;

	printf("\nMath Quiz\n\n");
	printf("Enter # of quistions: ");
	scanf("%d", &response);

	op1    = (int *) calloc(response, sizeof(int));
	op2    = (int *) calloc(response, sizeof(int));
	answer = (int *) calloc(response, sizeof(int));
	result = (bool *) calloc(response, sizeof(bool));

	if(op1 == NULL || op2 == NULL || answer == NULL || result == NULL)
	{
		printf("\nOut of Memory!\n");
		return;
	}

	for(x = 0; x < response; x++)
	{
		op1[x] = rand() % 100;
		op2[x] = rand() % 100;

		printf("\n%d + %d = ", op1[x], op2[x]);
		scanf("%d", &answer[x]);

		if(answer[x] == op1[x] + op2[x])
			result[x] = true;
		else
			result[x] = false;
	}

	printf("\nQuiz Results\n");
	printf("\nQuestion\tYour Answer\tCorrect\n");

	for(x = 0; x < response; x++)
	{
		if(result[x] == true)
			printf("%d + %d\t\t%d\t\tYes\n", op1[x], op2[x], answer[x]);
		else 
			printf("%d + %d\t\t%d\t\tNo\n", op1[x], op2[x], answer[x]);
	}

	free(op1);
	free(op2);
	free(answer);
	free(result);
}
