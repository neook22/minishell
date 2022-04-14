/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeuneje <sjeuneje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 13:13:28 by mdelforg          #+#    #+#             */
/*   Updated: 2022/04/14 15:59:11 by sjeuneje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>

# define E_NOT_BUILT_IN 256

typedef struct s_env
{
	int		size;
	int		e_last;
	char	**e_tab;
}	t_env;

int		ft_dispatcher(char *cmd, char **args, t_env *env);
int		ft_my_echo(char **args);
void	ft_create_env(t_env *env, char **envp);
void	ft_bigger_env(t_env *env, char **past_e);
int		ft_my_export(char **args, t_env *env);
int		ft_my_pwd(void);
int		ft_my_cd(char **args, t_env *env);
int		ft_my_unset(char **args, t_env *env);
int		ft_my_env(char **args, t_env *env);
int		ft_var_index(char *str, char **e_tab, int fct);
void	ft_remove_var(int i, t_env *env);

#endif
