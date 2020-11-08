#include "main.h"
#include "assert.h"

int		main(void)
{
	void	*ptr;
	int		range = 100;
	char	zone[10];

	ptr = malloc(10);
	memcpy(zone, ptr, 10);
	show_alloc_mem();
	printf("---------------------\n");

	for (int i = 0; i < range; i++)
		assert((ptr = realloc(ptr, rand() % 100)));

	ptr = realloc(ptr, 10);
	assert(!memcmp(zone, ptr, 10));
	free(ptr);
	show_alloc_mem();
	return (0);
}
