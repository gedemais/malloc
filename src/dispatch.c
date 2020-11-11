#include "main.h"

static bool	is_chunk_free(t_zone *zone, int page_index, int64_t	head)
{
	t_chunk	*chunk;

	for (int i = 0; i < zone->chunks.nb_cells; i++)
	{
		chunk = dyacc(&zone->chunks, i);
		if (chunk->page == page_index && chunk->addr == head)
			return (false);
	}
	return (true);
}

static void	*place_chunk_in_page(t_zone *zone, t_page *page, int page_index, size_t size)
{
	t_chunk	new;
	int64_t	head;
	int64_t	bound;

	head = page->addr;
	bound = head + (int64_t)page_size();
	while (head < bound)
	{
		if (*debug())
			printf("checking %p...\n", (void*)head);
		if (is_chunk_free(zone, page_index, head))
		{
			if (*debug())
				printf("free !\n");
			new.addr = head;
			new.size = size;
			new.page = page_index;
			new.zone = zone->id;
			if (push_dynarray(&zone->chunks, &new, false))
				return (NULL);
			page->frees--;
			return ((void*)head);
		}
		if (*debug())
			printf("not free !\n");
		head += zone->chunk_size;
	}
	return (NULL);
}

void	*allocate_large_chunk(t_zone *zone, size_t size)
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

void	*allocate_chunk(t_zone *zone, size_t size)
{
	void	*ret = NULL;
	t_page	*page;

	if (zone->id == ZONE_LARGE)
		return (allocate_large_chunk(zone, size));
	for (int i = 0; i < zone->pages.nb_cells; i++)
	{
		page = dyacc(&zone->pages, i);
		if (page->frees > 0)
			return (place_chunk_in_page(zone, page, i, size));
	}
	if (ret == NULL)
	{
		if (add_pages(zone, zone->pages.nb_cells * 2))
			return (NULL);
		return (allocate_chunk(zone, size));
	}
	return (ret);
}

void	*zone_dispatch(size_t size)
{
	const size_t	sizes[ZONE_MAX + 1] = {0, ZS_TINY, ZS_SMALL, ZS_LARGE};

	if (size == 0)
			return (allocate_chunk(g_zones(0), size));
	for (unsigned int i = 0; i < ZONE_MAX; i++)
		if (size > sizes[i] && size <= sizes[i + 1])
			return (allocate_chunk(g_zones(i), size));
	printf("dispatch failed (%zu)\n", size);
	return (NULL);
}
