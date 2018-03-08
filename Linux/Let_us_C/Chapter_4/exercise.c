#include <stdio.h>

void grace()
{
	int class, failSubject, grace = 0;

	printf("Enter student\'s class and amount of failed subjects: ");
	scanf("%d %d", &class, &failSubject);

	switch(class)
	{
		case 1:
		{
			if (failSubject <= 3)
			    grace = 5;
		} break;
		case 2:
		{
			if (failSubject <= 2)
			    grace = 4;
		} break;
		case 3:
		{
			if (failSubject <= 1)
			    grace = 5;
		} break;
		default:
		{
			grace = 0;
		} break;
	}

	if (grace == 0)
		printf("Student has not grace\n");
	else	
		printf("Student has %d grace per subject\n", grace);
}

int main()
{
    int a = 5;
    printf("Memory address of a with value %d is %d %u %p\n", a, &a, &a, &a);
    return 0;
}
