#ifndef MAIN_H
# define MAIN_H

# define MAX_NAME 64
# define MIN_ALLOC 100

# include "libft.h"

# include <stdio.h>
# include <limits.h>
# include <assert.h>

# define PUT printf("There\n");
# define PUT1 printf("There1\n");
# define PUT2 printf("There2\n");
# define PUT3 printf("There3\n");
# define PUT4 printf("There4\n");
# define PUT5 printf("There5\n");
# define PUT6 printf("There6\n");
# define PUT7 printf("There7\n");
# define PUT8 printf("There8\n");
# define PUT9 printf("There9\n");

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
	ZS_SMALL = 1024,
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
void	*allocate_chunk(t_zone *zone, size_t size);
void	*allocate_large_chunk(t_zone *zone, size_t size);
t_chunk	*find_chunk(void *ptr, int *index, t_zone **z);
void	free_chunk(t_zone *zone, t_chunk *chunk, int index);

bool	*zone_init(bool up);
bool	*debug(void);

#endif
