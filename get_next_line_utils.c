/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbooke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 21:08:28 by hbooke            #+#    #+#             */
/*   Updated: 2020/11/22 21:08:28 by hbooke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t		ft_strlen(const char *str)
{
	int res;

	res = 0;
	while (*str++)
		++res;
	return (res);
}

char		*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char*)s);
		++s;
	}
	return (NULL);
}

void		*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char *p1;
	unsigned char *p2;

	p1 = (unsigned char*)dest;
	p2 = (unsigned char*)src;
	if (!p1 && !p2 && n)
		return (NULL);
	while (n--)
		*p1++ = *p2++;
	return (dest);
}

void		*ft_realloc(void *ptr, size_t old_size, size_t size)
{
	void	*res;

	res = NULL;
	if (!size)
		free(ptr);
	else if (!ptr)
		res = malloc(size);
	else if (size <= old_size)
		res = ptr;
	else if (ptr && size > old_size)
	{
		res = malloc(size);
		if (res)
		{
			ft_memcpy(res, ptr, old_size);
			free(ptr);
		}
	}
	return (res);
}

void		*ft_flush(char **line, char *buf, size_t len)
{
	size_t	line_len;

	line_len = (*line) ? ft_strlen(*line) : 0;
	*line = (char*)ft_realloc(*line, line_len + 1, line_len + len + 1);
	if (*line)
	{
		ft_memcpy(*line + line_len, buf, len);
		*(*line + line_len + len) = 0;
	}
	return (*line);
}
