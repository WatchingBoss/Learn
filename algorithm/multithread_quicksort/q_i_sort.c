/*
 * Quicksort with insertion sort
 */

#include "common.c"

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

#define swap( a, b )     \
	{                    \
		int temp = a;    \
		a        = b;    \
		b        = temp; \
	}

#define sort3fast( a, b, c )     \
	if ( b < a ) {               \
		if ( c < a ) {           \
			if ( c < b ) {       \
				swap( a, c );    \
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

static int *partition( int *left, int *right ) {
	int *left0 = left, pivl = *left;

	++left;

	int *p   = left0 + ( right - left0 ) / 2;
	int  piv = *p;

	*p    = *left;
	*left = piv;

	int pivr = *right;

	sort3fast( pivl, piv, pivr );

	*right = pivr;
	*left0 = pivl;
	*left  = piv;

	for ( ;; ) {
		do
			++left;
		while ( *left < piv );
		do
			--right;
		while ( *right > piv );

		if ( left >= right ) break;
		swap( *left, *right );
	}

	*( left0 + 1 ) = *right;
	*right         = piv;
	return right;
}

void sort( int *arr, int count ) {
	int *stack[64] = { 0 };
	int  sp        = 0;
	int *left = arr, *right = arr + count - 1;

	for ( ;; ) {
		if ( right - left < 50 ) {
			insertion_sort( left, right );
			if ( !sp ) break;
			sp -= 2;
			left  = stack[sp];
			right = stack[sp + 1];
		} else {
			int *mid = partition( left, right );
			if ( mid < left + ( right - left ) / 2 ) {
				stack[sp]     = mid + 1;
				stack[sp + 1] = right;
				right         = mid - 1;
			} else {
				stack[sp]     = left;
				stack[sp + 1] = mid - 1;
				left          = mid + 1;
			}
			sp += 2;
		}
	}
}

int main( ) {
	testSort( 50000000, sort );

	return 0;
}
