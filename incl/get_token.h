#ifndef GET_TOKEN_H
# define GET_TOKEN_H

# include "token.h"

/* straddr points to a bash-style command like "cat | grep "foo" >> outfile"
 * read *straddr until we have enough info to build a t_tok obj
 * tokens can be either redirs (eg "> out"), operators (eg "&&", "|") or strings
 * build said t_tok obj and return it
 * make straddr point to where we stopped reading
 *
 * error are signaled by 'tok->type == BAD' */
t_tok	*ft_consume_token(char **stdraddr, t_tok *tok);

#endif
