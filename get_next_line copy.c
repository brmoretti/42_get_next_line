/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line copy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmoretti <brmoretti@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 19:16:35 by brmoretti         #+#    #+#             */
/*   Updated: 2024/01/07 10:57:28 by brmoretti        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*merge_n_right(char *left, char *right, size_t n_right)
{
	char	*merged;
	size_t	size;
	
	size = ft_strlen(left) + n_right + 1;
	merged = malloc(size * sizeof(char));
	if (merged)
	{
		merged[--size] = '\0';
		while (n_right-- && size--)
			merged[size] = right[n_right];
		while (size--)
			merged[size] = left[size];
	}
	free (left);
	return (merged);
}

static char	*ft_merge_till_bslash_n(char *line, t_buffer *buf)
{
	size_t	i;
	size_t	n_right;
	char	*merged;

	i = buf->pos;
	while (buf->buffer[i] && buf->buffer[i] != '\n')
		i++;
	if (buf->buffer[i] == '\n')
	{
		i++;
		buf->bslash = 1;
	}
	n_right = i - buf->pos;
	merged = merge_n_right(line, &buf->buffer[buf->pos], n_right);
	buf->pos = i;
	return (merged);
}

static char	*line_iterative(t_buffer *buf, int fd, char *line)
{
	ssize_t	read_size;

	while (1)
	{
		if (!buf->pos)
		{
			read_size = read(fd, buf->buffer, BUFFER_SIZE);
			if (read_size == -1 || (!read_size && !*line))
			{
				free(line);
				return (NULL);
			}
			if (!read_size)
				return (line);
		}
		line = ft_merge_till_bslash_n(line, buf);
		if (!line || buf->bslash)
			return (line);
		buf->pos = 0;
		ft_bzero(buf->buffer, BUFFER_SIZE);
	}
}

char	*get_next_line(int fd)
{
	static t_buffer		buf;
	static	t_buffer	arr[1024];
	char				*line;

	if (fd < 0 || BUFFER_SIZE < 1 || fd >= 1024)
		return (NULL);
	if (!arr[fd])
	{
		
	}
	line = ft_calloc(1, sizeof(char));
	if (!line)
		return (NULL);
	buf.bslash = 0;
	return (line_iterative(&buf, fd, line));
}
