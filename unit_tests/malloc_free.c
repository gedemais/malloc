#include "main.h"
#include <time.h>

int	main(void)
{
	t_dynarray	array;
	void		*ptr;
	int			range = 1000;
	size_t		size;

	srand((unsigned)time(0));
	if (init_dynarray(&array, sizeof(int64_t), range))
		return (-1);
	show_alloc_mem();
	printf("----------------------\n");
	for (int i = 0; i < range; i++)
	{
		size = rand() % ZS_TINY;
		ptr = malloc(size);
		push_dynarray(&array, &ptr, false);

		size = rand() % (ZS_SMALL - ZS_TINY) + ZS_TINY;
		ptr = malloc(size);
		push_dynarray(&array, &ptr, false);

		size = rand() % 1000 + ZS_SMALL;
		ptr = malloc(size);
		push_dynarray(&array, &ptr, false);
	}
	show_alloc_mem();
	printf("----------------------\n");
	int64_t	*addr;
	for (int i = 0; i < array.nb_cells; i++)
	{
		addr = dyacc(&array, i);
		free((void*)(*addr));
	}
	show_alloc_mem();
	printf("----------------------\n");
	return (0);
}
