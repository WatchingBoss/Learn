#include <stdio.h>

int
main()
{
	char ch;
	while((ch = getc(stdin)) != EOF)
		putc(ch, stdout);

	return(0);
}
