#include <stdlib.h>
#include <string.h>
#include "../includes/head.h"

void	print(char *s)
{
	write(1, s, strlen(s));
}

int		main()
{
	char	*addr;

	addr = (char*)malloc(16);
	free(NULL);
	free((void*)addr + 5);
	if (realloc((void*)addr + 5, 10) == NULL)
		print("Bonjours\n");
	return (0);
}