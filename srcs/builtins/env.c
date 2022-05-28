/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vambassa <vambassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 01:12:25 by vambassa          #+#    #+#             */
/*   Updated: 2022/03/25 22:33:39 by vambassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env_execute(t_env *env)
{
	if (!env || !env->key)
	{
		g_exit_code = 1;
		return ;
	}
	while (env)
	{
		ft_putendl_fd(env->line, STDOUT_FILENO);
		env = env->next;
	}
	g_exit_code = 0;
}
