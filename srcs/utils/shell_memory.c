/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calecia <calecia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 01:14:07 by vambassa          #+#    #+#             */
/*   Updated: 2022/03/28 20:58:07 by calecia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_shell(t_mini *shell)
{
	if (shell->input)
		free(shell->input);
	if (shell->args)
		free_args(&shell->args);
	if (shell->cmds)
		free_cmds(&shell->cmds);
}

void	init_shell(t_mini *shell)
{
	shell->input = NULL;
	shell->env = NULL;
	shell->env_copy = NULL;
	shell->args = NULL;
	shell->cmds = NULL;
}
