/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 18:01:17 by gedemais          #+#    #+#             */
/*   Updated: 2020/12/24 18:01:19 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	*malloc(size_t size)
{
	static bool	first = true;

	if (first && first_call(&first))
		return (NULL);
	return (zone_dispatch(size));
}
