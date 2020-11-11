#include "main.h"

int			add_pages(t_zone *zone, int nb_pages)
{
	t_page	new;
	void	*head;
	void	*blk;

	if (!(blk = alloc_content((size_t)nb_pages * (size_t)page_size())))
		return (-1);
	head = blk;
	for (int i = 0; i < nb_pages; i++)
	{
		new.addr = (int64_t)head;
		new.frees = zone->cpp;
		new.blk_size = (i == 0) ? (size_t)nb_pages * (size_t)page_size() : 0;
		if (push_dynarray(&zone->pages, &new, false))
			return (-1);
		head = (void*)((size_t)head + (size_t)page_size());
	}
	return (0);
}

static int	allocate_zone_data(t_zone *zone, bool is_large)
{
	int	nb_pages;

	nb_pages = is_large ? MIN_ALLOC : MIN_ALLOC / zone->cpp + 1;
	if (init_dynarray(&zone->pages, sizeof(t_page), nb_pages))
		return (-1);
	if (!is_large && add_pages(zone, nb_pages))
		return (-1);
	if (init_dynarray(&zone->chunks, sizeof(t_chunk), MIN_ALLOC))
		return (-1);
	return (0);
}

int			first_call(bool *first)
{
	const char		*names[ZONE_MAX] = {"TINY", "SMALL", "LARGE"};
	const size_t	sizes[ZONE_MAX] = {ZS_TINY, ZS_SMALL, ZS_LARGE};
	t_zone			*zone;

	for (unsigned int i = 0; i < ZONE_MAX; i++)
	{
		zone = g_zones(i);
		ft_strcpy(zone->name, names[i]);
		zone->id = (int)i;
		zone->chunk_size = sizes[i];
		zone->cpp = page_size() / (int)zone->chunk_size;
		if (allocate_zone_data(zone, (i == ZONE_LARGE)))
			return (-1);
	}
	*first = false;
	zone_init(true);
	return (0);
}
