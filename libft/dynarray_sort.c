#include "dynarray.h"
#include <stdio.h>

bool	is_dynarray_sort(t_dynarray *array, int (*compare)(void*, void*))
{
	int		i;

	i = 0;
	while (i < array->nb_cells - 1)
	{
		if (compare(dyacc(array, i), dyacc(array, i + 1)) > 0)
			return (false);
		i++;
	}
	return (true);
}

void	sort_dynarray(t_dynarray *array, int (*compare)(void*, void*))
{
	int		smallest_idx;
	int		cmp;
	int		i;
	int		j;

	i = 0;
	while (i < array->nb_cells)
	{
		j = i;
		smallest_idx = i;
		while (j < array->nb_cells)
		{
			cmp = compare(dyacc(array, smallest_idx), dyacc(array, j)); // compare should always return *i - *j
			if (cmp > 0)
				smallest_idx = j;
			j++;
		}
		if (smallest_idx != i)
			dynarray_swap_cells(array, i, smallest_idx);
		i++;
	}
}
