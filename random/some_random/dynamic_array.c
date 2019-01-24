/* Dynamic array
 * Try to create kind of dynamic array as stack in STL of C++
 */

#include <stdio.h>
#include <stdlib.h>

static inline int get_random( int min, int max ) {
	return ( rand( ) % ( max + 1 - min ) + min );
}

typedef struct {
	size_t size;
	size_t capacity;
	int *  array;
} darray;

darray *construct_darray( ) {
	darray *new_arr = (darray *)malloc( sizeof( darray ) );
	if ( !new_arr ) exit( EXIT_FAILURE );
	new_arr->size     = 0;
	new_arr->capacity = 2;
	new_arr->array    = (int *)malloc( sizeof( int ) * new_arr->capacity );

	return new_arr;
}

static void darray_push_back( darray *ar, int value ) {
	if ( ar->capacity - ar->size <= 1 ) {
		ar->capacity *= 2;
		ar->array = (int *)realloc( ar->array, sizeof( int ) * ar->capacity );
	}
	ar->array[ar->size] = value;
	++( ar->size );
}

static inline void darray_show_all( darray *ar ) {
	for ( int i = 0; i < ar->size; ++i ) printf( "%d\n", ar->array[i] );
}

int main( ) {
	darray *new_array = construct_darray( );

	for ( int i = 0; i < 1000; ++i )
		darray_push_back( new_array, get_random( 10, 1000 ) );

	darray_show_all( new_array );

	printf( "size:     %llu\n"
	        "capacity: %llu\n",
	        new_array->size, new_array->capacity );

	return 0;
}