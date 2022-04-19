#include <fcntl.h>
#include <stdlib.h>
#include "utils.h"
#include "libft.h"
#include "token.h"

t_op	ft_op_of_str(char const *str)
{
	if (!ft_strncmp("&&", str, 3))
		return (AND);
	if (!ft_strncmp("||", str, 3))
		return (OR);
	if (!ft_strncmp("|", str, 2))
		return (PIPE);
	if (!ft_strncmp("(", str, 2))
		return (OPAREN);
	if (!ft_strncmp(")", str, 2))
		return (CPAREN);
	return (UNDEF);
}

void	ft_free_redir(t_redir *redir)
{
	free(redir->filename);
	free(redir);
}

void	ft_free_tok_contents(t_tok *tok)
{
	if (tok->type == STR)
		free(tok->data.str);
	if (tok->type == REDIR)
		ft_free_redir(tok->data.redir);
}

// malloc a t_redir obj
// and pre-fill that can be deduced from 
// the operator ('>' '<' etc) 
t_redir	*ft_redir_of_str(char const *op_str)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->filename = NULL;
	redir->hdoc_fd = -1;
	if (*op_str == '<')
	{
		redir->fd = 0;
		redir->option = O_RDONLY;
		return (redir);
	}
	if (*op_str == '>')
	{
		redir->fd = 1;
		redir->option = O_WRONLY | O_CREAT;
		if (op_str[1] == '>')
			redir->option |= O_APPEND;
		else
			redir->option |= O_TRUNC;
	}
	return (redir);
}
