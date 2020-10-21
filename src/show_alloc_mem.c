#include "main.h"

static void	print_zone_title(t_zone *zone)
{
//	ft_putstr(zone->name);
//	ft_putstr(" : ");
//	fflush(stdout);
	printf("ZONE %s : %p\n", zone->name, zone->pages.c);

	t_page	*page;
	printf("%d pages, %d chunks (addr | frees | blk_size) :\n", zone->pages.nb_cells, zone->chunks.nb_cells);
	for (int i = 0; i < zone->pages.nb_cells; i++)
	{
		page = dyacc(&zone->pages, i);
		printf("%p | %d | %zu\n", (void*)page->addr, page->frees, page->blk_size);
	}
}

static void	print_zone_chunks(t_zone *zone, int *total)
{
	t_chunk	*chunk;

	for (int i = 0; i < zone->chunks.nb_cells; i++)
	{
		chunk = dyacc(&zone->chunks, i);
		*total += chunk->size;
		printf("%p - %p : %zu octets\n", (void*)chunk->addr, (void*)(chunk->addr + (int64_t)chunk->size), chunk->size);
	}
}

void	show_alloc_mem(void)
{
	t_zone	*zone;
	int		total = 0;

	for (unsigned int i = 0; i < ZONE_MAX; i++)
	{
		zone = g_zones(i);
		print_zone_title(zone);
		print_zone_chunks(zone, &total);
	}
}
