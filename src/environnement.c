/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environnement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeuneje <sjeuneje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:28:13 by mdelforg          #+#    #+#             */
/*   Updated: 2022/04/14 15:41:38 by sjeuneje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

void	ft_bigger_env(t_env *env, char **past_e)
{
	int	i;

	env->size += 10;
	env->e_tab = (char **)malloc(sizeof(char *) * (env->size + 1));
	if (!env->e_tab)
		exit(EXIT_FAILURE);
	i = 0;
	while (past_e[i])
	{
		env->e_tab[i] = past_e[i];
		i++;
	}
	while (i <= env->size)
	{
		env->e_tab[i] = NULL;
		i++;
	}

	i = -1;
	return ;
}

// free_env
void	ft_create_env(t_env *env, char **envp)
{
	int	i;
	int	count;

	count = 0;
	while (envp[count])
		count++;
	env->size = count + 10;
	i = 0;
	env->e_tab = (char **)malloc(sizeof(char *) * (env->size + 1));
	if (!env->e_tab)
		exit(EXIT_FAILURE);
	while (i < count)
	{
		env->e_tab[i] = ft_strdup(envp[i]);
		if (!env->e_tab[i])// && ft_free_tab(env, i));
			exit(EXIT_FAILURE);
		i++;
	}
	env->e_last = i - 1;
	while (i <= env->size)
	{
		env->e_tab[i] = NULL;
		i++;
	}
	return ;
}
