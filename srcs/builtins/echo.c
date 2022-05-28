/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vambassa <vambassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 01:12:19 by vambassa          #+#    #+#             */
/*   Updated: 2022/03/28 22:33:11 by vambassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	echo_execute(char **cmds)
{
	int	i;
	int	option;

	option = NO;
	i = 1;
	while (!ft_strcmp("-n", cmds[i]))
	{
		option = YES;
		i++;
	}
	while (cmds[i])
	{
		if (ft_strcmp("\"", cmds[i]) == 0)
			cmds[i][0] = '\0';
		ft_putstr_fd(cmds[i], STDOUT_FILENO);
		i++;
		if (cmds[i])
			ft_putstr_fd(" ", STDOUT_FILENO);
		else
			break ;
	}
	if (option == NO)
		ft_putstr_fd("\n", STDOUT_FILENO);
	g_exit_code = 0;
}
