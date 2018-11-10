/*
 * Use multithreading for quicksort + insertion sort
 */

#include "common.c"

#include <pthread.h>

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

#define MAX_THREADS 8
int n_threads;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  cond  = PTHREAD_COND_INITIALIZER;

void *sort_thr( void *arg ) {
	int **stack = (int **)arg;
	int   sp    = 0;
	int * left = stack[sp], *right = stack[sp + 1];

	for ( ;; ) {
		if ( right - left < 50 ) {
			insertion_sort( left, right );
			if ( !sp ) break;
			sp -= 2;
			left  = stack[sp];
			right = stack[sp + 1];
		} else {
			int *l, *r, *mid = partition( left, right );

			if ( mid < left + ( right - left ) / 2 ) {
				l     = mid + 1;
				r     = right;
				right = mid - 1;
			} else {
				l    = left;
				r    = mid - 1;
				left = mid + 1;
			}
			if ( r - l > 1000000 && n_threads < MAX_THREADS ) {
				pthread_t thread;
				int **    new_stack = (int **)xmalloc( 64 * sizeof( int * ) );
				new_stack[0]        = l;
				new_stack[1]        = r;

				pthread_mutex_lock( &mutex );
				++n_threads;

				pthread_mutex_unlock( &mutex );
				pthread_create( &thread, NULL, sort_thr, new_stack );
			} else {
				stack[sp]     = l;
				stack[sp + 1] = r;
				sp += 2;
			}
		}
	}

	free(stack);
	pthread_mutex_lock(&mutex);
	--n_threads;
	if(!n_threads) pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mutex);

	return NULL;
}

void sort( int *arr, int count ) {
	pthread_t thread;
	int **    stack = (int **)xmalloc( 64 * sizeof( int * ) );

	stack[0]  = arr;
	stack[1]  = arr + count - 1;
	n_threads = 1;
	pthread_create( &thread, NULL, sort_thr, stack );

	pthread_mutex_lock( &mutex );
	pthread_cond_wait( &cond, &mutex );
	pthread_mutex_unlock( &mutex );

	free( stack );
}

int main( ) {
	testSort( 50000000, sort );
	return 0;
}
