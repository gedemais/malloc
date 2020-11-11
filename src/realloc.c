#include "main.h"

void	*realloc(void *ptr, size_t size)
{
	t_zone	*zone;
	t_chunk	*chunk;
	int		index;

	if (*zone_init(false) == false)
		return (NULL);
	if (!(chunk = find_chunk(ptr, &index, &zone)))
		return (NULL);
	if (size < zone->chunk_size || size > zone->chunk_size)
	{
		free_chunk(zone, chunk, index);
		return (malloc(size));
	}
	else
	{
		chunk->size = size;
		return ((void*)chunk->addr);
	}
}
