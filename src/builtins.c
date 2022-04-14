/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeuneje <sjeuneje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 13:16:23 by mdelforg          #+#    #+#             */
/*   Updated: 2022/04/14 15:51:38 by sjeuneje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

int	ft_flag_n(char *str)
{
	int	i;

	if (str[0] != '-')
		return (1);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	ft_my_echo(char **args)
{
	int	i;
	int	n_option;

	i = -1;
	n_option = 0;
	while (args[++i] && !ft_flag_n(args[i]))
		n_option++;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[++i])
			printf(" ");
	}
	if (!n_option)
		printf("\n");
	return (0);
}

//	export var, sans =
//	verifier les args de pwd, cd, ...
//	exit -1
int	ft_dispatcher(char *cmd, char **args, t_env *env)
{
	if (!ft_strncmp(cmd, "env", 4))
		return (ft_my_env(args, env));
	else if (!ft_strncmp(cmd, "export", 7))
		return (ft_my_export(args, env));
	else if (!ft_strncmp(cmd, "unset", 6))
		return (ft_my_unset(args, env));
	else if (!ft_strncmp(cmd, "echo", 5))
		return (ft_my_echo(args));
	else if (!ft_strncmp(cmd, "cd", 3))
		return (ft_my_cd(args, env));
	else if (!ft_strncmp(cmd, "pwd", 4))
		return (ft_my_pwd());
	return (E_NOT_BUILT_IN);
}
