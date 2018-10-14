#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
	char *str;
	int   sz = 'z' - 'a' + 1;

	str = (char *)malloc(sizeof(char) * sz);

	for (int ch = 'a', i = 0; ch != 'z' + 1; ++ch) str[i++] = (char)ch;

	initStack(3);

	while (*str != '\0') { push(*str++); }

	while (isEmpty() == 0) printf("%c ", pop());

	putchar('\n');
	destroyStack();

	return (0);
}
