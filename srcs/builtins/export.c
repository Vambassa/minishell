/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vambassa <vambassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 01:12:32 by vambassa          #+#    #+#             */
/*   Updated: 2022/03/28 22:03:55 by vambassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	swap_env_vars(t_env **env)
{
	t_env	*tmp;

	if ((*env) || (*env)->next || (*env)->next->next)
	{
		tmp = (*env)->next;
		(*env)->next = (*env)->next->next;
		tmp->next = (*env);
		(*env) = tmp;
	}
}

static void	sort_env_export(t_env **env)
{
	t_env	*curr;
	int		is_sorted;

	if (!(*env) || !(*env)->next)
		return ;
	if (ft_strcmp((*env)->key, (*env)->next->key) > 0)
		swap_env_vars(env);
	curr = (*env);
	is_sorted = 0;
	while (curr->next->next)
	{
		if (ft_strcmp(curr->next->key, curr->next->next->key) > 0)
		{
			swap_env_vars(&(curr->next));
			is_sorted = 1;
		}
		curr = curr->next;
	}
	if (is_sorted)
		sort_env_export(env);
	return ;
}

static int	check_export_var(char *var)
{
	int	i;

	i = 0;
	if ((!ft_isalpha(var[0]) && var[0] != '_') || var[0] == '=')
		return (invalid_export_var(var));
	i++;
	while (var[i] && var[i] != '=')
	{
		if (!ft_isdigit(var[i]) && !ft_isalpha(var[i]) && var[i] != '_')
			return (invalid_export_var(var));
		i++;
	}
	return (0);
}

static char	*fix_norme(char **cmds, t_mini **shell, char **key, int *i)
{
	char	*value;

	if (check_export_var(cmds[*i]))
		return (NULL);
	*key = define_env_key(cmds[*i]);
	value = define_env_value(cmds[*i], *key);
	if (key_in_env_vars(*key, (*shell)->env_copy))
	{
		change_env_value((*shell)->env_copy, *key, value);
		change_env_value((*shell)->env, *key, value);
	}
	else
	{
		add_new_var(&((*shell)->env_copy), create_mew_var(cmds[*i]));
		if (str_find_chr(cmds[*i], '=') == 1)
			add_new_var(&((*shell)->env), create_mew_var(cmds[*i]));
	}
	return (value);
}

void	export_execute(t_mini *shell, char **cmds)
{
	int		i;
	char	*key;
	char	*value;

	i = 1;
	if (count_args(cmds) == 1)
	{
		sort_env_export(&shell->env_copy);
		print_export_vars(shell->env_copy);
	}
	else
	{
		while (cmds[i])
		{
			value = fix_norme(cmds, &shell, &key, &i);
			if (!value)
				return ;
			free(key);
			if (value)
				free(value);
			i++;
		}
	}
	g_exit_code = 0;
}
