/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vambassa <vambassa@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:01:38 by vambassa          #+#    #+#             */
/*   Updated: 2022/02/09 09:47:44 by vambassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_set(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		s1_len;
	int		j;

	i = 0;
	s1_len = ft_strlen(s1);
	while (s1[i] && ft_check_set(set, s1[i]) == 1)
		i++;
	while (s1_len > i && ft_check_set(set, s1[s1_len - 1]) == 1)
		s1_len--;
	str = (char *)malloc(sizeof(char) * (s1_len - i + 1));
	if (!str)
		return (NULL);
	j = 0;
	while (i < s1_len)
	{
		str[j] = s1[i];
		j++;
		i++;
	}
	str[j] = '\0';
	return (str);
}
