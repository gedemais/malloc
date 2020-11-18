#include "main.h"

void	*realloc(void *ptr, size_t size)
{
	void	*ret;
	t_zone	*zone;
	t_chunk	*chunk;
	int		index;

	if (*zone_init(false) == false)
		return (NULL);
	if (size == 0)
		free(ptr);
	if (ptr == NULL || !(chunk = find_chunk(ptr, &index, &zone)))
	{
		if (!(ret = malloc(size)))
			return (NULL);
		ft_memset(ret, 0, size);
		return (ret);
	}
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
