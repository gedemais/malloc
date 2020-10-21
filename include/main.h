#ifndef MAIN_H
# define MAIN_H

# define MAX_NAME 64
# define MIN_ALLOC 100

# include "libft.h"

# include <stdio.h>
# include <limits.h>

enum			e_zones
{
	ZONE_TINY,
	ZONE_SMALL,
	ZONE_LARGE,
	ZONE_MAX
};

enum			e_zone_size
{
	ZS_TINY = 16,
	ZS_SMALL = 64,
	ZS_LARGE = INT_MAX
};

typedef struct	s_chunk
{
	int64_t	addr;
	size_t	size;
	int		page;
	int		zone;
}		t_chunk;

typedef struct	s_page
{
	int64_t		addr;
	size_t		blk_size;
	int			frees;
	int			pad;
}				t_page;

typedef struct	s_zone
{
	t_dynarray	pages; // t_page
	t_dynarray	chunks; // t_chunk
	char		name[MAX_NAME];
	size_t		chunk_size;
	int			cpp;
	int			id;
}				t_zone;


void	*malloc(size_t size);
void	free(void *ptr);
void	*realloc(void *ptr, size_t size);

void	show_alloc_mem(void);


t_zone	*g_zones(unsigned int index);
int		page_size(void);
int		add_pages(t_zone *zone, int nb_pages);

int		first_call(bool *first);
void	*zone_dispatch(size_t size);

#endif
