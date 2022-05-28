/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vambassa <vambassa@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:00:05 by vambassa          #+#    #+#             */
/*   Updated: 2022/02/09 09:47:44 by vambassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_delimiter(char s, char c)
{
	if (s == c || s == '\0')
		return (1);
	return (0);
}

static int	ft_words_count(const char *str, char c)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	while (str[i])
	{
		if (ft_check_delimiter(str[i], c) == 0
			&& ft_check_delimiter(str[i + 1], c) == 1)
			words++;
		i++;
	}
	return (words);
}

static int	ft_wordlen(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static char	**ft_free_space(char **result)
{
	int	i;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	int		begin;
	int		i;
	char	**result;

	words = ft_words_count(s, c);
	result = (char **)malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	i = 0;
	begin = 0;
	while (s[begin] == c)
		begin++;
	while (i < words)
	{
		result[i] = ft_substr(s, begin, ft_wordlen(&s[begin], c));
		if (!result[i])
			return (ft_free_space(result));
		begin += ft_wordlen(&s[begin], c);
		while (s[begin] == c)
			begin++;
		i++;
	}
	result[i] = NULL;
	return (result);
}
