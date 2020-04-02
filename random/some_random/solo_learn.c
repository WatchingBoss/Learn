#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void sample_error_handling(){
	FILE *fp;
	errno = 0;

	fp = fopen("no_such_file.txt", "r");
	if(fp == NULL){
		perror("Error");
		fprintf(stderr, "%s\n", strerror(errno)); // Same as perror
		exit(EXIT_FAILURE);
	}
}

#define T 42
void compile_error(){
	int T = 8;
	printf("%d", T);
}
#undef T

int main(){
	// sample_error_handling();
	// compile_error();

	return 0;
}
