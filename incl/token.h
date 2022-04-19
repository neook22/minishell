#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_op {PIPE, AND, OR, CMD, OPAREN, CPAREN, UNDEF}	t_op;

typedef struct s_redir
{
	int		fd;
	int		option;
	char	*filename;
	int		hdoc_fd;
}	t_redir;

typedef enum e_tktype {OP, REDIR, STR, BAD, END}	t_tktype;

typedef struct s_tok
{
	t_tktype	type;
	union	u_tktype
	{
		t_redir	*redir;
		char	*str;
		t_op	op;
	}	data;
}	t_tok;

t_op	ft_op_of_str(char const *str);
void	ft_free_redir(t_redir *redir);
void	ft_free_tok_contents(t_tok *tok);
t_redir	*ft_redir_of_str(char const *str);

#endif
