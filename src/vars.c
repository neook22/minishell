#include <stdlib.h>
#include "libft.h"
#include "dyna_mem.h"
#include "utils.h"
#include "varexpand.h"
#include "vars.h"


// TODO split into files + use struct for curarg and newargs + check errors (t_dyna)

void	ft_set_varstrings(char **str, char **varname, char **varval, char **env)
{
	*varname = ft_parse_varname(*str);
	*varval = ft_varvalue(*varname, env);
	*str += ft_strlen(*varname);
}

void	ft_finish_word(char *str, size_t i, t_dyna *ca, t_dyna *na)
{
	char	*word;

	ft_dyna_append(ca, str, i);
	ft_dyna_zeros(ca, 1);
	word = ft_dedyna(ca);
	ft_init_dyna(ca);
	ft_dyna_append(na, &word, sizeof(char *));
}

char	*ft_expand_quote(char *arg, t_dyna *curarg, char **env)
{
	char	*varname;
	char	*varvalue;

	ft_set_varstrings(&arg, &varname, &varvalue, env);
	ft_dyna_slurp(curarg, varvalue, ft_strlen(varvalue));
	free(varname);
	return (arg);
}

char	*ft_expand_noquote(char *a, t_dyna *ca, t_dyna *na, char **env)
{
	char	*varname;
	char	*varvalue;
	size_t	i;
	char	*varvalue_save;

	ft_set_varstrings(&a, &varname, &varvalue, env);
	varvalue_save = varvalue;
	i = 0;
	while (varvalue[i])
	{
		if (ft_is_in(" \t\n\v\r\f", varvalue[i]))
		{
			ft_finish_word(varvalue, i, ca, na);
			while (ft_is_in(" \n\t\r\v\f", varvalue[i]))
				++i;
			varvalue += i;
			i = 0;
		}
		else
			++i;
	}
	ft_dyna_append(ca, varvalue, i);
	free(varvalue_save);
	free(varname);
	return (a);
}
	
int	ft_one_arg(char *arg, t_dyna *newargs, char qte, char **env)
{
	static t_dyna	curarg;
	size_t			i;
	static int		init = 0;

	if (!init)
	{
		ft_init_dyna(&curarg);
		init = 1;
	}
	i = 0;
	while (arg[i])
	{
		// 6 lines to func
		if (((arg[i] == '"' || arg[i] == '\'') && (!qte || qte == arg[i]))
				|| (qte != '\'' && arg[i] == '$'))
			ft_dyna_append(&curarg, arg, i);
		if (qte && qte == arg[i]) // endquote
			return (ft_one_arg(arg + i + 1, newargs, 0, env));
		if (!qte && (arg[i] == '"' || arg[i] == '\'')) // startquote
			return (ft_one_arg(arg + i + 1, newargs, arg[i], env));
		if (qte != '\'' && arg[i] == '$') // startvarexpand
		{
			arg += i + 1;
			if (!qte)
				arg = ft_expand_noquote(arg, &curarg, newargs, env);
			else
				arg = ft_expand_quote(arg, &curarg, env);
			return (ft_one_arg(arg, newargs, qte, env));
		}
		++i;
	}
	ft_finish_word(arg, i, &curarg, newargs);
	free(ft_dedyna(&curarg));
	init = 0;
	return (0);
}

char	**ft_expand_all_vars(char **oldargs, char **env)
{
	t_dyna	newargs;

	ft_init_dyna(&newargs);
	while (*oldargs)
	{
		ft_one_arg(*oldargs, &newargs, 0, env);
		++oldargs;
	}
//	ft_free_tab(oldargs);
	ft_dyna_zeros(&newargs, sizeof(char *));
	return (ft_dedyna(&newargs));
}
