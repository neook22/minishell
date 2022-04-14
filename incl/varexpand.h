#ifndef VAREXPAND_H
# define VAREXPAND_H

/* find (and alloc) the value of variable 'key' where env is 
 * a null-terminated array of "var=value" strings */
char	*ft_varvalue(char const *key, char **env);

/* returns the longest uninterrupted substring 
 * containing only '_' or alnum characters
 * at the start of 'start' 
 * 
 * The idea is that, if for example :
 * s = "123$varname whatever"
 * then ft_parse_name(s + 4) is the name of the 
 * variable that must be expanded, ie "varname" */
char	*ft_parse_varname(char const *start);

/* return a string containing the result of 'line' with 
 * its variables expanded according to key-value pairings
 * in env */
char	*ft_varexpand(char const *line, char **env);

#endif
