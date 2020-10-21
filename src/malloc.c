#include "main.h"

void	*malloc(size_t size)
{
	static bool	first = true;

	if (first && first_call(&first))
		return (NULL);
	return (zone_dispatch(size));
}
