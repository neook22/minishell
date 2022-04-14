#include <fcntl.h>
#include <stdlib.h>
#include "utils.h"
#include "libft.h"
#include "get_token.h"

#include <stdio.h>

//typedef enum e_op {PIPE, AND, OR, CMD, OPAREN, CPAREN, UNDEF} t_op;
//
//typedef struct s_redir 
//{
//	int 	fd;
//	int 	option;
//	char	*filename;
//} t_redir;
//
//typedef enum e_tktype {OP, REDIR, STR, BAD} t_tktype;
//
//typedef union u_tkdata 
//{
//	t_redir	*redir;
//	char	*str;
//	t_op	op;
//}	t_tkdata;
//
//typedef struct s_tok
//{
//	t_tktype	type;
//	t_tkdata	data;
//}	t_tok;

t_op	ft_op_of_str(char const *str)
{
	// maybe add 1 to n? or make strcmp (not n) fun
	if (!ft_strncmp("&&", str, 2))
		return (AND);
	if (!ft_strncmp("||", str, 2))
		return (OR);
	if (!ft_strncmp("|", str, 1))
		return (PIPE);
	if (!ft_strncmp("(", str, 1))
		return (OPAREN);
	if (!ft_strncmp(")", str, 1))
		return (CPAREN);
	return (UNDEF);
}

char	*ft_first_word(char *str, char * const *allowed_words)
{
	while (*allowed_words)
	{
		if (!ft_strncmp(str, *allowed_words, ft_strlen(*allowed_words)))
			return (*allowed_words);
		allowed_words++;
	}
	return (NULL);
}

void	ft_free_redir(t_redir *redir)
{
	free(redir->filename);
	free(redir);
}

void	ft_free_tok(t_tok *tok)
{
	if (tok->type == STR)
		free(tok->data.str);
	if (tok->type == REDIR)
		ft_free_redir(tok->data.redir);
	free(tok);
}

/** move to .h **/
static t_tok	*ft_consume_op(char **stdraddr, t_tok *tok, char *opstr);
static t_tok	*ft_consume_str(char **stdraddr, t_tok *tok);
static t_tok	*ft_consume_redir(char **stdraddr, t_tok *tok, char *redirstr);

// fill '*tok' with token data taken from the first token in str
// doesn't alloc *tok
t_tok	*ft_consume_token(char **straddr, t_tok *tok)
{
	char * const whitespace = " \t\n\r\v\f";
	char * const ops[6] = {"&&", "||", "|", "(", ")", NULL};
	char * const redirs[4] = {">>", ">", "<", NULL}; // TODO handle <<
	char * first_word;

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

t_redir	*ft_redir_of_str(char const *str)
{
	t_redir *redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->filename = NULL;
	if (*str == '<')
	{
		redir->fd = 0;
		redir->option = O_RDONLY;
		return (redir);
	}
	if (*str == '>') 
	{
		redir->fd = 1;
		redir->option = O_WRONLY | O_CREAT;
		if (str[1] == '>')
			redir->option |= O_APPEND;
		else 
			redir->option |= O_TRUNC;
	}
	return (redir);
}

static t_tok	*ft_consume_redir(char **straddr, t_tok *tok, char *redir_str)
{
	t_tok	filename;

	tok->type = REDIR;
	tok->data.redir = ft_redir_of_str(redir_str);
	if (!tok->data.redir)
	{
		tok->type = BAD;
		return (tok);
	}
	*straddr += ft_strlen(redir_str);
	if (!ft_consume_token(straddr, &filename) || filename.type != STR)
	{
		tok->type = BAD;
		ft_free_redir(tok->data.redir);
		return (tok);
	}
	tok->data.redir->filename = ft_strdup(filename.data.str);
	return (tok);
}

// static t_tok	*ft_consume_str(char **strp, t_tok *tok)
// {
// 	char *buffer;
// 	char * const 	blanks = " \t\n\r\v\f";
// 	char * const	ops[9] = {">>", ">", "<", "&&", "||", "|", "(", ")", NULL};
// 	size_t	i;
	
// 	tok->type = BAD; // assume error
// 	buffer = malloc(ft_strlen(*strp) + 1);
// 	if (!buffer)
// 		return (tok);
// 	i = 0;
// 	while (**strp && !ft_is_in(blanks, **strp) && !ft_first_word(*strp, ops))
// 	{
// 		if (**strp == '"')
// 		{
// 			while (*(++*strp) != '"')
// 				buffer[i++] = **strp;
// 			++(*strp);
// 		}
// 		else if (**strp == '\'')
// 		{
// 			while (*(++(*strp)) != '\'')
// 				buffer[i++] = **strp;
// 			++(*strp);
// 		}
// 		else 
// 			buffer[i++] = *(*strp)++;
// 	}
// 	tok->data.str = malloc(i + 1);
// 	if (!tok->data.str)
// 	{
// 		free(buffer);
// 		return (tok);
// 	}
// 	tok->type = STR;
// 	ft_memcpy(tok->data.str, buffer, i);
// 	tok->data.str[i] = '\0';
// 	free(buffer);
// //	printf("%s\n", tok->data.str);
// 	return (tok);
// }

static size_t	ft_endtoken_index(char *str, int *errcode)
{
	char *const	blanks = " \t\n\r\v\f";
	char *const	ops[10]
		= {">>", ">", "<<", "<", "&&", "||", "|", "(", ")", NULL};
	size_t		i;
	char		quote;

	i = 0;
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
	str = *straddr;
	errnum = 0;
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