#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

static void my_init_hook();
static void *my_malloc_hook(size_t, const void *);
static void my_free_hook(void *, const void *);

int main()
{
	my_init_hook();

	return(0);
}

static void my_init_hook()
{
	old_malloc_hook = __malloc_hook;
	old_free_hook = __free_hook;
	__malloc_hook = my_malloc_hook;
	__free_hook = my_free_hook;
}

static void * my_malloc_hook(size_t size, const void *caller)
{
	void *result;
	__malloc_hook = old_malloc_hook;
	__free_hook = old_free_hook;

	result = malloc(size);

	old_malloc_hook = __malloc_hook;
	old_free_hook = __free_hook;

	printf("malloc (%u) returns %p\n", (unsigned int)size, result);

	__malloc_hook = my_malloc_hook;
	__free_hook = my_free_hook;
	return(result);
}

static void my_free_hook(void *ptr, const void *caller)
{
	__malloc_hook = old_malloc_hook;
	__free_hook = old_free_hook;

	free(ptr);

	old_malloc_hook = __malloc_hook;
	old_free_hook = __free_hook;

	printf("freed pointer %p\n", ptr);

	__malloc_hook = my_malloc_hook;
	__free_hook = my_free_hook;
}
