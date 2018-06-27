/*
 * Sample of using obstack_alloc()
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <obstack.h>

struct obstack *string_obstack;

char * copystring(char *string)
{
	size_t len = strlen(string) + 1;
	char *s = (char *) obstack_alloc(string_obstack, len);
	memcpy(s, string, len);

	return(s);
}

int main()
{
	char *str = "hello everybody here";
	char *obstack_str = copystring(str);

	printf("%s\n%s\n", str, obstack_str);

	exit(EXIT_SUCCESS);
}
