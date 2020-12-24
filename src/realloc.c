/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 18:01:32 by gedemais          #+#    #+#             */
/*   Updated: 2020/12/24 18:04:16 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	*new_allocation(t_zone *zone,
							t_chunk *chunk, int index, size_t size)
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

static bool	is_addr_in_chunk(int64_t ptr)
{
	t_zone			*zone;
	t_chunk			*chunk;
	unsigned int	i;
	int				j;

	i = 0;
	while (i < ZONE_MAX)
	{
		j = 0;
		zone = g_zones(i);
		while (j < zone->chunks.nb_cells)
		{
			chunk = dyacc(&zone->chunks, j);
			if (ptr >= chunk->addr && ptr <= chunk->addr + (int64_t)chunk->size)
				return (true);
			j++;
		}
		i++;
	}
	return (false);
}

void		*realloc(void *ptr, size_t size)
{
	t_zone	*zone;
	t_chunk	*chunk;
	int		index;

	if (*zone_init(false) == false && first_call(NULL))
		return (NULL);
	if (size == 0)
		free(ptr);
	if (ptr == NULL || !(chunk = find_chunk(ptr, &index, &zone)))
		return (is_addr_in_chunk((int64_t)ptr) ? NULL : addr_not_found(size));
	if (size < zone->chunk_size || size > zone->chunk_size)
		return (new_allocation(zone, chunk, index, size));
	else
	{
		chunk->size = size;
		return ((void*)chunk->addr);
	}
}
