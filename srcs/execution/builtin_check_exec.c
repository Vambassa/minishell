/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check_exec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vambassa <vambassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 01:12:58 by vambassa          #+#    #+#             */
/*   Updated: 2022/03/28 21:14:17 by vambassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_exec(t_mini *shell, t_cmd *cmd)
{
	if (!ft_strcmp("echo", cmd->command[0]))
		echo_execute(shell->cmds->command);
	else if (!ft_strcmp("cd", cmd->command[0]))
		cd_execute(shell, shell->cmds->command);
	else if (!ft_strcmp("pwd", cmd->command[0]))
		pwd_execute();
	else if (!ft_strcmp("export", cmd->command[0]))
		export_execute(shell, shell->cmds->command);
	else if (!ft_strcmp("unset", cmd->command[0]))
		unset_execute(shell, shell->cmds->command);
	else if (!ft_strcmp("env", cmd->command[0]))
		env_execute(shell->env);
	else if (!ft_strcmp("exit", cmd->command[0]))
		exit_execute(shell->cmds->command);
	else
		return ;
}

int	check_if_builtin(char *cmd)
{
	if (!cmd)
		return (1);
	if (!ft_strcmp(cmd, "echo"))
		return (0);
	else if (!ft_strcmp(cmd, "cd"))
		return (0);
	else if (!ft_strcmp(cmd, "pwd"))
		return (0);
	else if (!ft_strcmp(cmd, "export"))
		return (0);
	else if (!ft_strcmp(cmd, "unset"))
		return (0);
	else if (!ft_strcmp(cmd, "env"))
		return (0);
	else if (!ft_strcmp(cmd, "exit"))
		return (0);
	else
		return (1);
}
