/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_call.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 17:56:01 by gedemais          #+#    #+#             */
/*   Updated: 2021/06/24 13:59:29 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int			add_pages(t_zone *zone, int nb_pages)
{
	t_page	new;
	int		i;

	i = 0;
	while (i < nb_pages)
	{
		if (!(new.addr = (int64_t)alloc_content((size_t)page_size())))
			return (-1);
		new.frees = zone->cpp;
		new.blk_size = page_size();
		if (push_dynarray(&zone->pages, &new, false))
			return (-1);
		i++;
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

int			first_call(void)
{
	const char		*names[ZONE_MAX] = {"TINY", "SMALL", "LARGE"};
	const size_t	sizes[ZONE_MAX] = {ZS_TINY, ZS_SMALL, ZS_LARGE};
	t_zone			*zone;
	unsigned int	i;

	i = 0;
	while (i < ZONE_MAX)
	{
		zone = g_zones(i);
		ft_strcpy(zone->name, names[i]);
		zone->id = (int)i;
		zone->chunk_size = sizes[i];
		zone->cpp = page_size() / (int)zone->chunk_size;
		if (allocate_zone_data(zone, (i == ZONE_LARGE)))
			return (-1);
		i++;
	}
	*zone_init() = true;
	return (0);
}
