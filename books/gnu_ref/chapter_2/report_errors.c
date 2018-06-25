#define _GNU_SOURCE

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>

typedef unsigned int uint;

FILE * open_file(char *name)
{
	FILE *fp;

	fp = fopen(name, "r");

	return(fp);
}

void er(char *name)
{
	char *line = NULL;
	size_t len = 0;
	uint lineno = 0;
	error_message_count = 0;

	FILE *fp = open_file(name);

	while(!feof_unlocked(fp))
	{
p		ssize_t n = getline(&line, &len, fp);
		if(n <= 0)
			break;
		++lineno;

//		if()
//			error_at_line(0, errval, filename, lineno, "some error text");
	}
}

int main(int argc, char *argv[])
{
	char *name = *(argv + 1);

	er(name);

	return(0);
}
