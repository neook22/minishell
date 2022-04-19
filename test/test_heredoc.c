#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "heredoc.h"
#include <sys/types.h>
#include <sys/wait.h>

int main(int ac, char **av)
{
	if (ac == 1)
		return (1);
	ac--; av++;
	int *fds = malloc(sizeof(int) * ac);
	for (int i = 0; i < ac; ++i)
		fds[i] = ft_add_hdoc(strdup(av[i]));
	ft_hdoc_readall();
	printf("read all\n");
	for (int i = 0; i < ac; ++i)
	{
		if (fork() == 0)
		{
			dup2(fds[i], 0);
			printf("pre cat (%d)\n", i);
			execlp("cat", "cat", "-e", NULL);
			printf("bah\n");
		}
		else 
		{
			printf ("waiting\n");
			wait(NULL);
		}
	}
//	return (2);
	ft_hdoc_closeall();
	free(fds);
	return (0);
}
			



