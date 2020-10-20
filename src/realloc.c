#include "main.h"

void	*realloc(void *ptr, size_t size)
{
	printf("%s\n", __FUNCTION__);
	(void)ptr;
	(void)size;
	return (NULL);
}
