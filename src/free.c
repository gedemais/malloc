#include "main.h"

t_chunk		*find_chunk(void *ptr, int *index, t_zone **z)
{
	t_chunk	*chunk;
	t_zone	*zone;

	for (unsigned int i = 0; i < ZONE_MAX; i++)
	{
		zone = g_zones(i);
		for (int j = 0; j < zone->chunks.nb_cells; j++)
		{
			chunk = dyacc(&zone->chunks, j);
			if (chunk->addr == (int64_t)ptr)
			{
				*z = zone;
				*index = j;
				return (chunk);
			}
		}
	}
	return (NULL);
}

void	free(void *ptr)
{
	t_chunk	*chunk;
	t_page	*page;
	t_zone	*zone;
	int		index;

	if ((chunk = find_chunk(ptr, &index, &zone)))
	{
		page = dyacc(&zone->pages, chunk->page);
		page->frees++;
		extract_dynarray(&zone->chunks, index);
		return ;
	}
}
