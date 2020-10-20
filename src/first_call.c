#include "main.h"

int			add_pages(t_zone *zone)
{
	(void)zone;
	return (0);
}

static int	allocate_zone_data(t_zone *zone)
{
	int		need;

	need = ((int)zone->chunk_size * MIN_ALLOC) / page_size() + 1;
	if (init_dynarray(&zone->pages, sizeof(t_page), need)
		|| add_pages(zone))
		return (-1);
	if (init_dynarray(&zone->chunks, sizeof(t_chunk), MIN_ALLOC))
		return (-1);
	return (0);
}

int			first_call(bool *first)
{
	const char		*names[ZONE_MAX] = {"TINY", "SMALL", "MIDDLE", "BIG", "LARGE"};
	const size_t	sizes[ZONE_MAX] = {ZS_TINY, ZS_SMALL, ZS_MIDDLE, ZS_BIG, ZS_LARGE};
	t_zone			*zone;

	for (unsigned int i = 0; i < ZONE_MAX; i++)
	{
		zone = g_zones(i);
		ft_strcpy(zone->name, names[i]);
		zone->chunk_size = sizes[i];
		if (allocate_zone_data(zone))
			return (-1);
	}
	*first = false;
	return (0);
}
