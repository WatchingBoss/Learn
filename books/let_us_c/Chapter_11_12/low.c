#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>

void
low()
{
	char buffer[512], source[128], target[128];
	int inhandle, outhandle, bytes;

	printf("Enter source file name");
	gets(source);

	inhandle == open(source, O_RDONLY|O_BINARY);
	if(inhandle == -1)
	{
		puts("Cannot open file");
		exit(0);
	}

	printf("Enter target file name");
	gets(target);

	outhandle = open(target, O_CREAT|O_BINARY|O_WRONLY, S_IWRITE);
	if(inhandle == -1)
	{
		puts("Cannot open file");
		close(inhandle);
		exit(0);
	}

	while(1)
	{
		bytes = read(inhandle, buffer, 512);

		if(bytes > 0)
			write(outhandle, buffer, bytes);
		else
			break;
	}

	close(inhandle);
	close(outhandle);
}

int
main()
{
	low();
	
	return(0);
}
