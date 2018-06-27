/*
 * Example of allocation space for an obstack and initialize it
 */

#include <stdlib.h>
#include <stdio.h>
#include <obstack.h>

#define obstack_chunk_alloc xmalloc
#define obstack_chunk_free free

void * xmalloc(size_t size_struct)
{
	void *ptr = (void *) malloc(size_struct);
	if(!ptr)
	{
		printf("Allocation of %ld is failed", size_struct);
		exit(EXIT_FAILURE);
	}
	return(ptr);
}

static struct obstack my_obstack;

struct obstack * my_obstack_init()
{
	struct obstack *my_obstack_ptr = (struct obstack *) xmalloc(sizeof(struct obstack));
	return(my_obstack_ptr);
}

int main()
{
	obstack_init(&my_obstack);

	obstack_init(my_obstack_init());

	exit(EXIT_SUCCESS);
}
