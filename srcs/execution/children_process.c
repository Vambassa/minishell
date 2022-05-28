/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calecia <calecia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 01:13:04 by vambassa          #+#    #+#             */
/*   Updated: 2022/03/28 20:57:55 by calecia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_path_variable(t_env **env)
{
	if (env && *env)
	{
		while (*env)
		{
			if (!ft_strcmp((*env)->key, "PATH"))
				return (0);
			*env = (*env)->next;
		}
	}
	return (1);
}

static void	print_command_error(char *cmd, char *str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
	g_exit_code = 127;
	exit(g_exit_code);
}

void	execute_cmd(t_mini *shell, t_cmd *cmds)
{
	char	*path;
	char	**env_arr;

	if (!check_if_builtin(cmds->command[0]))
	{
		builtin_exec(shell, cmds);
		if (cmds->fork)
			exit (g_exit_code);
	}
	else
	{
		env_arr = env_copy(shell->env);
		path = find_path(shell, cmds->command[0]);
		if (!path)
		{
			if (!check_path_variable(&shell->env))
				print_command_error(cmds->command[0], "command not found");
			else
				print_command_error(cmds->command[0],
					"No such file or directory");
		}
		if (access(path, F_OK))
			print_command_error(cmds->command[0], "No such file or directory");
		execve(path, cmds->command, env_arr);
	}
}

static int	dup2_fds(t_cmd *cmds)
{
	if (cmds->in != STDIN_FILENO)
	{
		if (dup2(cmds->in, STDIN_FILENO) < 0)
			return (print_error_message("dup2 failed", 1));
		close(cmds->in);
	}
	if (cmds->out != STDOUT_FILENO)
	{
		if (dup2(cmds->out, STDOUT_FILENO) < 0)
			return (print_error_message("dup2 failed", 1));
		close(cmds->out);
	}
	return (0);
}

void	children_process(t_mini *shell, t_cmd *cmds, t_cmd *begin)
{
	dup2_fds(cmds);
	while (begin->next)
	{
		close(begin->pipe_fd[0]);
		close(begin->pipe_fd[1]);
		begin = begin->next;
	}
	execute_cmd(shell, cmds);
}
