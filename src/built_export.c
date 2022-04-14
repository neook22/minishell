/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeuneje <sjeuneje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:45:03 by mdelforg          #+#    #+#             */
/*   Updated: 2022/04/14 15:41:21 by sjeuneje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

int	ft_check_var(char *str)
{
	int	i;

	if (str[0] == '=' || ft_isdigit((int)str[0]))
		return (1);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (ft_strchr("!@#$%^&*()-+[]{}\\|;:\'\",.<>/?˜`", str[i]))
			return (1);
		i++;
	}
	i = 0;
	while (str[i])
	{
		if (!ft_isalnum((int)str[i]) && !ft_strchr("@#$%^*-_=+[]{}\\|:,./?˜", str[i]))
			return (1);
		i++;
	}
	return (0);
}

// export +=
int	*ft_env_index(char **env)
{
	int max;
	int	a;
	int	i;
	int	*index;

	max = 0;
	while (env[max])
		max++;
	index = (int *)malloc(sizeof(int) * (max + 1));
	a = 0;
	while (a < max)
	{
		index[a] = 0;
		i = 0;
		while (env[i])
		{
			if (ft_strncmp(env[a], env[i], ft_strlen(env[a])) > 0)
				index[a]++;
			i++;
		}
		a++;
	}
	index[a] = -1;
	return (index);
}

void	ft_putstr_export(char *str)
{
	int	i;

	printf("declare -x ");
	i = 0;
	while (str[i] && str[i - 1] != '=')
	{
		printf("%c", str[i]);
		i++;
	}
	if (str[i - 1] == '=')
	{
		printf("\"");
		while (str[i])
		{
			printf("%c", str[i]);
			i++;
		}
		printf("\"");
	}
	printf("\n");
	return ;
}

int	ft_env_sorted(char **env)
{
	int	i;
	int	nb;
	int	max;
	int	*index;

	index = ft_env_index(env);
	max = 0;
	while (env[max])
		max++;
	nb = 0;
	while (nb < max)
	{
		i = 0;
		while (env[i])
		{
			if ((index[i] == nb) && !(env[i][0] == '_' && env[i][1] == '='))
				ft_putstr_export(env[i]);
			i++;
		}
		nb++;
	}
	free(index);
	return (0);
}

//	export a=" " (parsing)
int	ft_my_export(char **args, t_env *env)
{
	int	a;
	int	i;
	int j;
	int	ret;

	j = 0;
	if (!args || !*args)
		return (ft_env_sorted(env->e_tab));
	ret = 0;
	while (args[j])
	{
		i = env->e_last + 1;
		if (!ft_check_var(args[j]))
		{
			a = ft_var_index(args[j], env->e_tab, 1);
			if (a >= 0)
			{
				free(env->e_tab[a]);
				env->e_tab[a] = ft_strdup(args[j]);
			}
			else
			{
				env->e_tab[i] = ft_strdup(args[j]);
				env->e_last++;
			}
		}
		else
			ret = 1;
		j++;
		if (env->e_last == env->size -1)
			ft_bigger_env(env, env->e_tab);
	}
	return (ret);
}
