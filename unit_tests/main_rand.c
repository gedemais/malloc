/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_rand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 15:01:26 by arobion           #+#    #+#             */
/*   Updated: 2020/11/03 23:22:09 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#define SIZE_TAB	2
#define NB_TEST		1000000
#define SIZE_ALLOC	16
#define ERROR	-1
#define SUCCESS	0

int		size_tab[SIZE_TAB];

int			get_size_alloc()
{
	return (rand() % (1 << 16));
}

void	ft_putnbr(int nb, int b)
{
	char	*base = "0123456789abcdef";

	if (nb == 0)
	{
		write(1, "0", 1);
		return ;
	}
	if (nb != 0)
	{
		ft_putnbr(nb / b, b);
		write(1, base[nb % b], 1);
	}
}

void		test_write2(void *mem, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
		((char*)mem)[i++] = (uint8_t)size;
}

void		test_read2(void *mem, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
		if (((uint8_t*)mem)[i++] != (uint8_t)size)
		{
			write(1, "ERROR USER MEMORY HAS BEEN ALTERED\n", 35);
			break ;
		}
}

# define IN_START		999999999

int8_t		unit_test(char **tab, int index)
{
	int			r;

	r = rand() % SIZE_TAB;
	(void)index;
	test_read2(tab[r], size_tab[r]);
	free(tab[r]);
	size_tab[r] = get_size_alloc();
	ft_putnbr(size_tab[r], 10);
	fflush(stdout);
	if (!(tab[r] = malloc(size_tab[r])))
		return (ERROR);
	test_write2(tab[r], size_tab[r]);
	return (SUCCESS);
}

char		**init(void)
{
	char		**tab;
	int			i;

	write(1, "v", 1);
	if (!(tab = malloc(sizeof(void *) * SIZE_TAB)))
		return (NULL);
	write(1, "^", 1);
	i = 0;
	write(1, "\n", 1);
	while (i < SIZE_TAB)
	{
		write(1, "x", 1);
		if (!(tab[i] = malloc(SIZE_ALLOC)))
			return (NULL);
		size_tab[i] = SIZE_ALLOC;
		test_write2(tab[i], size_tab[i]);
		i++;
	}
	return (tab);
}

void		finish(char **tab)
{
	int			i;
	i = 0;
	while (i < SIZE_TAB)
	{
		write(1, "o", 1);
		free(tab[i]);
		i++;
	}
	write(1, "e", 1);
	free(tab);
}

int			main(int ac, char **av)
{
	char		**tab;
	int			i;
	int			nb_tests = NB_TEST;

	if (ac > 1)
		nb_tests = atoi(av[1]);
	else
		nb_tests = NB_TEST;

	if (ac > 2)
		srand(atoi(av[2]));
	else
		srand(17);

	write(1, "Begin tests\n", 12);
	printf("SIZE TAB = %d\n", SIZE_TAB);
	if (!(tab = init()))
		return (10);
	write(1, "\n", 1);
	i = -1;
	// while (++i < NB_TEST)
	while (++i < nb_tests)
	{
		write(1, "?", 1);
		if (0 == i % 1000)
			printf("%d\n", i);
		if (ERROR == unit_test(tab, i))
			return (10);
		// if (i % 100000 == 0)
		// {
		// 	print_malloc_mem();
		// 	show_alloc_mem();
		// }
	}
	write(1, "\n", 1);
	finish(tab);

	write(1, "\nEnd tests\n", 11);
	return (0);
}
