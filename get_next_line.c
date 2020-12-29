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

int		get_next_line(int fd, char **line)
{
	static t_line_buf	fds[MAX_FILES];
	char				*p_endl;
	int					need_line;

	if (fd < 0 || !line)
		return (-1);
	*line = malloc(1);
	**line = 0;
	need_line = 1;
	while (1)
	{
		if (!fds[fd].start && need_line)
		{
			fds[fd].readed = read(fd, fds[fd].buf, BUFFER_SIZE);
			if (fds[fd].readed <= 0)
				return ((fds[fd].readed != 0) * (-1));
			need_line = 0;
		}
		else if ((p_endl = ft_memchr(fds[fd].buf + fds[fd].start, '\n', fds[fd].readed - fds[fd].start)) &&
			fds[fd].buf + fds[fd].readed >= p_endl &&
			fds[fd].buf + fds[fd].start <= p_endl)
		{
			if (!ft_flush(line, fds[fd].buf + fds[fd].start,
				p_endl - fds[fd].buf - fds[fd].start))
				return (-1);
			fds[fd].start = (p_endl - fds[fd].buf + 1) % BUFFER_SIZE;
			return (1);
		}
		else
		{
			if (!ft_flush(line, fds[fd].buf + fds[fd].start, fds[fd].readed - fds[fd].start))
				return (-1);
			fds[fd].start = 0;
			need_line = 1;
		}
	}
}
