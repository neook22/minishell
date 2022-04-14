#include "exec.h"
#include "tree.h"
#include "built_ins.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(int ac, char **av, char **envp)
{
	t_tree	*t;
	t_env	env;
	char	*line;
	char	*line_save;
	int		ret;

	if (ac != 1)
		return (EXIT_FAILURE);
	
	(void)av;
	ft_create_env(&env, envp);
	// SHLVL thingy
	line = readline("schnell-1.1$ ");
	while (line)
	{
		line_save = line;
		t = ft_tree_of_line(&line);
		ret = ft_exec(t, &env);
		free(line_save);
		line = readline("schnell-1.1$ ");
	}
	return (ret);
}