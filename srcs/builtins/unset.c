/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calecia <calecia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 01:12:44 by vambassa          #+#    #+#             */
/*   Updated: 2022/03/28 20:47:59 by calecia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	delete_env_list(t_env *elem)
{
	if (!elem)
		return ;
	free(elem->line);
	free(elem->key);
	free(elem->value);
	free(elem);
}

void	delete_var(t_env **var_before_del)
{
	t_env	*del_var;

	del_var = (*var_before_del)->next;
	(*var_before_del)->next = (*var_before_del)->next->next;
	delete_env_list(del_var);
}

void	delete_var_from_env(t_env **env, int index)
{
	t_env	*tmp_del;

	tmp_del = NULL;
	if (!env || !(*env))
		return ;
	if (!index)
	{
		tmp_del = *env;
		*env = (*env)->next;
		delete_env_list(tmp_del);
	}
	else
	{
		tmp_del = (*env);
		while (index != 1)
		{
			tmp_del = tmp_del->next;
			index--;
		}
		delete_var(&tmp_del);
	}
}

int	find_var_in_env(t_env *env, char *var)
{
	t_env	*tmp_env;
	int		env_ind;

	env_ind = 0;
	tmp_env = env;
	while (tmp_env)
	{
		if (!ft_strcmp(tmp_env->key, var))
			return (env_ind);
		tmp_env = tmp_env->next;
		env_ind++;
	}
	return (-1);
}

void	unset_execute(t_mini *shell, char **cmds)
{
	int	i;
	int	index;

	i = 1;
	if (count_args(cmds) > 1)
	{
		while (cmds[i])
		{
			if (ft_isdigit(cmds[i][0]))
			{
				print_unset_error(cmds[i]);
				return ;
			}
			index = find_var_in_env(shell->env_copy, cmds[i]);
			if (index != -1)
			{
				delete_var_from_env(&shell->env_copy, index);
				index = find_var_in_env(shell->env, cmds[i]);
				delete_var_from_env(&shell->env, index);
			}
			i++;
		}
	}
	g_exit_code = 0;
}
