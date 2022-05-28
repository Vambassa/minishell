/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vambassa <vambassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:20:30 by calecia           #+#    #+#             */
/*   Updated: 2022/03/28 12:54:53 by vambassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_full_command(t_arg *args)
{
	int		quantity;
	t_arg	*tmp;

	if (!args)
		return (0);
	tmp = args;
	quantity = 1;
	if (ft_strcmp("|", tmp->arg_origin) == 0)
		return (0);
	while (tmp->next)
	{
		tmp = tmp->next;
		if (ft_strcmp(tmp->arg_origin, "|") == 0)
			return (quantity);
		quantity++;
	}
	return (quantity);
}

char	**write_cmd_to_array(t_arg *args, int quantity_lists)
{
	int		it;
	char	**arg_arr;

	it = 0;
	arg_arr = malloc(sizeof(char *) * (quantity_lists + 1));
	if (!arg_arr)
		return (NULL);
	while (args && (quantity_lists != 0))
	{
		arg_arr[it] = ft_strdup(args->arg_origin);
		it++;
		quantity_lists--;
		args = args->next;
	}
	arg_arr[it] = NULL;
	return (arg_arr);
}

t_cmd	*cmds_lstnew(t_arg *args)
{
	t_cmd	*element;
	int		quantity_lists;

	element = (t_cmd *)malloc(sizeof(t_cmd));
	if (!element || !args)
		return (NULL);
	element->redir = NULL;
	element->redir = redirect_processing(&args);
	quantity_lists = find_full_command(args);
	element->command = write_cmd_to_array(args, quantity_lists);
	element->in = 0;
	element->out = 1;
	element->fork = 0;
	element->pipe_fd[0] = 0;
	element->pipe_fd[1] = 0;
	element->next = NULL;
	return (element);
}

void	cmds_lstadd_back(t_cmd	**list, t_cmd *new)
{
	t_cmd	*last;

	if (!list || !new)
		exit(EXIT_FAILURE);
	if (*list)
	{
		last = *list;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	else
		*list = new;
}
