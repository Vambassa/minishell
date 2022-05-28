/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vambassa <vambassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 01:13:10 by vambassa          #+#    #+#             */
/*   Updated: 2022/03/26 13:21:56 by vambassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_in_env(t_env *env, char *key)
{
	if (!env || !key)
		return (NULL);
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	**get_paths(t_mini *shell)
{
	char	*path_value;
	char	**paths;

	path_value = find_in_env(shell->env, "PATH");
	if (!path_value)
		return (NULL);
	paths = ft_split(path_value, ':');
	return (paths);
}

char	*find_path(t_mini *shell, char *line)
{
	int		it;
	char	*path;
	char	**paths;

	it = 0;
	if (str_find_chr(line, '/') > -1)
		return (line);
	paths = get_paths(shell);
	if (!paths)
		return (NULL);
	while (paths[it])
	{
		path = ft_strjoin_joiner(paths[it], line, '/');
		if (!access(path, F_OK))
		{
			free_array(paths);
			return (path);
		}
		free(path);
		it++;
	}
	free_array(paths);
	return (NULL);
}
