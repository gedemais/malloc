#include "main.h"
#include "assert.h"

int		main(void)
{
	void	*ptr;

	for (int i = 0; i < 3000; i++)
	{
		ptr = malloc(10);
		assert(ptr);
		free(ptr);

		ptr = malloc(40);
		assert(ptr);
		free(ptr);

		ptr = malloc(80);
		assert(ptr);
		free(ptr);
	}
	show_alloc_mem();
	return (0);
}
