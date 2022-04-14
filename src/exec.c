#include "exec.h"

int	ft_pipe(t_tree *l, t_tree *r, t_env *env)
{
	int outs[2];
	int	pid1;
	int	pid2;

	if (pipe(outs) < 0)
		return (1);
	pid1 = fork();
	if (pid1 == 0)
	{
		if (dup2(outs[1], 1) < 0)
			return (1);
		close(outs[0]);
		close(outs[1]);
		exit(ft_exec(l, env));
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		if (dup2(outs[0], 0) < 0)
			return (1);
		close(outs[0]);
		close(outs[1]);
		exit(ft_exec(r, env));
	}
	close(outs[0]);
	close(outs[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}

/* 
 * AND : si vrai -> fais le 2e, output = 2e
 *	 si faux -> skip le 2e et output = faux
*/
int ft_and(t_tree *l, t_tree *r, t_env *env)
{
	int ret_l;
	int ret_r;

	ret_l = ft_exec(l, env);
	if (ret_l == 0)
	{
		ret_r = ft_exec(r, env);
		return (ret_r);
	}
	return (1);
}

/*
 * OR :  si vrai -> skip le 2e, output = vrai
 *       si faux -> fais le 2e et output = 2e
*/
int	ft_or(t_tree *l, t_tree *r, t_env *env)
{
	int ret;

	ret = ft_exec(l, env);
	if (ret == 0)
		return (0);
	ret = ft_exec(r, env);
	return (ret);
}

int	ft_exec_command(char **args, t_env *env)
{
	char	*path_command;
	int 	pid;
	int		ret;
	int		waitstatus;
	
	ret = ft_dispatcher(args[0], args+1, env);
	if (ret != E_NOT_BUILT_IN)
		return (ret);
	path_command = ft_get_path(args[0], env->e_tab);
	if (!path_command)
		return (1);
	pid = fork();
	if (pid == 0)
	{
		/* potentials closes */
		execve(path_command, args, env->e_tab);
		perror(path_command);
		exit(1);
	}
	wait(&waitstatus);
	ret = WEXITSTATUS(waitstatus);
	return (ret);
}

int	ft_redirs(t_redir **redirs)
{
	// 1. ouvrir les fichiers
	int *fd_redirs;
	int size_redirs;
	int	last_in;
	int last_out;
	int i;

	last_in = 0;
	last_out = 1;
	size_redirs = ft_get_size(redirs);
	fd_redirs = malloc(size_redirs * sizeof(int));
	if (!fd_redirs)
		return (1);
	i = 0;
	while (redirs[i])
	{
		/* gérer les erreurs de open */
		fd_redirs[i] = open(redirs[i]->filename, redirs[i]->option); // check options permisions
		if (redirs[i]->fd == 0)
			last_in = fd_redirs[i];
		else
			last_out = fd_redirs[i];
		i++;
	}

	// 2. redirections (dup2)
	if (dup2(last_in, 0) < 0)
		return (1);
	if (dup2(last_out, 1) < 0)
		return (1);

	// 3. close
	i = 0;
	while (fd_redirs[i])
		close(fd_redirs[i++]);
	return (0);
}

int	ft_exec(t_tree *t, t_env *env)
{
	int save_out;
	int save_in;

	save_out = dup(1);
	save_in = dup(0);
	ft_redirs(t->redirs);
	if (t->op == PIPE)
	{
		ft_pipe(t->l, t->r, env);
	}
	else if (t->op == AND)
	{
		ft_and(t->l, t->r,  env);
	}
	else if (t->op == OR)
	{
		ft_or(t->l, t->r,  env);
	}
	else if (t->op == CMD)
	{
		t->args = ft_expand_all_vars(t->args,  env->e_tab);
		if (ft_exec_command(t->args, env) == 1)
			return (1); /* + print error */
	}
	if (dup2(save_in, 0) < 0)
		return (1);
	if (dup2(save_out, 1) < 0)
		return (1);
	close(save_in);
	close(save_out);
	return (0);
}
