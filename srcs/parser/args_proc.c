/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vambassa <vambassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:48:44 by calecia           #+#    #+#             */
/*   Updated: 2022/03/28 21:21:44 by vambassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "norme.h"

static int	search_end(const char *line, int *flag, int i)
{
	char	qt;

	while (line && line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			qt = line[i];
			i++;
			while (line[i] && line[i] != qt)
				i++;
		}
		if (ft_strchr("<|> \t", line[i]))
		{
			if (ft_strchr("<>|", line[i]))
				*flag = 1;
			if (ft_strchr("<>", line[i]) && ft_strchr("<>", line[i + 1]))
				*flag = 2;
			return (i);
		}
		i++;
	}
	return (i);
}

static void	split(t_arg **args, char *line, t_norme n)
{
	while (line && line[n.i])
	{
		n.i = skip_space(line, n.i);
		n.start = n.i;
		n.end = search_end(line, &(n.flag), n.i);
		n.i = n.end;
		n.i = skip_space(line, n.end);
		if (n.flag != 0)
		{
			n.temp = ft_substr(line, n.start, n.end - n.start);
			if (n.temp == NULL || n.temp[0] == '\0')
				free (n.temp);
			else
				args_lstadd_back(args, args_lstnew(n.temp));
			args_lstadd_back(args, args_lstnew(ft_substr(line, n.end, n.flag)));
			n.i += n.flag;
			n.flag = 0;
		}
		else
			args_lstadd_back(args, args_lstnew(
					ft_substr(line, n.start, n.end - n.start)));
	}
}

static int	redirect_check(char *arg)
{
	if (!ft_strcmp(arg, "<") || !ft_strcmp(arg, "<<")
		|| !ft_strcmp(arg, ">") || !ft_strcmp(arg, ">>"))
		return (1);
	return (0);
}

static void	redirect(t_arg *arg)
{
	while (arg)
	{
		if (redirect_check(arg->arg_origin))
		{
			arg->redirect = 1;
			arg->next->redirect = 2;
			arg = arg->next->next;
		}
		else
			arg = arg->next;
	}
}

t_arg	*args_proc(t_mini *shell)
{
	t_norme	norme;

	norme.i = 0;
	norme.start = 0;
	norme.end = 0;
	norme.flag = 0;
	split(&shell->args, shell->input, norme);
	redirect(shell->args);
	return (shell->args);
}
