#ifndef EXEC_UTILS_H
#define EXEC_UTILS_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

typedef struct s_path
{
	char	*path;
	char	*env_paths;
	char	**paths;
	char	*tmp;
	int	i;
}              t_path;

char	*ft_get_path(char *command, char **env);
int		ft_get_size(t_redir **redirs);

#endif
