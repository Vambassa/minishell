/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vambassa <vambassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 01:12:53 by vambassa          #+#    #+#             */
/*   Updated: 2022/03/25 23:08:19 by vambassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*define_env_value(char *env_var, char *key)
{
	int		i;
	char	*value;

	i = 0;
	if (!ft_strcmp(key, "OLDPWD"))
		value = NULL;
	else
	{
		while (env_var[i] && env_var[i] != '=')
			i++;
		if (!env_var[i])
			value = NULL;
		else
			value = ft_strdup(&env_var[i + 1]);
	}
	return (value);
}

char	*define_env_key(char *env_var)
{
	int		i;
	char	*key;

	i = 0;
	while (env_var[i] && env_var[i] != '=')
		i++;
	key = ft_substr(env_var, 0, i);
	return (key);
}

void	init_env(t_mini *shell, char **env)
{
	int		i;
	t_env	*start_env;

	i = 1;
	start_env = (t_env *)malloc(sizeof(t_env));
	if (!start_env)
		exit(EXIT_FAILURE);
	start_env->line = ft_strdup(env[0]);
	start_env->key = define_env_key(env[0]);
	start_env->value = define_env_value(env[0], start_env->key);
	start_env->next = NULL;
	shell->env = start_env;
	while (env[i])
	{
		start_env->next = (t_env *) malloc(sizeof (t_env));
		if (!start_env->next)
			exit(EXIT_FAILURE);
		start_env->next->line = ft_strdup(env[i]);
		start_env->next->key = define_env_key(env[i]);
		start_env->next->value = define_env_value(env[i], start_env->next->key);
		start_env->next->next = NULL;
		start_env = start_env->next;
		i++;
	}
}

void	init_export_env(t_mini *shell, char **env)
{
	int		i;
	t_env	*start_env;

	i = 1;
	start_env = (t_env *)malloc(sizeof(t_env));
	if (!start_env)
		exit(EXIT_FAILURE);
	start_env->line = ft_strdup(env[0]);
	start_env->key = define_env_key(env[0]);
	start_env->value = define_env_value(env[0], start_env->key);
	start_env->next = NULL;
	shell->env_copy = start_env;
	while (env[i])
	{
		start_env->next = (t_env *) malloc(sizeof (t_env));
		if (!start_env->next)
			exit(EXIT_FAILURE);
		start_env->next->line = ft_strdup(env[i]);
		start_env->next->key = define_env_key(env[i]);
		start_env->next->value = define_env_value(env[i], start_env->next->key);
		start_env->next->next = NULL;
		start_env = start_env->next;
		i++;
	}
}
