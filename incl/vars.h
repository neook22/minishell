
#ifndef VARS_H
# define VARS_H

# include "dyna_mem.h"

void	ft_set_varstrings(char **str, char **varname, char **varval, char **env);
void	ft_finish_word(char *str, size_t i, t_dyna *ca, t_dyna *na);
char	*ft_expand_quote(char *arg, t_dyna *curarg, char **env);
char	*ft_expand_noquote(char *a, t_dyna *ca, t_dyna *na, char **env);
int		ft_one_arg(char *arg, t_dyna *newargs, char qte, char **env);
char	**ft_expand_all_vars(char **oldargs, char **env);

#endif
