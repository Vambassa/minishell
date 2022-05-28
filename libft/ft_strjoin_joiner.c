/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_joiner.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calecia <calecia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:00:39 by vambassa          #+#    #+#             */
/*   Updated: 2022/03/23 19:04:56 by calecia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_joiner(char *str1, char *str2, char joiner)
{
	char	*s;
	int		i;
	int		j;

	if (!str1 || !str2)
		return (NULL);
	s = (char *)malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 2));
	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	while (str1[i])
	{
		s[i] = str1[i];
		i++;
	}
	s[i++] = joiner;
	while (str2[j])
		s[i++] = str2[j++];
	s[i] = '\0';
	return (s);
}
