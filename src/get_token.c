#include <fcntl.h>
#include <stdlib.h>
#include "utils.h"
#include "libft.h"
#include "token.h"
#include "heredoc.h"
#include "get_token.h"

# include <stdio.h>

static t_tok	*ft_consume_op(char **stdraddr, t_tok *tok, char *opstr);
static t_tok	*ft_consume_str(char **stdraddr, t_tok *tok);
static t_tok	*ft_consume_redir(char **stdraddr, t_tok *tok, char *redirstr);

// fill '*tok' with token data taken from the first token in str
// doesn't alloc *tok
t_tok	*ft_consume_token(char **straddr, t_tok *tok)
{
	char *const	whitespace = " \t\n\r\v\f";
	char *const	ops[6] = {"&&", "||", "|", "(", ")", NULL};
	char *const	redirs[5] = {">>", ">", "<<", "<", NULL};
	char		*first_word;

	while (ft_is_in(whitespace, **straddr))
		++(*straddr);
	if (!(**straddr))
	{
		tok->type = END;
		return (tok);
	}
	first_word = ft_first_word(*straddr, (char **) ops);
	if (first_word)
		return (ft_consume_op(straddr, tok, first_word));
	first_word = ft_first_word(*straddr, (char **) redirs);
	if (first_word)
		return (ft_consume_redir(straddr, tok, first_word));
	else
		return (ft_consume_str(straddr, tok));
}

static t_tok	*ft_consume_op(char **straddr, t_tok *tok, char *op_str)
{
	tok->type = OP;
	tok->data.op = ft_op_of_str(op_str);
	*straddr += ft_strlen(op_str);
	return (tok);
}

static t_tok	*ft_consume_redir(char **straddr, t_tok *tok, char *redir_str)
{
	t_tok	fname_tok;

	tok->type = BAD;
	tok->data.redir = ft_redir_of_str(redir_str);
	if (!tok->data.redir)
		return (tok);
	*straddr += ft_strlen(redir_str);
	if (!ft_consume_token(straddr, &fname_tok) || fname_tok.type != STR)
	{
		ft_free_redir(tok->data.redir);
		return (tok);
	}
	if (!ft_strncmp("<<", redir_str, 3))
	{
		tok->type = REDIR;
		tok->data.redir->hdoc_fd = ft_add_hdoc(fname_tok.data.str);
		return (tok);
	}
	tok->data.redir->filename = fname_tok.data.str; // need to dup?
	if (!(tok->data.redir->filename))
		return (tok);
	tok->type = REDIR;
	return (tok);
}

static size_t	ft_endtoken_index(char *str, int *errcode)
{
	char *const	blanks = " \t\n\r\v\f";
	char *const	ops[10]
		= {">>", ">", "<<", "<", "&&", "||", "|", "(", ")", NULL};
	size_t		i;
	char		quote;

	i = 0;
	quote = 0;
	while (str[i] && !ft_is_in(blanks, str[i]) && !ft_first_word(str + i, ops))
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				++i;
			if (!str[i])
				*errcode = -1;
		}
		if (str[i])
			++i;
	}
	return (i);
}

static t_tok	*ft_consume_str(char **straddr, t_tok *tok)
{
	size_t		i_end;
	int			errnum;
	char		*str;

	tok->type = BAD;
	errnum = 0;
	str = *straddr;
	i_end = ft_endtoken_index(str, &errnum);
	*straddr += i_end;
	if (errnum == -1)
		return (tok);
	tok->data.str = ft_substr(str, 0, i_end);
	if (tok->data.str == NULL)
		return (tok);
	tok->type = STR;
	return (tok);
}
