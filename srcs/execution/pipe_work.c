/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_work.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vambassa <vambassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 01:13:36 by vambassa          #+#    #+#             */
/*   Updated: 2022/03/23 20:54:09 by vambassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	print_fork_error(t_cmd *cmds)
{
	ft_putstr_fd("minishell$ pipe failed", STDERR_FILENO);
	g_exit_code = 128;
	while (cmds->next)
	{
		close(cmds->pipe_fd[0]);
		close(cmds->pipe_fd[1]);
		cmds = cmds->next;
	}
	return (1);
}

int	pipe_creator(t_cmd *cmds)
{
	t_cmd	*start;

	start = cmds;
	while (cmds->next)
	{
		if (pipe(cmds->pipe_fd) < 0)
			return (print_fork_error(start));
		cmds->out = cmds->pipe_fd[1];
		cmds->next->in = cmds->pipe_fd[0];
		cmds = cmds->next;
	}
	return (0);
}
