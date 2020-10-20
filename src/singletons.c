#include "main.h"

int		page_size(void)
{
	static int	page_size = 0;

	if (page_size == 0)
		page_size = getpagesize();
	return (page_size);
}

t_zone	*g_zones(unsigned int index)
{
	static t_zone	zones[ZONE_MAX];

	return (&zones[index]);
}