/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calecia <calecia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 01:12:41 by vambassa          #+#    #+#             */
/*   Updated: 2022/03/28 20:48:10 by calecia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd_execute(void)
{
	char	dir[PATH_MAX];

	if (getcwd(dir, PATH_MAX))
		ft_putendl_fd(dir, STDOUT_FILENO);
	else
	{
		g_exit_code = 1;
		return ;
	}
	g_exit_code = 0;
}

int	print_unset_error(char *str)
{
	ft_putstr_fd("minishell: unset: '", STDOUT_FILENO);
	ft_putstr_fd(str, STDOUT_FILENO);
	ft_putendl_fd("': not a valid identifier", STDOUT_FILENO);
	g_exit_code = 1;
	return (g_exit_code);
}
