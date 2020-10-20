#include "main.h"

void	*malloc(size_t size)
{
	static bool	first = true;

	if (first && first_call(&first))
		return (NULL);
	printf("%s\n", __FUNCTION__);
	(void)size;
	return (NULL);
}
