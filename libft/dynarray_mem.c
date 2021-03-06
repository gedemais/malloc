/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynarray_mem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 18:04:09 by gedemais          #+#    #+#             */
/*   Updated: 2021/06/18 17:39:35 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*alloc_content(size_t size)
{
	int			pagesize;
	size_t		new;
	void		*ptr;

	new = 1;
	pagesize = getpagesize();
	while (new < size)
		new += (size_t)pagesize;
	ptr = mmap(NULL, new,
		PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
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
	munmap(arr->tmp, (size_t)prev_size);
	if (!(tmp = alloc_content((size_t)arr->byte_size))
		|| !(arr->tmp = alloc_content((size_t)arr->byte_size)))
		return (-1);
	ft_memcpy(tmp, arr->c, (size_t)prev_size);
	munmap(arr->c, (size_t)prev_size);
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

int		dynarray_dump(t_dynarray *array, t_dynarray *dump)
{
	ft_memcpy(dump, array, sizeof(t_dynarray));
	if (!(dump->c = alloc_content((size_t)dump->byte_size))
		|| !(dump->tmp = alloc_content((size_t)dump->byte_size)))
		return (-1);
	ft_memcpy(dump->c, array->c, (size_t)dump->byte_size);
	return (0);
}
