#include "main.h"

void	free(void *ptr)
{
	printf("%s\n", __FUNCTION__);
	(void)ptr;
}
