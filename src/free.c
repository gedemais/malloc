#include "main.h"

static unsigned int	detect_zone(void *ptr)
{
	t_zone	*zone;
	t_page	*page;

	for (unsigned int i = 0; i < ZONE_LARGE; i++)
	{
		zone = g_zones(i);
		for (int j = 0; j < zone->pages.nb_cells; j++)
		{
			page = dyacc(&zone->pages, j);
			if (ptr >= (void*)page->addr && ptr < (void*)((size_t)page->addr + page->blk_size))
				return (i);
		}
	}
	return (ZONE_LARGE);
}

t_chunk		*find_chunk(void *ptr, int *index, t_zone **z)
{
	t_zone	*zone;
	t_chunk	*chunk;

	if (!(zone = g_zones(detect_zone(ptr))))
		return (NULL);
	for (int j = 0; j < zone->chunks.nb_cells; j++)
	{
		chunk = dyacc(&zone->chunks, j);
		if (chunk->zone == zone->id && chunk->addr == (int64_t)ptr)
		{
			*z = zone;
			*index = j;
			return (chunk);
		}
	}
	return (NULL);
}

void	free_chunk(t_zone *zone, t_chunk *chunk, int index)
{
	t_page	*page;

	if (zone->id != ZONE_LARGE)
	{
		page = dyacc(&zone->pages, chunk->page);
		page->frees++;
	}
	else
		munmap((void*)chunk->addr, chunk->size);
	extract_dynarray(&zone->chunks, index);
}

void	free(void *ptr)
{
	t_chunk	*chunk;
	t_zone	*zone;
	int		index;

	if (*zone_init(false) == false)
		return ;
	if ((chunk = find_chunk(ptr, &index, &zone)))
	{
		free_chunk(zone, chunk, index);
		return ;
	}
	printf("failed ! %p\n", ptr);
}
