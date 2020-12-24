/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 17:50:46 by gedemais          #+#    #+#             */
/*   Updated: 2020/12/24 17:55:45 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static bool	is_chunk_free(t_zone *zone, int page_index, int64_t head)
{
	t_chunk	*chunk;
	int		i;

	i = 0;
	while (i < zone->chunks.nb_cells)
	{
		chunk = dyacc(&zone->chunks, i);
		if (chunk->page == page_index && chunk->addr == head)
			return (false);
		i++;
	}
	return (true);
}

static void	*place_chunk_in_page(t_zone *zone,
									t_page *page, int page_index, size_t size)
{
	t_chunk	new;
	int64_t	head;
	int64_t	bound;

	head = page->addr;
	bound = head + (int64_t)page_size();
	while (head < bound)
	{
		if (is_chunk_free(zone, page_index, head))
		{
			new.addr = head;
			new.size = size;
			new.page = page_index;
			new.zone = zone->id;
			if (push_dynarray(&zone->chunks, &new, false))
				return (NULL);
			page->frees--;
			return ((void*)head);
		}
		head += zone->chunk_size;
	}
	return (NULL);
}

void		*allocate_large_chunk(t_zone *zone, size_t size)
{
	t_chunk	new;
	void	*addr;

	if (!(addr = alloc_content(size)))
		return (NULL);
	new.addr = (int64_t)addr;
	new.size = size;
	new.page = zone->chunks.nb_cells;
	new.zone = zone->id;
	if (push_dynarray(&zone->chunks, &new, false))
		return (NULL);
	return (addr);
}

void		*allocate_chunk(t_zone *zone, size_t size)
{
	t_page	*page;
	void	*ret;
	int		i;

	i = 0;
	ret = NULL;
	if (zone->id == ZONE_LARGE)
		return (allocate_large_chunk(zone, size));
	while (i < zone->pages.nb_cells)
	{
		page = dyacc(&zone->pages, i);
		if (page->frees > 0)
			return (place_chunk_in_page(zone, page, i, size));
		i++;
	}
	if (ret == NULL)
	{
		if (add_pages(zone, zone->pages.nb_cells * 2))
			return (NULL);
		return (allocate_chunk(zone, size));
	}
	return (ret);
}

void		*zone_dispatch(size_t size)
{
	const size_t	sizes[ZONE_MAX + 1] = {0, ZS_TINY, ZS_SMALL, ZS_LARGE};
	unsigned int	i;

	i = 0;
	if (size == 0)
		return (allocate_chunk(g_zones(0), size));
	while (i < ZONE_MAX)
	{
		if (size > sizes[i] && size <= sizes[i + 1])
			return (allocate_chunk(g_zones(i), size));
		i++;
	}
	return (NULL);
}
