#define _GNU_SOURCE

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *open_sesame(char *name)
{
	FILE *stream;

	errno = 0;
	stream = fopen(name, "r");

	if(stream == NULL)
	{
		fprintf(stderr, "%s: Could not open file %s; %s\n",
				program_invocation_short_name, name,strerror(errno));
		exit(EXIT_FAILURE);
	}
	else
		return stream;
}

int main(int argc, char *argv[])
{
	char *name = argv[1];
	FILE *fp;

	fp = open_sesame(name);

	char word[15];

	while(fscanf(fp, "%s", word) != EOF)
	{
		printf("%s\n", word);
	}

	return(0);
}

