/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calecia <calecia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:58:03 by calecia           #+#    #+#             */
/*   Updated: 2022/03/28 20:11:05 by calecia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "parser.h"

static char	*proc_string(char *line, int start, int end, t_env *env)
{
	char	*str;
	char	*t1;
	char	*t2;
	char	*t3;
	char	*ret;

	str = ft_substr(line, start + 1, end - start - 1);
	t1 = ft_substr(line, 0, start);
	t2 = ft_strdup (line + end);
	free (line);
	line = NULL;
	t3 = ft_strdup(find_in_env(env, str));
	free(str);
	if (t3 == NULL)
		ret = ft_strjoin(t1, t2);
	else
	{
		ret = ft_strjoin_joiner_str(t1, t3, t2);
		free(t1);
	}
	free(t2);
	free(t3);
	return (ret);
}

static char	*proc_quest(char *line, int *i, int start)
{
	char	*ret;
	char	*t1;
	char	*t2;
	char	*ex_code;
	char	*tail;

	ex_code = ft_itoa(g_exit_code);
	t1 = ft_substr(line, 0, start);
	if (!t1)
		return (NULL);
	t2 = ft_strjoin(t1, ex_code);
	tail = ft_strdup(line + *i);
	free(line);
	if (!t2 || !tail)
		return (NULL);
	ret = ft_strjoin(t2, tail);
	free(tail);
	if (!ret)
		return (NULL);
	g_exit_code = 0;
	return (ret);
}

static int	check_c(char c)
{
	return (c == '_' || ft_isalnum(c));
}

char	*proc_dollar(char *line, int *i, t_env *env)
{
	int	start;

	start = *i;
	if (ft_strchr("?", line[start + 1]))
	{
		(*i) += 2;
		return (proc_quest(line, i, start));
	}
	while (line[++(*i)])
	{
		if (!check_c(line[*i]))
			break ;
	}
	if (*i == start + 1)
		return (line);
	return (proc_string(line, start, *i, env));
}
