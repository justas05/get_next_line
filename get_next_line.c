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

int		ft_extract_line(t_line_buf *fds, char **line, int fd)
{
	char	*p_endl;

	if (!(p_endl = ft_strchr(fds[fd].buf + fds[fd].start, '\n')) ||
		fds[fd].buf + fds[fd].readed < p_endl)
	{
		if (!ft_flush(line, fds[fd].buf + fds[fd].start,
			fds[fd].readed - fds[fd].start))
			return (-1);
		fds[fd].start = 0;
		return (1);
	}
	else if (fds[fd].buf + fds[fd].start <= p_endl)
	{
		if (!ft_flush(line, fds[fd].buf + fds[fd].start,
				p_endl - fds[fd].buf - fds[fd].start))
			return (-1);
		fds[fd].start = (p_endl - fds[fd].buf + 1) % BUFFER_SIZE;
		return (1);
	}
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static t_line_buf	fds[MAX_FILES];
	int					request_new_line;

	if (fd < 0)
		return (-1);
	request_new_line = 1;
	while (fds[fd].readed != -1)
	{
		if (!fds[fd].start && request_new_line == 1)
		{
			fds[fd].readed = read(fd, fds[fd].buf, BUFFER_SIZE);
			request_new_line = 0;
		}
		else if (fds[fd].readed == 0)
			return (0);
		else if (ft_extract_line(fds, line, fd) > 0)
			return (1);
		else
			request_new_line = 1;
	}
	return (-1);
}
