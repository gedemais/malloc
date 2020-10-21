#include "main.h"

int		main(void)
{
	void	*ptr;

	for (int i = 0; i < 300; i++)
	{
		ptr = malloc(10);
		ptr = malloc(40);
		ptr = malloc(80);
	}
	show_alloc_mem();
	return (0);
}
