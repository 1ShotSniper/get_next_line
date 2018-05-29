/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 11:48:49 by dslogrov          #+#    #+#             */
/*   Updated: 2018/05/29 11:57:00 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static t_list	*get_file_buffer(size_t fd, t_list **start)
{
	t_list	*tmp;

	tmp = *start;
	while (tmp)
	{
		if (tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = ft_lstnew("\0", fd);
	ft_lstadd(start, tmp);
	return (tmp);
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
	t_list			*f_buf;

	if (fd < 0 || line == NULL || read(fd, local_buffer, 0) < 0)
		return (-1);
	f_buf = get_file_buffer(fd, &buffer_list);
	if (!f_buf->content)
		f_buf->content = ft_strnew(1);
	while ((bytes_read = read(fd, local_buffer, BUFF_SIZE)))
	{
		local_buffer[bytes_read] = 0;
		temp = ft_strjoin(f_buf->content, local_buffer);
		free(f_buf->content);
		f_buf->content = temp;
		if (!f_buf->content)
			return (-1);
		if (ft_strchr(f_buf->content, '\n'))
			break ;
	}
	if (bytes_read < BUFF_SIZE && !*(char *)(f_buf->content))
		return (0);
	*line = ft_strndup(f_buf->content, ft_endl_pos(f_buf->content));
	if (ft_strlen(*line) < ft_strlen(f_buf->content))
	{
		temp = ft_strdup(f_buf->content + ft_strlen(*line) + 1);
		free(f_buf->content);
		f_buf->content = temp;
	}
	else
		ft_strdel((char **)&f_buf->content);
	return (1);
}
