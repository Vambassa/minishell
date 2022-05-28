/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calecia <calecia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 21:42:30 by calecia           #+#    #+#             */
/*   Updated: 2022/03/24 21:30:47 by calecia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../../includes/minishell.h"

static void	cleaner(t_mini *mini)
{
	t_cmd	*i_cmd;
	t_rdr	*redir;
	int		i;

	i_cmd = mini->cmds;
	redir = mini->cmds->redir;
	while (i_cmd)
	{
		if (i_cmd->command)
		{
			i = 0;
			while (i_cmd->command[i])
			{
				i_cmd->command[i] = lsat_pars(i_cmd->command[i],
						mini->env_copy);
				i++;
			}
		}
		while (redir)
		{
			redir->name = lsat_pars(redir->name, mini->env_copy);
			redir = redir->next;
		}
		i_cmd = i_cmd->next;
	}
}

t_cmd	*pars_cmd(t_mini *mini)
{
	t_arg	*i;
	t_arg	*cmd;

	if (!mini->args)
		return (NULL);
	i = mini->args;
	cmd = i;
	while (i)
	{
		if (!ft_strcmp(i->arg_origin, "|"))
		{
			cmds_lstadd_back(&mini->cmds, cmds_lstnew(cmd));
			cmd = i->next;
		}
		i = i->next;
	}
	cmds_lstadd_back(&mini->cmds, cmds_lstnew(cmd));
	cleaner(mini);
	return (mini->cmds);
}
