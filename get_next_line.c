/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbooke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 21:08:28 by hbooke            #+#    #+#             */
/*   Updated: 2020/11/22 21:08:28 by hbooke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <unistd.h>
#include <stdlib.h>

static int	prepare(int fd, char **line, int *need_line)
{
	if (fd < 0 || !line)
		return (-1);
	*line = malloc(1);
	**line = 0;
	*need_line = 1;
	return (0);
}

static int	check_long_condition(char **p_endl, t_line_buf *line_buf)
{
	return ((*p_endl = ft_memchr(line_buf->buf + line_buf->start, '\n',
								line_buf->readed - line_buf->start)) &&
			line_buf->buf + line_buf->readed >= *p_endl &&
			line_buf->buf + line_buf->start <= *p_endl);
}

static int	ret_line(char **line, char *p_endl, t_line_buf *line_buf)
{
	if (!ft_flush(line, line_buf->buf + line_buf->start,
				p_endl - line_buf->buf - line_buf->start))
		return (-1);
	line_buf->start = (p_endl - line_buf->buf + 1) % BUFFER_SIZE;
	return (1);
}

int			get_next_line(int fd, char **line)
{
	static t_line_buf	fds[MAX_FILES];
	char				*p_endl;
	int					need_line;

	if (prepare(fd, line, &need_line))
		return (-1);
	while (1)
		if (!fds[fd].start && need_line)
		{
			fds[fd].readed = read(fd, fds[fd].buf, BUFFER_SIZE);
			need_line = 0;
			if (fds[fd].readed <= 0)
				return ((fds[fd].readed != 0) * (-1));
		}
		else if (check_long_condition(&p_endl, &fds[fd]))
			return (ret_line(line, p_endl, &fds[fd]));
		else
		{
			if (!ft_flush(line, fds[fd].buf + fds[fd].start,
						fds[fd].readed - fds[fd].start))
				return (-1);
			fds[fd].start = 0;
			need_line = 1;
		}
}
