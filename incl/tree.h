#ifndef TREE_H
# define TREE_H

# include "get_token.h"

typedef struct s_tree
{
	t_op			op;
	char			**args;
	t_redir			**redirs;
	struct s_tree	*l;
	struct s_tree	*r;
}	t_tree;

t_tree	*ft_node(t_op op, t_tree *l, t_tree *r);
t_tree	*ft_tree_of_line(char **line);
void	ft_free_tree(t_tree *t);

#endif
