/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calecia <calecia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 01:13:16 by vambassa          #+#    #+#             */
/*   Updated: 2022/03/28 20:46:30 by calecia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	heredoc_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\b\b\n", 3);
	exit(1);
}

static void	fix_norme_2(t_cmd **cmds, t_mini **shell, t_cmd **begin)
{
	if ((*cmds)->pid < 0)
		print_error_message("minishell: fork failed", 128);
	else if (!(*cmds)->pid)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &heredoc_sigint);
		handle_heredoc((*cmds));
	}
	else
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		waitpid((*cmds)->pid, NULL, 0);
	}
	handle_blocking_signals();
	(*cmds)->pid = fork();
	if ((*cmds)->pid < 0)
		print_error_message("minishell: fork failed", 128);
	else if ((*cmds)->pid == 0)
		children_process((*shell), (*cmds), (*begin));
}

static void	fix_norme_1(t_cmd **cmds, t_mini **shell, t_cmd **begin)
{
	if ((*cmds)->redir && !ft_strcmp("<<", (*cmds)->redir->type))
	{
		open_file((*cmds));
		(*cmds)->pid = fork();
		(*cmds)->fork = 1;
		fix_norme_2(cmds, shell, begin);
	}
	else
	{
		open_file((*cmds));
		(*cmds)->pid = fork();
		(*cmds)->fork = 1;
		if ((*cmds)->pid < 0)
			print_error_message("minishell: fork failed", 128);
		else if (!(*cmds)->pid)
			children_process((*shell), (*cmds), (*begin));
	}
}

void	execute_commands(t_mini *shell, t_cmd *cmds)
{
	t_cmd	*begin;

	begin = cmds;
	handle_blocking_signals();
	if (!cmds->next && !check_if_builtin(cmds->command[0]) && !cmds->redir)
		execute_cmd(shell, cmds);
	else
	{
		if (!pipe_creator(cmds))
		{
			while (cmds)
			{
				fix_norme_1(&cmds, &shell, &begin);
				cmds = cmds->next;
			}
			parent_process(begin);
		}
	}
}
