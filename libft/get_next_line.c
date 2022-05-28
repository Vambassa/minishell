/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vambassa <vambassa@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 13:54:37 by vambassa          #+#    #+#             */
/*   Updated: 2022/02/09 09:47:44 by vambassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_read_from_file(int fd, char *buffer)
{
	char	*tmp_buf;
	int		r;

	tmp_buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp_buf)
		return (NULL);
	r = 1;
	while (!ft_strchr(buffer, '\n') && r > 0)
	{
		r = read(fd, tmp_buf, BUFFER_SIZE);
		if (r == -1)
		{
			free(tmp_buf);
			return (NULL);
		}
		tmp_buf[r] = '\0';
		buffer = ft_strjoin(buffer, tmp_buf);
	}
	free(tmp_buf);
	return (buffer);
}

static char	*ft_get_line(char *buffer)
{
	char	*result;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	result = (char *)malloc(sizeof(char) * (i + 2));
	if (!result)
		return (NULL);
	ft_memmove(result, buffer, i);
	if (buffer[i] == '\n')
	{
		result[i] = '\n';
		i++;
	}
	result[i] = '\0';
	return (result);
}

static char	*ft_next_line(char *buffer)
{
	int		i;
	int		j;
	char	*new_buffer;

	i = 0;
	j = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = (char *)malloc(sizeof(char) * (ft_strlen(buffer) - i + 1));
	if (!new_buffer)
		return (NULL);
	i++;
	while (buffer[i])
		new_buffer[j++] = buffer[i++];
	new_buffer[j] = '\0';
	free(buffer);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	char		*result;
	static char	*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_read_from_file(fd, buffer);
	if (!buffer)
		return (NULL);
	result = ft_get_line(buffer);
	buffer = ft_next_line(buffer);
	return (result);
}
