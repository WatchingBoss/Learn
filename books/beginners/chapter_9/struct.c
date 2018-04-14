#include <stdio.h>

typedef struct employee
{
	int id;
	int salary;
} emp;

void proc(emp *);


int main()
{
    emp emp1 = {0, 0};

	printf("%d %d\n", emp1.id, emp1.salary);

	proc(&emp1);

	printf("%d %d\n", emp1.id, emp1.salary);

    return 0;
}

void proc(emp *e)
{
	e->id = 123;
	e->salary = 25000;
}
