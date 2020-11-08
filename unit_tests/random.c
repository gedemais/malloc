#include "main.h"
#include <time.h>
#include <assert.h>

static void	realloc_ptr(t_dynarray *array)
{
	void	*ptr;
	int64_t	addr;
	int		index;

	index = rand() % array->nb_cells;
	ft_memcpy(&addr, dyacc(array, index), sizeof(void*));
	ptr = (void*)addr;
	assert(ptr = realloc(ptr, rand() % 100));
	ft_memcpy(dyacc(array, index), &ptr, sizeof(void*));
}

static void	free_ptr(t_dynarray *array)
{
	void	*ptr;
	int64_t	addr;
	int		index;

	index = rand() % array->nb_cells;
	ft_memcpy(&addr, dyacc(array, index), sizeof(void*));
	ptr = (void*)addr;
	free(ptr);
	extract_dynarray(array, index);
}

int	m = 0;
int	r = 0;
int	f = 0;

static int	do_stuff(t_dynarray *array, int id)
{
	static bool	first = true;
	void	*ptr;

	if (id == 0 && (array->nb_cells > 0 || first))// malloc
	{
		first = false;
		assert(ptr = malloc(rand() % 100));
		m++;
		return (push_dynarray(array, &ptr, false));
	}
	if (id == 1 && (array->nb_cells > 0 || first))// realloc
	{
		first = false;
		r++;
		realloc_ptr(array);
		return (0);
	}
	if (id == 2 && (array->nb_cells > 0 || first))// free
	{
		f++;
		first = false;
		free_ptr(array);
		return (0);
	}
	return (0);
}

static void	check_nb_allocations(void)
{
	t_zone	*zone;
	int		nb_chunks = 0;

	for (int i = 0; i < ZONE_MAX; i++)
	{
		zone = g_zones(i);
		nb_chunks += zone->chunks.nb_cells;
	}
	printf("%d\n", nb_chunks);
	printf("%d\n", m - f);
	printf("--------------------\n");
//	printf("%d\n", ((t_zone*)g_zones(ZONE_TINY))->chunks.nb_cells);
//	printf("%d\n", ((t_zone*)g_zones(ZONE_SMALL))->chunks.nb_cells);
//	printf("%d\n", ((t_zone*)g_zones(ZONE_LARGE))->chunks.nb_cells);
	fflush(stdout);
	assert(m - f == nb_chunks);
}

int	main(void)
{
	t_dynarray	array;
	void		*ptr;
	int			range = 100000;
	size_t		size;

	srand((unsigned)time(0));
	if (init_dynarray(&array, sizeof(int64_t), range))
		return (-1);
	show_alloc_mem();
	printf("----------------------\n");
	for (int i = 0; i < range; i++)
		do_stuff(&array, i < (range / 3) ? 0 : rand() % 3);
	show_alloc_mem();
	printf("----------------------\n");
	printf("%d mallocs, %d reallocs, %d frees\n", m, r, f);

	check_nb_allocations();

	for (int i = 0; i < array.nb_cells; i++)
	{
		ft_memcpy(&ptr, dyacc(&array, i), sizeof(void*));
		free(ptr);
	}
	show_alloc_mem();
	return (0);
}
