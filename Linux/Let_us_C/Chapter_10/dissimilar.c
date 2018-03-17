#include <stdio.h>

void
array()
{
	char name[3];
	float price[3];
	int pages[3], i;

	printf("Enter names, prices and no. of pages of 3 books\n");
	for(i = 0; i <= 2; i++)
	{
		scanf("%c %f %d", &name[i], &price[i], &pages[i]);
		getc(stdin);
	}

	printf("And this is what you entered\n");
	for(i = 0; i <= 2; i++)
	{
		printf("%c %.2f %d\n", name[i], price[i], pages[i]);
	}	
}

void
structure()
{
	struct book
	{
		char name;
		float price;
		int pages;
	};
	struct book b1, b2, b3;

	printf("Enter names, prices and no. of pages of 3 books\n");
	scanf("%c %f %d", &b1.name, &b1.price, &b1.pages);
	getc(stdin);
	scanf("%c %f %d", &b2.name, &b2.price, &b2.pages);
	getc(stdin);
	scanf("%c %f %d", &b3.name, &b3.price, &b3.pages);

	printf("And this is what you entered\n");
	printf("%c %.2f %d\n", b1.name, b1.price, b1.pages);
	printf("%c %.2f %d\n", b2.name, b2.price, b2.pages);
	printf("%c %.2f %d\n", b3.name, b3.price, b3.pages);
}

int main()
{
    structure();
    return 0;
}
