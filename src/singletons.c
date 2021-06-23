/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singletons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 18:04:37 by gedemais          #+#    #+#             */
/*   Updated: 2021/06/23 17:17:32 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		page_size(void)
{
	static int	page_size = 0;

	if (page_size == 0)
		page_size = getpagesize();
	return (page_size);
}

t_zone	*g_zones(unsigned int index)
{
	static t_zone	zones[ZONE_MAX];

	if (index >= ZONE_MAX)
		return (NULL);
	return (&zones[index]);
}

bool	*zone_init(void)
{
	static bool	var = false;

	return (&var);
}

bool	*debug(void)
{
	static bool	value = false;

	return (&value);
}
