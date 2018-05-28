/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 11:48:49 by dslogrov          #+#    #+#             */
/*   Updated: 2018/05/28 18:26:48 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static char		*get_file_buffer(size_t fd, t_list *start)
{
	t_list	*tmp;

	tmp = start;
	while (tmp)
	{
		if (tmp->content_size == fd)
			return (tmp->content);
		tmp = tmp->next;
	}
	tmp = ft_lstnew(NULL, fd);
	ft_lstadd(&start, tmp);
	return (tmp->content);
}

static size_t	ft_endl_pos(const char *s)
{
	char	*c;

	c = (char *)s;
	while (*c && *c != '\n')
		c++;
	return (c - s);
}

int				get_next_line(const int fd, char **line)
{
	char			local_buffer[BUFF_SIZE + 1];
	size_t			bytes_read;
	static t_list	*buffer_list;
	char			*temp;
	char			*f_buf;

	f_buf = get_file_buffer(fd, buffer_list);
	if (fd < 0 || line == NULL || read(fd, local_buffer, 0) < 0)
		return (-1);
	if (!f_buf)
		f_buf = ft_strnew(1);
	while ((bytes_read = read(fd, local_buffer, BUFF_SIZE)))
	{
		local_buffer[bytes_read] = 0;
		temp = ft_strjoin(f_buf, local_buffer);
		free(f_buf);
		f_buf = temp;
		//if (!f_buf)
		//	return (-1);
		if (ft_strchr(f_buf, '\n'))
			break ;
	}
	if (bytes_read < BUFF_SIZE && !f_buf)
		return (0);
	*line = ft_strndup(f_buf, ft_endl_pos(f_buf));
	if (ft_strlen(*line) <= ft_strlen(f_buf))
	{
		temp = ft_strdup(f_buf + ft_strlen(*line) + 1);
		free(f_buf);
		f_buf = temp;
	}
	else
		ft_strdel((char **)&f_buf);
	return (1);
}
