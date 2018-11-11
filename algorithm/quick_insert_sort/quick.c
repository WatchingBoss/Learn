#include "common.c"

static void short_insertion_sort( int *left, int *right ) {
	for ( int *pi = left + 1; pi <= right; ++pi ) {
		int  key = *pi;
		int *pj  = pi - 1;

		while ( pj >= left && *pj > key ) {
			*( pj + 1 ) = *pj;
			--pj;
		}

		*( pj + 1 ) = key;
	}
}

static void insertion_sort( int *left, int *right ) {
	int min = *left, *pmin = left, *pi = left + 1;

	while ( pi <= right ) {
		if ( *pi < min ) {
			pmin = pi;
			min  = *pi;
		}
		++pi;
	}

	*pmin = *left;
	*left = min;

	pi = left + 2;
	while ( pi <= right ) {
		int  h  = *pi;
		int *pj = pi - 1;

		while ( h < *pj ) {
			*( pj + 1 ) = *pj;
			--pj;
		}
		*( pj + 1 ) = h;
		++pi;
	}
}

#define swap( a, b ) \
	int temp = a;    \
	a        = b;    \
	b        = temp;

#define sort3fast( a, b, c )     \
	if ( b < a ) {               \
		if ( c < a ) {           \
			if ( c < b ) {       \
				swap( a, c )     \
			} else {             \
				int temp = a;    \
				a        = b;    \
				b        = c;    \
				c        = temp; \
			}                    \
		} else {                 \
			swap( a, b );        \
		}                        \
	} else {                     \
		if ( c < b ) {           \
			int temp = c;        \
			c        = b;        \
			b        = a;        \
			a        = temp;     \
		} else {                 \
			swap( b, c );        \
		}                        \
	}

int main( int argc, char *argv[] ) {
	if ( argc < 2 ) {
		printf( "Usage: %s <COUNT OF ELEMENTS IN ARRAY>\n", argv[0] );
		exit( EXIT_FAILURE );
	}

	int count = atoi( argv[1] );
	test( count );

	return 0;
}
