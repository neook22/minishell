#ifndef HEREDOC_H
# define HEREDOC_H

# include "dyna_mem.h"

/* implementations of heredocs as pipes 
 * the idea is that the write-end (in) of the pipe 
 * will be pre-filled when the heredoc is declared/read
 * and the contents can then be read out of the read-end (out)
 * of the pipe */
typedef struct s_hdoc
{
	int		pipefd[2];
	char	*name;
}	t_hdoc;

// fill heredoc with contents from stdin until
// a the line "<hdoc->name>" is encountered
// TODO do we need expand vars? 
void	ft_read_hdoc(t_hdoc *hdoc);

// read stdin until all current hdocs are filled
// (ie they were closed by a single line containing their name)
void	ft_hdoc_readall(void);

// Remove quotes from a token (bash rules)
// Meant for heredoc names
// eg :	
// 	"foo" -> foo
// 	"'foo'b"'ar"q'ux -> 'foo'bar"qux
//
// 'token' will be freed and replaced with the new string
char	*ft_dequote(char *token);

// add an heredoc
// name is a bash-style token that can contain quotes that will not appear 
// in the final heredoc name (unless escaped by other quotes, etc)
// 
// return the the fd of the read-end (out) of the pipe (or -1 if error)
int	ft_add_hdoc(char *name);

// close all current heredocs and free their ressources
void 	ft_hdoc_closeall(void);

#endif
