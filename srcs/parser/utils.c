/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calecia <calecia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:18:45 by calecia           #+#    #+#             */
/*   Updated: 2022/03/24 18:40:48 by calecia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isspace_1(char c)
{
	return (c == ' ' || c == '\n' || c == '\t'
		|| c == '\v' || c == '\f' || c == '\r');
}

static char	*sub_func(char *trim, size_t new_len)
{
	size_t	i;
	char	*ret;

	i = 0;
	ret = malloc((new_len + 1) * sizeof(char));
	if (!ret)
		exit (2);
	ret[new_len + 1] = '\0';
	while (i < new_len + 1)
	{
		if (ft_isspace_1(*trim) && ft_isspace_1(*(trim + 1)))
		{
		}
		else
		{
			if (ft_isspace_1(*trim))
				*trim = ' ';
			ret[i++] = *trim;
		}
		trim++;
	}
	return (ret);
}

char	*clean_space(char *str)
{
	char	*trim;
	char	*ret;
	size_t	i;
	size_t	new_len;

	i = 0;
	new_len = 0;
	if (!str)
		return (NULL);
	trim = ft_strtrim(str, "\t\n\v\f\r ");
	if (!trim)
		return (NULL);
	if (ft_strlen(trim) == 1)
		new_len = 1;
	while (trim && trim[i] && trim[i + 1])
	{
		if (!(ft_isspace_1(trim[i]) && ft_isspace_1(trim[i + 1])))
			new_len++;
		i++;
	}
	ret = sub_func(trim, new_len);
	free(str);
	free(trim);
	return (ret);
}

int	skip_space(char *line, int i)
{
	while (line && line[i] && line[i] == ' ')
		i++;
	return (i);
}
