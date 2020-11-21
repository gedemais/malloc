#include "main.h"

static void	*new_allocation(t_zone *zone, t_chunk *chunk, int index, size_t size)
{
	void	*ptr;

	if (!(ptr = malloc(size)))
		return (NULL);
	ft_memcpy(ptr, (void*)chunk->addr, chunk->size);
	free_chunk(zone, chunk, index);
	return (ptr);
}

static void	*addr_not_found(size_t size)
{
	void	*ptr;

	if (!(ptr = malloc(size)))
		return (NULL);
	ft_memset(ptr, 0, size);
	return (ptr);
}

void		*realloc(void *ptr, size_t size)
{
	t_zone	*zone;
	t_chunk	*chunk;
	int		index;

	if (*zone_init(false) == false)
		return (NULL);
	if (size == 0)
		free(ptr);
	if (ptr == NULL || !(chunk = find_chunk(ptr, &index, &zone))) // Address not found -> new allocation
		return (addr_not_found(size));
	if (size < zone->chunk_size || size > zone->chunk_size) // Another allocation is needed
		return (new_allocation(zone, chunk, index, size));
	else
	{
		chunk->size = size;
		return ((void*)chunk->addr);
	}
}
