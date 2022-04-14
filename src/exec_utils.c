#include "tree.h"
#include "exec_utils.h"
#include "libft.h"
#include "varexpand.h"

int	ft_get_size(t_redir **redirs)
{
	int size;

	size = 0;
	while (redirs[size])
		size++;
	return (size);
}

int	ft_strcmp(char *str1, char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		if (*str1 != *str2)
			return (0);
		str1++;
		str2++;
	}
	return (1);
}

int	ft_containschar(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_free_paths(char **paths, char *path, int mode)
{
	int i;

	i = 0;
	if (mode)
	{
		while (paths[i])
		{
			free(paths[i]);
			i++;
		}
		free(paths);
		return (path);
	}
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
	return (NULL);	
}


char	*ft_get_path(char *command, char **env)
{
	t_path	p;
	
	p.i = 0;
	if (ft_containschar(command, '/'))
		return (command);
	p.env_paths = ft_varvalue("PATH", env);
	if (!p.env_paths)
		return (NULL);
	p.paths = ft_split(p.env_paths, ':');
	if (!p.paths)
		return (NULL);
	free(p.env_paths);
	while (p.paths[p.i])
	{
		p.tmp = ft_strjoin(p.paths[p.i], "/");
		p.path = ft_strjoin(p.tmp, command);
		free(p.tmp);
		if (access(p.path, X_OK) != -1)
			return (ft_free_paths(p.paths, p.path, 1));
		free(p.path);
		p.i++;
	}
	perror("command not found");
	return (ft_free_paths(p.paths, p.path, 0));
}
