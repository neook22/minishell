#ifndef TREE_H
# define TREE_H

# include "get_token.h"
# include <stdlib.h>

typedef struct s_tree
{
	t_op			op;
	char			**args;
	t_redir			**redirs; // actually y 2 * ?? (TODO change)
	struct s_tree	*l;
	struct s_tree	*r;
}	t_tree;

// for now let's assume this will be enough space always (wrong !!!)
typedef struct s_mem
{
	char	*args[64];
	t_redir	*redirs[64];
	size_t	iarg; // start at -1
	size_t	iredir;
}	t_mem;

t_tree	*ft_node(t_op op, t_tree *l, t_tree *r, t_mem *mem);
t_tree	*ft_one_cmd(char **line, t_mem *mem, t_tok *tok);
t_tree *ft_tree_of_line(char **line);

#endif
