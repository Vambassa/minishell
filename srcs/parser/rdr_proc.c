/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_proc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calecia <calecia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 17:34:04 by calecia           #+#    #+#             */
/*   Updated: 2022/03/24 17:37:39 by calecia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redir_lstadd_back(t_rdr **list, t_rdr *new)
{
	t_rdr	*last;

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

t_rdr	*redir_lstnew(char *type, char *name)
{
	t_rdr	*element;

	element = (t_rdr *)malloc(sizeof(t_rdr));
	if (!element)
		return (NULL);
	element->type = ft_strdup(type);
	element->name = ft_strdup(name);
	element->next = NULL;
	return (element);
}

int	first_redirect(t_arg **args, t_rdr **rdr)
{
	while (*args)
	{
		if ((*args)->redirect == 1)
		{
			redir_lstadd_back(rdr, redir_lstnew((*args)->arg_origin, \
			(*args)->next->arg_origin));
			if (!(*args)->next->next)
			{
				(*args) = (*args)->next->next;
				return (1);
			}
			(*args) = (*args)->next->next;
		}
		if ((*args)->redirect == 0)
			break ;
	}
	return (0);
}

t_rdr	*redirect_processing(t_arg **args)
{
	t_rdr	*rdr;
	t_arg	*tmp;

	if (!args || !(*args))
		return (NULL);
	rdr = NULL;
	if (first_redirect(args, &rdr) == 1)
		return (rdr);
	tmp = *args;
	while (tmp->next)
	{
		if (ft_strcmp(tmp->arg_origin, "|") == 0)
			break ;
		if (tmp->next->redirect == 1)
		{
			redir_lstadd_back(&rdr, redir_lstnew(tmp->next->arg_origin, \
			tmp->next->next->arg_origin));
			args_lstdelnode(&tmp->next);
			args_lstdelnode(&tmp->next);
		}
		if (tmp->next && tmp->next->redirect != 1)
			tmp = tmp->next;
	}
	return (rdr);
}
