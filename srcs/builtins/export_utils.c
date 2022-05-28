/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vambassa <vambassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 01:12:37 by vambassa          #+#    #+#             */
/*   Updated: 2022/03/25 23:05:45 by vambassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*create_mew_var(char *new_var)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->line = ft_strdup(new_var);
	new->key = define_env_key(new_var);
	new->value = define_env_value(new_var, new->key);
	new->next = NULL;
	return (new);
}

void	add_new_var(t_env **vars, t_env *new)
{
	t_env	*last;

	if (!vars || !new)
		exit(EXIT_FAILURE);
	if (*vars)
	{
		last = *vars;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	else
		*vars = new;
}

int	invalid_export_var(char *var)
{
	ft_putstr_fd ("minishell: export `", STDERR_FILENO);
	ft_putstr_fd(var, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	g_exit_code = 1;
	return (1);
}

void	print_export_vars(t_env *var)
{
	if (!var)
		return ;
	while (var)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(var->key, STDOUT_FILENO);
		if (var->value)
		{
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
			ft_putstr_fd(var->value, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		var = var->next;
	}
}

int	key_in_env_vars(char *key, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
