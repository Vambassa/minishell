/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calecia <calecia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 01:13:51 by vambassa          #+#    #+#             */
/*   Updated: 2022/03/24 17:49:38 by calecia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_arg	*args_lstnew(char *arg_str)
{
	t_arg	*element;

	element = (t_arg *)malloc(sizeof(t_arg));
	if (!element)
		return (NULL);
	element->arg_origin = ft_strdup(arg_str);
	element->redirect = 0;
	element->next = NULL;
	free(arg_str);
	return (element);
}

void	args_lstadd_back(t_arg	**list, t_arg *new)
{
	t_arg	*last;

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

void	args_lstdelnode(t_arg **args)
{
	t_arg	*next;

	if (!args || !(*args))
		return ;
	next = (*args)->next;
	free((*args)->arg_origin);
	(*args)->arg_origin = NULL;
	free((*args));
	*args = next;
}
