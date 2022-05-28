/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_shlvl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vambassa <vambassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:20:30 by calecia           #+#    #+#             */
/*   Updated: 2022/03/28 13:41:10 by vambassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	define_shell_level(t_mini *shell)
{
	int		cur_lvl;
	int		next;
	char	*next_lvl;

	cur_lvl = ft_atoi(cd_find_key_value(shell->env, "SHLVL"));
	next = cur_lvl + 1;
	if (next >= 1001)
	{
		ft_putstr_fd("minishell: warning: ", STDOUT_FILENO);
		ft_putstr_fd("shell level (", STDOUT_FILENO);
		ft_putstr_fd(ft_itoa(next), STDOUT_FILENO);
		ft_putendl_fd(") too high, resetting to 1", STDOUT_FILENO);
		next = 1;
	}
	else if (next < 0)
		next = 0;
	next_lvl = ft_itoa(next);
	change_env_value(shell->env, "SHLVL", next_lvl);
	change_env_value(shell->env_copy, "SHLVL", next_lvl);
	free(next_lvl);
	g_exit_code = 0;
}
