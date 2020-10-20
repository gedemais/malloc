#include "libft/libft.h"

int		main(void)
{
	void	*ptr;

	ptr = malloc(10);
	free(NULL);
	ptr = realloc(ptr, 0);
	return (0);
}
