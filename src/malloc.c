/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 18:01:17 by gedemais          #+#    #+#             */
/*   Updated: 2021/06/23 22:15:17 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	*malloc(size_t size)
{
	if (*zone_init() == false && first_call())
		return (NULL);
	return (zone_dispatch(size));
}
