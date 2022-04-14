/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeuneje <sjeuneje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:53:46 by mdelforg          #+#    #+#             */
/*   Updated: 2022/04/14 15:41:25 by sjeuneje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

int	ft_my_env(char **args, t_env *env)
{
	int	i;

	i = 0;
	if (!args || !*args)
	{
		while (i <= env->e_last)
		{
			if (ft_strchr(env->e_tab[i], '='))
				printf("%s\n", env->e_tab[i]);
			i++;
		}
		return (0);
	}
	return (1);
}

void	ft_remove_var(int i, t_env *env)
{
	while (env->e_tab[i] || env->e_tab[i + 1])
	{
		free(env->e_tab[i]);
		env->e_tab[i] = env->e_tab[i + 1];
		env->e_tab[i + 1] = NULL;
		i++;
	}
	env->e_last--;
	return ;
}

int	ft_var_index(char *str, char **e_tab, int fct)
{
	int	i;
	int	j;

	i = 0;
	while (e_tab[i])
	{
		j = 0;
		while (e_tab[i][j] && e_tab[i][j] != '=')
			j++;
		if (!fct)
		{	
			if (!ft_strncmp(e_tab[i], str, j) && !str[j])
				return (i);
		}
		else
		{
			if (!ft_strncmp(e_tab[i], str, j))
				return (i);
		}
		i++;
	}
	return (-1);
}

int	ft_check_unset(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr("!@#$%^&*()-+[]{}\\|;:\'\",.<>/?˜`", str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_my_unset(char **args, t_env *env)
{
	int	i;
	int	a;
	int	ret;

	a = 0;
	ret = 0;
	while (args[a])
	{
		if (ft_check_unset(args[a]))
			ret = 1;
		i = ft_var_index(args[a], env->e_tab, 0);
		if (i >= 0)
			ft_remove_var(i, env);
		a++;
	}
	return (ret);
}
