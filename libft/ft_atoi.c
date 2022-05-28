/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calecia <calecia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 09:00:48 by vambassa          #+#    #+#             */
/*   Updated: 2022/03/09 19:16:26 by calecia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	size_t			i;
	unsigned long	res;
	unsigned long	limit;
	int				sign;

	sign = 1;
	res = 0;
	limit = (unsigned long)(LIMIT_VALUE / 10);
	i = ft_isspace(str);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		if ((res > limit || (res == limit && (str[i] - '0') > 7)) && sign == 1)
			return (-1);
		if ((res > limit || (res == limit && (str[i] - '0') > 7)) && sign == -1)
			return (0);
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(res * sign));
}
