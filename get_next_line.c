/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 11:48:49 by dslogrov          #+#    #+#             */
/*   Updated: 2018/05/28 17:06:23 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

size_t	ft_endl_pos(const char *s)
{
	char	*c;

	c = (char *)s;
	while (*c && *c != '\n')
		c++;
	return (c - s);
}

int		get_next_line(const int fd, char **line)
{
	char		buffer[BUFF_SIZE + 1];
	size_t		bytes_read;
	static char	*read_string;
	char		*temp;

	if (fd < 0 || line == NULL || read(fd, buffer, 0) < 0)
		return (-1);
	if (!read_string)
		read_string = ft_strnew(1);
	while ((bytes_read = read(fd, buffer, BUFF_SIZE)))
	{
		buffer[bytes_read] = 0;
		temp = ft_strjoin(read_string, buffer);
		free(read_string);
		read_string = temp;
		if (!read_string)
			return (-1);
		if (ft_strchr(read_string, '\n'))
			break ;
	}
	if (bytes_read < BUFF_SIZE && !*read_string)
		return (0);
	*line = ft_strndup(read_string, ft_endl_pos(read_string));
	if (ft_strlen(*line) <= ft_strlen(read_string))
	{
		temp = ft_strdup(read_string + ft_strlen(*line) + 1);
		free(read_string);
		read_string = temp;
	}
	else
		ft_strdel(&read_string);
	return (1);
}
