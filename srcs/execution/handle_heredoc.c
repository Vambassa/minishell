/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vambassa <vambassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 01:13:29 by vambassa          #+#    #+#             */
/*   Updated: 2022/03/28 21:23:36 by vambassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	read_input(t_cmd *cmd, char *limiter)
{
	char	*input;

	input = readline("> ");
	while (ft_strcmp(input, limiter))
	{
		ft_putendl_fd(input, cmd->out);
		free(input);
		input = readline("> ");
	}
	if (input)
		free(input);
	close(cmd->out);
	exit(0);
}

static void	fix_norme(pid_t *pid, int fd[2], t_cmd **cmd)
{
	if (!*pid)
	{
		close(*fd);
		(*cmd)->out = (*(fd + 1));
		read_input((*cmd), (*cmd)->redir->name);
	}
	else
	{
		close(*(fd + 1));
		waitpid(*pid, NULL, 0);
		(*cmd)->in = (*fd);
	}
}

void	handle_heredoc(t_cmd *cmd)
{
	int		fd[2];
	pid_t	pid;

	while (cmd->redir)
	{
		if (pipe(fd) == -1)
		{
			print_error_message("pipe failed", 1);
			exit(g_exit_code);
		}
		pid = fork();
		if (pid == -1)
		{
			print_error_message("fork failed", 1);
			exit(g_exit_code);
		}
		fix_norme(&pid, fd, &cmd);
		cmd->redir = cmd->redir->next;
	}
}
