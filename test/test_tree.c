#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

void print_tree(t_tree *t)
{
	char * const ops[9] = {"|", "&&", "||", "cmd", "(", ")", "undef"};

	printf("%s :", ops[t->op]);
	if (t->op == CMD && t->args)
	{
		for (int i = 0; t->args[i]; i++)
			printf("'%s', ", t->args[i]);
	}
	printf("\nredirs: ");
	if (t->redirs)
	{
		for (int i = 0; t->redirs[i]; i++)
			printf("(%d '%s') ", t->redirs[i]->fd, t->redirs[i]->filename);
	}
	printf("\n\n");
	if (t->op != CMD)
	{
		print_tree(t->l);
		print_tree(t->r);
	}
}
int main(int ac, char **av)
{
	if (ac != 2)
		return (-1);
	t_tree *t = ft_tree_of_line(av + 1);
	printf("*****************  PREFIX TREE ****************\n");
	print_tree(t);
	return (0);
}
