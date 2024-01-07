/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmoretti <brmoretti@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 19:16:35 by brmoretti         #+#    #+#             */
/*   Updated: 2024/01/06 23:54:48 by brmoretti        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_join_till_bslash_n(char *line, char **buffer)
{
	char		*p;
	char		*joined;
	ssize_t		i;
	ssize_t		size;

	p = *buffer;
	while (*p && *p != '\n')
		p++;
	if (*p == '\n')
		p++;
	i = (size_t)(p - *buffer);
	size = ft_strlen(line) + i + 1;
	joined = malloc(size * sizeof(char));
	if (!joined)
		return (NULL);
	joined[--size] = '\0';
	while (i-- && size--)
		joined[size] = (*buffer)[i];
	while (size--)
		joined[size] = line[size];
	free (line);
	*buffer = p;
	if (!**buffer)
		*buffer = NULL;
	return (joined);
}

static char	*line_iterative(t_buffer *buffer, int fd, char *line)
{
	ssize_t	read_size;

	while (1)
	{
		if (!buffer->p)
		{
			read_size = read(fd, buffer->buffer, BUFFER_SIZE);
			if (read_size == -1 || (!read_size && !*line))
			{
				free(line);
				return (NULL);
			}
			if (!read_size)
				return (line);
			buffer->p = buffer->buffer;
		}
		line = ft_join_till_bslash_n(line, &(buffer->p));
		if (!line || buffer->p)
			return (line);
		ft_bzero(buffer->buffer, BUFFER_SIZE);
	}
}

char	*get_next_line(int fd)
{
	static t_buffer	buf;
	char			*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	line = ft_calloc(1, sizeof(char));
	if (!line)
		return (NULL);
	return (line_iterative(&buf, fd, line));
}
