#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int	main(void)
{
	void	*ptr;

	ptr = realloc(NULL, 10);

	assert(ptr != NULL);

	ptr = realloc(ptr, 64);

	assert(ptr != NULL);

	ptr = realloc((void*)((size_t)ptr + 10), 128);

	assert(ptr == NULL);
	return (0);
}
