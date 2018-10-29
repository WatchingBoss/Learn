#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

static void letter_to_binary( const char ch ) {
	char dec    = ch;
	char bin[9] = { 0 };

	for ( int i = 7; i >= 0; --i ) {
		char c;
		if ( dec ) {
			size_t rem = dec % 2;
			rem ? ( c = '1' ) : ( c = '0' );
			dec /= 2;
		} else
			c = '0';
		bin[i] = c;
	}
	bin[8] = '\0';

	printf("%s ", bin);
}

static void print_in_binary( const char *str, int last ) {
	size_t len = strlen( str );

	for ( size_t i = 0; i < len; ++i ) letter_to_binary( str[i] );
	if ( !last ) letter_to_binary( ' ' );
}

int main( int argc, char *argv[] ) {
	if ( argc < 2 ) {
		printf( "Usage: %s <STRING>", argv[0] );
		exit( EXIT_FAILURE );
	}

	for ( int i = 1; i < argc; ++i ) {
		if ( i != argc - 1 ) print_in_binary( argv[i], FALSE);
		else print_in_binary( argv[i], TRUE);
	}

	return 0;
}
