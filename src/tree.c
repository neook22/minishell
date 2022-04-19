#include <stdlib.h>
#include "libft.h"
#include "utils.h"
#include "get_token.h"
#include "dyna_mem.h"
#include "tree.h"

void	ft_free_tree(t_tree *t)
{
	size_t 	i;

	if (!t)
		return ;
	ft_free_strtab(t->args);
	i = 0;
	while (t->redirs && t->redirs[i])
		ft_free_redir(t->redirs[i++]);
	ft_free_tree(t->l);
	ft_free_tree(t->r);
	free(t);
}

t_tree	*ft_node(t_op op, t_tree *l, t_tree *r)
{
	t_tree *t;

	t = malloc(sizeof(t_tree));
	if (!t)
		return (NULL);
	t->redirs = NULL;
	t->args = NULL;
	t->op = op;
	t->l = l;
	t->r = r;
	return (t);
}

static t_tree	*ft_one_cmd(char **line, t_tok *tok, t_dyna *redirs)
{
	t_tree	*t;
	t_dyna	args;

	ft_init_dyna(&args);
	t = ft_node(CMD, NULL, NULL);
	while (tok) // note : one token is pre-loaded
	{
		if (tok->type == STR)
			ft_dyna_append(&args, &(tok->data.str), sizeof(char *));
		else if (tok->type == REDIR)
			ft_dyna_append(redirs, &(tok->data.redir), sizeof(t_redir *));
		else
			break;
		tok = ft_consume_token(line, tok);
	}
	ft_dyna_zeros(&args, sizeof(char *));
	t->args = (char **) ft_dedyna(&args);
	return (t);
}

static t_tree	*ft_recaux(char **line, int min_prio, t_tok *tok)
{
	t_tree	*left;
	int		prio;
	t_dyna	redirs;

	ft_init_dyna(&redirs);
	ft_consume_token(line, tok);
	if (tok->type == OP && tok->data.op == OPAREN)
	{
		left = ft_recaux(line, 0, tok);
		if (!(tok->type == OP && tok->data.op == CPAREN))
			exit (2);
		ft_consume_token(line, tok);
		while (tok->type == REDIR)
		{
			ft_dyna_append(&redirs, &(tok->data.redir), sizeof(t_redir *));
			ft_consume_token(line, tok);
		}
	}
	else if (tok->type == STR || tok->type == REDIR)
		left = ft_one_cmd(line, tok, &redirs);
	else 
		exit (3);
	ft_dyna_zeros(&redirs, sizeof(t_redir *));
	left->redirs = (t_redir **) ft_dedyna(&redirs);
	while (tok->type != END && !(tok->type == OP && tok->data.op == CPAREN))
	{
		if (tok->type == OP && (tok->data.op == PIPE))
			prio = 2;
		else if (tok->type == OP && (tok->data.op == AND || tok->data.op == OR))
			prio = 1;
		else
			exit (4);
		if (prio < min_prio)
			return (left);
		t_op tmp = tok->data.op;
		left = ft_node(tmp, left, ft_recaux(line, prio + 1, tok));
	}
	return (left);
}

t_tree *ft_tree_of_line(char **line)
{
	t_tok	tok;
	t_tree	*t;
	
	t = ft_recaux(line, 0, &tok);  
//	if (errcode)
//	{
//		ft_free_tree(t);
//		return (NULL);
//		ft_free_tok_contents(&tok);
//	}
	return (t);
}
