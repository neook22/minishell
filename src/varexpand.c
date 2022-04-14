#include <stdlib.h>
#include "libft.h"
#include "varexpand.h"

/* find (and alloc) the value of variable 'key' where env is 
 * a null-terminated array of "var=value" strings */
char	*ft_varvalue(char const *key, char **env)
{
	size_t	keysz;
	char	*empty;

	keysz = ft_strlen(key);
	while (*env)
	{
		if (ft_strncmp(key, *env, keysz) == 0 && (*env)[keysz] == '=')
			return (ft_strdup(*env + keysz + 1));
		++env;
	}
	empty = malloc(1);
	if (empty)
		*empty = '\0';
	return (empty);
}

/* is '_' or an alnum character
 * these are the characters allowed in bash variable names */
static int	ft_isvarchar(char c)
{
	return (c == '_' || ft_isalpha(c) || ft_isdigit(c));
}

/* returns the longest uninterrupted substring 
 * containing only '_' or alnum characters
 * at the start of 'start' 
 * 
 * The idea is that, if for example :
 * s = "123$varname whatever"
 * then ft_parse_name(s + 4) is the name of the 
 * variable that must be expanded, ie "varname" */
char	*ft_parse_varname(char const *start)
{
	size_t	sz;

	sz = 0;
	while (ft_isvarchar(start[sz]))
		++sz;
	return (ft_substr(start, 0, sz));
}

///* expand one variable (ie append its value to 'dy')
// * and return the string pointing to what is *after*
// * the expanded variable */
//static char	*ft_expand_one(char const *s, char **env, t_dyna *dy, int i)
//{
//	char	*varname;
//	char	*varvalue;
//
//	ft_dyna_slurp(dy, ft_substr(s, 0, i), i + 1); 
//	varname = ft_parse_varname(s + (++i));
//	varvalue = ft_varvalue(varname, env);
//	ft_dyna_slurp(dy, varvalue, ft_strlen(varvalue) + 1);
//	i += ft_strlen(varname);
//	free(varname);
//	return (s + i);
//}
//
//static char	*ft_vexp_helper(char const *s, char **env, t_dyna *dy, int qte)
//{
//	const int	sgqte_mask = 1;	
//	const int	dblqte_mask = 2;
//	size_t		i;
//
//	i = 0;
//	while (s[i])
//	{
//		if (!(qte & sgqte_mask) && s[i] == '$' && ft_isvarchar(s[i + 1]))
//		{
//			s = ft_expand_one(s, env, dy, i);
//			return (ft_vexp_helper(s, env, dy, qte));
//		}
//		if (s[i] == '\'' && !(qte & dblqte_mask))
//			qte ^= sgqte_mask; 
//		if (s[i] == '"' && !(qte & sgqte_mask))
//			qte ^= dblqte_mask;
//		++i;
//	}
//	ft_dyna_append(dy, s, ft_strlen(s) + 1); 
//	return (ft_strify(dy));
//}
//
///* return a string containing the result of 'line' with 
// * its variables expanded according to key-value pairings
// * in env */
//char	*ft_varexpand(char const *line, char **env)
//{
//	t_dyna	slurper;
//
//	ft_init_dyna(&slurper);
//	return (ft_vexp_helper(line, env, &slurper, 0));
//}
