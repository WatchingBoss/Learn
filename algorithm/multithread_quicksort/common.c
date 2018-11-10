#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <sys/time.h>

extern void sort(int *, int);

static void *xmalloc( int bytes ) {
	void *ptr = malloc( bytes );
	if ( !ptr ) {
		perror( "xmalloc: malloc error" );
		exit( EXIT_FAILURE );
	}
	return ptr;
}

static inline int randomInt(int min, int max){
	return rand() % (max - min + 1) + min;
}

static int *fillArray( int count) {
	int *arr = (int *)xmalloc(count * sizeof(int));

	srand(time(NULL));

	for(int i = 0; i < count; ++i)
		arr[i] = randomInt(1, count - 1);

	return arr;
}

static void print_arr(int *arr){
	for(int i = 0; i < 10; ++i)
		printf("%d  ", arr[i]);
	printf("\n\n");
}

static double getTime(){
	static double t;
	struct timeval tv;
	gettimeofday(&tv, NULL);
	double h = t;
	t = tv.tv_sec + tv.tv_usec / 1000000.;
	return t - h;
}

static void testSort(int count, void (*func)(int*, int)){
	int *arr = fillArray(count);

	puts("Before sorting:");
	print_arr(arr);

	getTime();
	func(arr, count);

	puts("After sorting:");
	print_arr(arr);

	double req_time = getTime();

	printf("Sorting %d numbers took %.3f seconds\n", count, req_time);

	free(arr);
}
