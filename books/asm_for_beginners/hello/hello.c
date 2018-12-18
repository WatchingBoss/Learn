#include <stdio.h>

int just_return( ) { return 105; }

int main( ) {
	printf( "%d\n"
	        "hello\n",
	        just_return( ) );

	return 0;
}
