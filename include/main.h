/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 00:02:04 by gedemais          #+#    #+#             */
/*   Updated: 2021/06/24 13:44:46 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# define MAX_NAME 64
# define MIN_ALLOC 100

# include "libft.h"

# include <stdio.h>
# include <sys/resource.h>
# include <limits.h>
# include <assert.h>

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
}				t_chunk;

typedef struct	s_page
{
	int64_t		addr;
	size_t		blk_size;
	int			frees;
	int			pad;
}				t_page;

typedef struct	s_zone
{
	t_dynarray	pages;
	t_dynarray	chunks;
	char		name[MAX_NAME];
	size_t		chunk_size;
	int			cpp;
	int			id;
}				t_zone;

void			*malloc(size_t size);
void			free(void *ptr);
void			*realloc(void *ptr, size_t size);

void			show_alloc_mem(void);

t_zone			*g_zones(unsigned int index);
int				page_size(void);
int				add_pages(t_zone *zone, int nb_pages);

int				first_call(void);
void			*zone_dispatch(size_t size);
void			*allocate_chunk(t_zone *zone, size_t size);
void			*allocate_large_chunk(t_zone *zone, size_t size);
t_chunk			*find_chunk(void *ptr, int *index, t_zone **z);
void			free_chunk(t_zone *zone, t_chunk *chunk, int index);

bool			*zone_init(void);
bool			*debug(void);

#endif
