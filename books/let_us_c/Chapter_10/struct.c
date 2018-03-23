#include <stdio.h>
#include <string.h>

void
first()
{
	struct name
	{
		char first;
		char second;
		int integer;
	} n1, n2, n3;
	
	struct book
	{
		char name[10];
		float price;
		int pages;
	};

	struct book b1 = {"Basic", 130.00, 550};
	struct book b2 = {"Physics", 150.80, 800};
}

void
second()
{
	struct book
	{
		char name;
		float price;
		int pages;
	};

	struct book b[3];
	int i;

	for (i = 0; i <= 2; i++)
	{
		printf("Enter name, price and pages\n");
		scanf("%c %f %d", &b[i].name, &b[i].price, &b[i].pages);
		getc(stdin);
	}

	for(i = 0; i <= 2; i++)
	{
		printf("%c %.2f %d\n", b[i].name, b[i].price, b[i].pages);
	}
}

void
third()
{
	struct employee
	{
		char name[10];
		int age;
		float salary;
	};
	struct employee e1 = {"Sanjay", 30, 5500.50};
	struct employee e2, e3;

	// piece-meal copying
	strcpy(e2.name, e1. name);
	e2.age = e1.age;
	e2.salary = e1.salary;

	// copying all elements at one go

	e3 = e2;

	printf("%s %d %.2f\n", e1.name, e1.age, e1.salary);
	printf("%s %d %.2f\n", e2.name, e2.age, e2.salary);
	printf("%s %d %.2f\n", e3.name, e3.age, e3.salary); 
}

void
nested()
{
	struct address
	{
		char phone[15];
		char city[25];
		int pin;
	};

	struct emp
	{
		char name[25];
		struct address a;
	};

	struct emp e = {"jeru", "531046", "nagput", 10};

	printf("name = %s phone = %s\n"
		   "city = %s pin = %d\n", e.name, e.a.phone, e.a.city, e.a.pin);
}

// Example passing elements of structure to function

void
call(char *s, char *t, int n)
{
	printf("%s %s %d\n", s, t, n);
}


void
prim()
{
	struct book
	{
		char name[25];
		char author[25];
		int callno;
	};

	struct book b1 = {"Name", "Last name", 125};

	call(b1.name, b1.author, b1.callno);
}
//////////////////////////////////////////////

// Example passing struct to function

struct book1
{
	char name[25];
	char author[25];
	int callno;
};

void
call1(struct book1 b)
{
	printf("%s %s %d\n", b.name, b.author, b.callno);
}

void
primer()
{
	struct book1 b1 = {"Cool book", "Santiago", 4565};
	call1(b1);
}

///////////////////////////////////////////////

// Structure pointer

void
fourth()
{
	struct book
	{
		char name[25];
		char author[25];
		int callno;
	};
	
	struct book b1 = {"Name", "Author", 5324};
	struct book *ptr;

	ptr = &b1;

	printf("%s %s %d\n", b1.name, b1.author, b1.callno);
	printf("%s %s %d\n", ptr->name, ptr->author, ptr->callno);
}

//////////////////////////////////////////////


int
main()
{
	fourth();
	
	return(0);
}
