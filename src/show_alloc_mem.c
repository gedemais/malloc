#include "main.h"

static int	addresses_sort_func(void *cell_a, void *cell_b)
{
	const t_chunk	*a = cell_a;
	const t_chunk	*b = cell_b;
	int64_t			offset;

	offset = a->addr - b->addr;
	if (offset != 0)
		return (offset < 0 ? -1 : 1);
	return (0);
}

static void	print_zone_title(t_zone *zone)
{
//	ft_putstr(zone->name);
//	ft_putstr(" : ");
//	fflush(stdout);
	printf("ZONE %s : %p\n", zone->name, zone->pages.c);

	printf("%d pages, %d chunks (addr | frees | blk_size) :\n", zone->pages.nb_cells, zone->chunks.nb_cells);
}

static void	print_zone_chunks(t_zone *zone, int *total)
{
	t_dynarray	dump;
	t_chunk		*chunk;

	if (dynarray_dump(&zone->chunks, &dump))
		return ;
	sort_dynarray(&dump, addresses_sort_func);
	for (int i = 0; i < dump.nb_cells; i++)
	{
		chunk = dyacc(&dump, i);
		*total += chunk->size;
		printf("%p - %p : %zu octets\n", (void*)chunk->addr, (void*)(chunk->addr + (int64_t)chunk->size), chunk->size);
	}
	free_dynarray(&dump);
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
