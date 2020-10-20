/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynarray_mem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 18:04:09 by gedemais          #+#    #+#             */
/*   Updated: 2020/10/19 23:33:04 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*alloc_content(size_t size)
{
	void	*ptr;

	ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (ptr == MAP_FAILED)
		return (NULL);
	return (ptr);
}

static int	realloc_content(t_dynarray *arr)
{
	void	*tmp;
	int		prev_size;

	prev_size = arr->byte_size;
	arr->byte_size *= 2;
	munmap(arr->tmp, prev_size);
	if (!(tmp = alloc_content(arr->byte_size))
		|| !(arr->tmp = alloc_content(arr->byte_size)))
		return (-1);
	ft_memcpy(tmp, arr->c, prev_size);
	munmap(arr->c, prev_size);
	arr->c = tmp;
	return (0);
}

int			check_space(t_dynarray *arr)
{
	arr->nb_cells++;
	while (arr->nb_cells * arr->cell_size >= arr->byte_size)
		if (realloc_content(arr))
			return (-1);
	return (0);
}
