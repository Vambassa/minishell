/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_parser_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vambassa <vambassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:45:58 by calecia           #+#    #+#             */
/*   Updated: 2022/03/28 22:28:38 by vambassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "parser.h"

char	*proc_dollar(char *line, int *i, t_env *env);

static char	*proc_str(char *line, int start, int end)
{
	char	*t1;
	char	*t2;
	char	*t3;

	t1 = ft_substr(line, 0, start);
	if (!t1)
		return (NULL);
	t2 = ft_substr(line, start + 1, end - start - 1);
	if (!t2)
		return (NULL);
	t3 = ft_strdup(line + end + 1);
	if (!t3)
		return (NULL);
	free (line);
	line = NULL;
	line = ft_strjoin_joiner_str(t1, t2, t3);
	free(t1);
	free(t2);
	free(t3);
	return (line);
}

static char	*proc_quote(char *line, int *i)
{
	int	start;

	start = *i;
	while (line[++(*i)])
	{
		if (line[*i] == '\'')
			break ;
	}
	line = proc_str(line, start, *i);
	return (line);
}

static char	*proc_slash(char *line, int *i)
{
	char	*t1;
	char	*t2;

	t1 = ft_substr(line, 0, *i);
	if (!t1)
		return (NULL);
	t2 = ft_strdup(line + *i + 1);
	if (!t2)
		return (NULL);
	line = NULL;
	line = ft_strjoin(t1, t2);
	free(t2);
	if (!line)
		return (NULL);
	(*i)++;
	return (line);
}

static char	*proc_quote_2(char *line, int *i, t_env *env)
{
	int	start;

	start = *i;
	while (line[++(*i)])
	{
		if (line[*i] == '\\' && (line[*i + 1] == '\"'
				|| line[*i + 1] == '$' || line[*i + 1 == '\\']))
		{
			line = proc_slash(line, i);
		}
		else if (line[*i] == '$')
		{
			line = proc_dollar(line, i, env);
		}
		else if (line[*i] == '\"')
		{
			break ;
		}
	}
	line = proc_str(line, start, *i);
	return (line);
}

char	*lsat_pars(char *line, t_env *env)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			line = proc_dollar(line, &i, env);
		}
		else if (line[i] == '\\')
		{
			line = proc_slash(line, &i);
		}
		else if (line[i] == '\'')
		{
			line = proc_quote(line, &i);
		}
		else if (line[i] == '\"')
		{
			line = proc_quote_2(line, &i, env);
		}
		i++;
	}
	return (line);
}
