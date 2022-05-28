/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vambassa <vambassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 01:12:49 by vambassa          #+#    #+#             */
/*   Updated: 2022/03/25 23:07:36 by vambassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	env_lstsize(t_env *env)
{
	int		count;

	if (!env)
		return (-1);
	count = 0;
	while (env)
	{
		env = env->next;
		count++;
	}
	return (count);
}

int	str_find_chr(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (-1);
}

void	change_env_value(t_env *env, char *key, char *value)
{
	if (!env || !key || !value)
		return ;
	while (env)
	{
		if (!ft_strcmp(env->key, key))
		{
			if (env->line)
				free(env->line);
			env->line = ft_strjoin_joiner(key, value, '=');
			if (env->value)
				free(env->value);
			env->value = ft_strdup(value);
			return ;
		}
		env = env->next;
	}
}
