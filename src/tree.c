#include <stdlib.h>
#include "libft.h"
#include "tree.h"
#include "get_token.h"

#include <stdio.h>

//prototype needed for recursion
static t_tree	*ft_recaux(char **line, int min_prio, t_mem *mem, t_tok *tok);

t_tree	*ft_node(t_op op, t_tree *l, t_tree *r, t_mem *mem)
{
	t_tree *t;

	++(mem->iredir);
	t = malloc(sizeof(t_tree));
	if (!t)
		return (NULL);
	t->redirs = mem->redirs + mem->iredir;
	t->args = NULL;
	t->op = op;
	t->l = l;
	t->r = r;
	return (t);
}

t_tree	*ft_one_cmd(char **line, t_mem *mem, t_tok *tok)
{
	t_tree	*t;

	t = ft_node(CMD, NULL, NULL, mem);
	++(mem->iarg);
	t->args = mem->args + mem->iarg;
	while (tok) // note : one token is pre-loaded
	{
		if (tok->type == STR)
			mem->args[mem->iarg++] = tok->data.str;
		else if (tok->type == REDIR)
			mem->redirs[mem->iredir++] = tok->data.redir;
		else
			break;
		tok = ft_consume_token(line, tok);
	}
	return (t);
}

static t_tree	*ft_recaux(char **line, int min_prio, t_mem *mem, t_tok *tok)
{
	t_tree	*left;
	int		prio;

	ft_consume_token(line, tok);
	if (tok->type == END)
		exit(4);
	if (tok->type == OP && tok->data.op == OPAREN)
	{
		left = ft_recaux(line, 0, mem, tok);
		if (!(tok->type == OP && tok->data.op == CPAREN))
			exit (1); // TODO proper error (unclosed paren)
		ft_consume_token(line, tok);
		while (tok->type == REDIR)
		{
			mem->redirs[mem->iredir++] = tok->data.redir;
			ft_consume_token(line, tok);
		}
	}
	else if (tok->type == STR || tok->type == REDIR)
		left = ft_one_cmd(line, mem, tok);
	else 
		exit (2); // better error (missing arg)
	while (tok->type != END && !(tok->type == OP && tok->data.op == CPAREN))
	{
		if (tok->type == OP && (tok->data.op == PIPE))
			prio = 2;
		else if (tok->type == OP && (tok->data.op == AND || tok->data.op == OR))
			prio = 1;
		else
			exit (3); // better error (unexpected token)
		if (prio < min_prio)
			return (left);
		t_op tmp = tok->data.op;
		left = ft_node(tmp, left, ft_recaux(line, prio + 1, mem, tok), mem);
	}
	return (left);
}

// maybe consume_tok should have a different tok->type for END instead of returning NULL
t_tree *ft_tree_of_line(char **line)
{
	t_mem *mem = malloc(sizeof(t_mem));
	// !!! this will cause leaks (TODO)
	t_tok tok;
	
	ft_bzero(mem, sizeof(t_mem)); // hopefully this does set pointers to NULL
	return (ft_recaux(line, 0, mem, &tok));
	// in error cases free tok contents...
}
