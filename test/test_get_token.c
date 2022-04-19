#include <stdio.h>
#include "get_token.h"

static void	print_tok(t_tok const *tok)
{
	char * const ops[9] = {"|", "&&", "||", "cmd", "(", ")", "undef"};
	switch (tok->type)
	{
		case STR:
			printf("'%s' ", tok->data.str);
			break;
		case REDIR:
			printf("REDIR %d, %d, %s ", tok->data.redir->fd, tok->data.redir->hdoc_fd, tok->data.redir->filename);
			break;
		case OP:
			printf("OP %s ", ops[tok->data.op]);
			break;
		case BAD:
		default:
			printf("bad token");
			break;
	}
	printf("\n");
}

int main(int ac, char **av)
{
	if (ac != 2)
	{
		dprintf(2, "provide 2 args\n");
		return (-1);
	}
	t_tok tok;
	ft_consume_token(av + 1, &tok);
	while (tok.type != END)
	{
		print_tok(&tok);
		ft_consume_token(av + 1, &tok);
	}
	return (0);
}
