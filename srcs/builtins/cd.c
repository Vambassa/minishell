/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vambassa <vambassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 01:12:14 by vambassa          #+#    #+#             */
/*   Updated: 2022/03/25 22:32:55 by vambassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	define_new_pwd(t_mini *shell)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, PATH_MAX);
	if (!new_pwd)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return (1);
	}
	else
	{
		change_value_in_env(shell->env, "PWD", new_pwd);
		change_value_in_env(shell->env_copy, "PWD", new_pwd);
		free(new_pwd);
	}
	return (0);
}

static char	*define_home_path(t_env *env)
{
	char	*path;

	path = NULL;
	while (env)
	{
		if (!ft_strcmp(env->key, "HOME"))
		{
			path = ft_strdup(env->value);
			return (path);
		}
		env = env->next;
	}
	return (NULL);
}

int	define_print_oldpwd(t_mini *shell)
{
	char	*value;

	value = cd_find_key_value(shell->env, "OLDPWD");
	if (!value)
	{
		ft_putendl_fd("minishell: cd: OLDPWD not set", STDERR_FILENO);
		return (1);
	}
	else
	{
		ft_putendl_fd(value, STDOUT_FILENO);
		return (chdir(value));
	}
}

int	apply_cd(t_mini *shell, char *home_path)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, PATH_MAX);
	if (!oldpwd)
		oldpwd = ft_strdup(cd_find_key_value(shell->env, "HOME"));
	change_value_in_env(shell->env, "OLDPWD", oldpwd);
	change_value_in_env(shell->env_copy, "OLDPWD", oldpwd);
	if (chdir(home_path) == -1)
	{
		free(oldpwd);
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(home_path, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return (1);
	}
	else
		free(oldpwd);
	return (define_new_pwd(shell));
}

void	cd_execute(t_mini *shell, char **cmds)
{
	char	*home_path;

	if (count_args(cmds) == 1)
	{
		home_path = define_home_path(shell->env);
		if (!home_path)
		{
			ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
			return ;
		}
		g_exit_code = apply_cd(shell, home_path);
		free(home_path);
		return ;
	}
	else if (!ft_strcmp(cmds[1], "-"))
		g_exit_code = define_print_oldpwd(shell);
	else if (cmds[1][0] == '~' || !ft_strcmp(cmds[1], "--"))
	{
		cmds[1] = NULL;
		cd_execute(shell, cmds);
		g_exit_code = 0;
	}
	else
		g_exit_code = apply_cd(shell, cmds[1]);
}
