#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

extern void my_sort(int *, const int);

static void *xmalloc( const int bytes ) {
	void *ptr = malloc( bytes );
	if ( !ptr ) {
		perror( "xmalloc: malloc error" );
		exit( EXIT_FAILURE );
	}
	return ptr;
}

#define rand_int( min, max ) rand( ) % ( max - min + 1 ) + min

static int *get_arr( const int count ) {
	int *arr = (int *)xmalloc( count * sizeof( int ) );

	srand( time( NULL ) );

	for ( int i = 0; i < count; ++i ) arr[i] = rand_int( 1, count - 1 );
	return arr;
}

static void print_arr( const int *arr ) {
	for ( int i = 0; i < 10; ++i ) printf( "%d  ", arr[i] );
}

static double get_time( ) {
	struct timeval tv;
	gettimeofday( &tv, NULL );
	return tv.tv_sec + tv.tv_usec / 1000000.;
}

static void test( const int count ) {
	int *arr = get_arr( count );

	puts( "\nBefore sort:" );
	print_arr( arr );

	double start = 0, end = 0;
	start = get_time( );
	my_sort( arr, count );
	end = get_time( );

	puts( "\nAfter sort:" );
	print_arr( arr );

	double reqTime = end - start;
	printf( "\nSorting took %.4f sec for %d elemets\n", reqTime, count );

	free(arr);
}
