#include "main.h"
#include "assert.h"

int		main(void)
{
	void	*ptr;
	t_dynarray	array;
	int		range = 100;

	init_dynarray(&array, sizeof(void*), range);
	for (int i = 0; i < range; i++)
	{
		ptr = malloc(16);
		push_dynarray(&array, &ptr, false);
	}
	show_alloc_mem();
	printf("----------------------\n");
	memcpy(&ptr, dyacc(&array, 10), sizeof(void*));
	free(ptr);
	memcpy(&ptr, dyacc(&array, 11), sizeof(void*));
	free(ptr);
	memcpy(&ptr, dyacc(&array, 12), sizeof(void*));
	free(ptr);
	show_alloc_mem();
	printf("----------------------\n");
	*debug() = true;
	ptr = malloc(rand() % 100);
	show_alloc_mem();
	printf("----------------------\n");
	return (0);
}
