/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calecia <calecia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 01:14:20 by vambassa          #+#    #+#             */
/*   Updated: 2022/03/28 21:01:02 by calecia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_rdr(t_rdr **arg)
{
	t_rdr	*tmp;

	if (arg && (*arg))
	{
		while (*arg)
		{
			tmp = (*arg)->next;
			free((*arg)->type);
			free((*arg)->name);
			free(*arg);
			*arg = tmp;
		}
	}
}

static void	delete_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd)
	{
		while (cmd->command[i])
		{
			free(cmd->command[i]);
			i++;
		}
		free(cmd->command);
		if (cmd->redir)
			free_rdr(&cmd->redir);
		free(cmd);
	}
}

void	free_cmds(t_cmd	**cmds)
{
	t_cmd	*tmp;

	while (cmds && (*cmds))
	{
		tmp = (*cmds)->next;
		delete_cmd(*cmds);
		*cmds = tmp;
	}
}

void	free_args(t_arg **args)
{
	t_arg	*tmp;

	if (args && (*args))
	{
		while (*args)
		{
			tmp = (*args)->next;
			free((*args)->arg_origin);
			free(*args);
			*args = tmp;
		}
	}
}
