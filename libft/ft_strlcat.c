/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vambassa <vambassa@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:00:39 by vambassa          #+#    #+#             */
/*   Updated: 2022/02/09 09:47:44 by vambassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	d_len;
	size_t	s_len;
	size_t	src_len;

	d_len = 0;
	s_len = 0;
	while (d_len < dstsize && dst[d_len])
		d_len++;
	while (d_len + s_len + 1 < dstsize && src[s_len])
	{
		dst[d_len + s_len] = src[s_len];
		s_len++;
	}
	if (d_len < dstsize)
		dst[d_len + s_len] = '\0';
	src_len = ft_strlen(src);
	return (d_len + src_len);
}
