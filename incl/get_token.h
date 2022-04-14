
#ifndef GET_TOKEN_H
# define GET_TOKEN_H

typedef enum e_op {PIPE, AND, OR, CMD, OPAREN, CPAREN, UNDEF} t_op;

typedef struct s_redir 
{
	int 	fd;
	int 	option;
	char	*filename;
} t_redir;

typedef enum e_tktype {OP, REDIR, STR, BAD, END} t_tktype;

typedef union u_tkdata 
{
	t_redir	*redir;
	char	*str;
	t_op	op;
}	t_tkdata;

typedef struct s_tok
{
	t_tktype	type;
	t_tkdata	data;
}	t_tok;

t_op	ft_op_of_str(char const *str);
t_tok	*ft_consume_token(char **stdraddr, t_tok *tok);
char	*ft_first_word(char *str, char * const *allowed_words);
void	ft_free_redir(t_redir *redir);
void	ft_free_tok(t_tok *tok);
t_redir	*ft_redir_of_str(char const *str);

#endif
