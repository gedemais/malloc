/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynarray.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 18:03:19 by gedemais          #+#    #+#             */
/*   Updated: 2020/12/26 01:01:26 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DYNARRAY_H
# define DYNARRAY_H

# include "libft.h"
# include <stdbool.h>

typedef struct	s_dynarray
{
	void		*c;
	void		*tmp;
	int			cell_size;
	int			nb_cells;
	int			byte_size;
	int			pad;
}				t_dynarray;

int				init_dynarray(t_dynarray *arr, int cell_size, int nb_cells);
void			clear_dynarray(t_dynarray *arr);
void			*dyacc(t_dynarray *arr, int index);

void			*alloc_content(size_t size);
int				check_space(t_dynarray *arr);
void			free_dynarray(t_dynarray *arr);

int				pop_dynarray(t_dynarray *arr, bool front);
int				push_dynarray(t_dynarray *arr, void *src, bool back);
int				replace_dynarray_cell(t_dynarray *arr, void *src, int index);
int				insert_dynarray(t_dynarray *arr, void *src, int index);
int				extract_dynarray(t_dynarray *arr, int index);
int				dynarray_swap_cells(t_dynarray *add, int index1, int index2);
void			sort_dynarray(t_dynarray *array, int (*compare)(void*, void*));
bool			is_dynarray_sort(t_dynarray *array, int (*compare)(void*, void*));

#endif
