#include <stdio.h>
#include "vars.h"
#include "utils.h"

int main(int ac, char **av, char **ev)
{
	char **expanded;

	if (ac == 1)
	{
		dprintf(2, "plz provide at least 1 arg");
		return (-1);
	}
	expanded = ft_expand_all_vars(av + 1, ev);
	for (int i = 0; expanded[i]; ++i)
		printf("%s\n", expanded[i]);
	ft_free_strtab(expanded);
	return (0);
}
