/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 10:06:00 by gedemais          #+#    #+#             */
/*   Updated: 2021/05/08 09:34:44 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_convert_base(char *res, size_t val, char *base_to)
{
	size_t		len_base;
	int			i;

	len_base = ft_strlen(base_to);
	i = 0;
	if (val)
		while (val > 0)
		{
			res[i] = base_to[val % len_base];
			val /= len_base;
			++i;
		}
	else
		res[i++] = base_to[0];
	res[i] = '\0';
	ft_strrev(res);
}
