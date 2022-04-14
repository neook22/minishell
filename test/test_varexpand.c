#include <stdlib.h>
#include <stdio.h>
#include "varexpand.h"

extern char	**environ;

int main(int ac, char **av)
{
	if (ac != 2)
		return (-1);
	char *str = ft_varexpand(av[1], environ);
	printf("%s\n", str);
	free(str);
	return (0);
}
