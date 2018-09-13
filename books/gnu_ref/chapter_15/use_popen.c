#include <stdio.h>
#include <stdlib.h>

void sys_er(const char *e)
{
	perror(e);
	exit(EXIT_FAILURE);
}

void write_to_pipe(FILE *stream)
{
	for(size_t i = 0; i < 10; ++i)
		fprintf(stream, "%ld\n", i);
	if(ferror(stream))
		sys_er("Outpur to stream failed. Error");
}

int main()
{
	FILE *output = popen("more", "w");

	if(!output)
		sys_er("popen error");

	write_to_pipe(output);

	if(pclose(output))
		sys_er("pclose error");

	return 0;
}
