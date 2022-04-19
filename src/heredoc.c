#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include "heredoc.h"

// access the list of current heredocs :
// (as described in 2nd paragraph)
// they can be in 2 states -being built, 
// and thus represented by a t_dyna types- 
// or "finished" and represnted by a malloced array.
//
// if dy is not null : make it point to the t_dyna struct
// *then* if hdocs is not null :
//   if a t_dyna is being built 
//     transforms it into an array and make hdocs point to it
//   else make hdocs point to the last such array that was transformed
//
// TODO maybe reconsider triple star.......
static void	ft_get_hdocs(t_dyna **dy, t_hdoc ***hdocs)
{
	static t_dyna	st_dy;
	static t_hdoc	**st_hdocs = NULL;
	static int		init = 0;

	if (!dy && !hdocs)
		st_hdocs = NULL;
	if (!init && dy)
	{
		ft_init_dyna(&st_dy);
		init = 1;
	}
	if (dy)
		*dy = &st_dy;
	if (hdocs)
	{
		if (init)
		{
			ft_dyna_zeros(&st_dy, sizeof(t_hdoc *));
			st_hdocs = ft_dedyna(&st_dy);
			init = 0;
		}
		*hdocs = st_hdocs;
	}
}

// fill heredoc with contents from stdin until
// a the line "<hdoc->name>" is encountered
// TODO do we need expand vars? 
void	ft_read_hdoc(t_hdoc *hdoc)
{
	char	*line;

	line = readline("heredoc > ");
	while (ft_strncmp(line, hdoc->name, ft_strlen(line) + 1))
	{
		write(hdoc->pipefd[1], line, ft_strlen(line));
		write(hdoc->pipefd[1], "\n", 1);
		free(line);
		line = readline("heredoc > ");
	}
	free(line);
	close(hdoc->pipefd[1]);
	hdoc->pipefd[1] = -1;
}

// read stdin until all current hdocs are filled
// (ie they were closed by a single line containing their name)
void	ft_hdoc_readall(void)
{
	t_hdoc	**hdocs;

	ft_get_hdocs(NULL, &hdocs);
	if (!hdocs)
		return ;
	while (*hdocs)
	{
		ft_read_hdoc(*(hdocs++));
	}
}
		
// Remove quotes from a token (bash rules)
// Meant for heredoc names
// eg :	
// 	"foo" -> foo
// 	"'foo'b"'ar"q'ux -> 'foo'bar"qux
//
// 'token' will be freed and replaced with the new string
char	*ft_dequote(char *token)
{
	t_dyna	dy;
	char 	quote;
	size_t	i;
	char	*save_token;

	quote = 0;
	i = 0;
	ft_init_dyna(&dy);
	save_token = token;
	while (token[i])
	{
		if ((!quote && (token[i] == '\'' || token[i] == '"'))
				|| token[i] == quote)
		{
			quote = token[i];
			ft_dyna_append(&dy, token, i++);
			token += i;
			i = 0;
		}
		else 
			++i;
	}
	ft_dyna_append(&dy, token, i);
	ft_dyna_zeros(&dy, 1);
	free(save_token);
	return (ft_dedyna(&dy));
}

// add an heredoc
// name is a bash-style token that can contain quotes that will not appear 
// in the final heredoc name (unless escaped by other quotes, etc)
// 
// return the the fd of the read-end (out) of the pipe (or -1 if error)
int	ft_add_hdoc(char *name)
{
	t_hdoc	*newdoc;
	t_dyna	*hdocs;

	newdoc = malloc(sizeof(t_hdoc));
	if (!newdoc)
		return (-1);
	newdoc->name = ft_dequote(name);
	ft_get_hdocs(&hdocs, NULL);
	hdocs = ft_dyna_append(hdocs, &newdoc, sizeof(t_hdoc *));
	if (!hdocs || !(newdoc->name) || pipe(newdoc->pipefd) == -1)
	{
		free(newdoc);
		return (-1);
	}
	return (newdoc->pipefd[0]);
}

// close all current heredocs and free their ressources
//
// note : careful not to close twice
void 	ft_hdoc_closeall(void)
{
	t_hdoc	**hdocs;
	size_t	i;

	ft_get_hdocs(NULL, &hdocs);
	i = 0;
	while (hdocs && hdocs[i])
	{
		//close(hdocs[i]->pipefd[0]);
		close(hdocs[i]->pipefd[1]);
		free(hdocs[i]->name);
		free(hdocs[i]);
		++i;
	}
	free(hdocs);
	ft_get_hdocs(NULL, NULL);
}
