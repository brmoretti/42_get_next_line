/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoretti <bmoretti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 23:25:38 by bmoretti          #+#    #+#             */
/*   Updated: 2023/10/21 16:57:46 by bmoretti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>     //to remove
#include <strings.h>   //to remove
#define BUFFER_SIZE 1000 // to remove

char	*ft_buffer_leftover(size_t *i, char *buffer, size_t lo_limit)
{
	size_t	j;
	char	*b_leftover;
	char	*ptr;

	if (!lo_limit || *i >= lo_limit)
	{
		*i = 0;
		b_leftover = calloc(1, 1);
		return (b_leftover);
	}
	j = *i;
	while (*i < lo_limit && buffer[*i] != '\n')
		(*i)++;
	b_leftover = malloc((*i - j) + 1);
	if (!b_leftover)
		return (NULL);
	ptr = b_leftover;
	while (j < *i)
		*(ptr++) = buffer[j++];
	*ptr = '\0';
	if (++(*i) > lo_limit)
		*i = 0;
	return (b_leftover);
}


size_t	ft_seek_end_or_backslash_n(char *str, size_t max_len)
{
	size_t	i;

	i = 0;
	while (i < max_len)
	{
		if (str[i++] == '\n')
			return (i - 1);
	}
	return (max_len);
}

int	ft_read_continue(int fd, char *buffer, size_t *n_bytes,
	size_t *end_index)
{
	*n_bytes = read(fd, buffer, BUFFER_SIZE);
	if (*n_bytes == 0)
		return (0);
	*end_index = ft_seek_end_or_backslash_n(buffer, *n_bytes);
	return (1);
}

char	*ft_EOF(char *line)
{
	free(line);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char		buffer[BUFFER_SIZE];
	static size_t	i;
	static size_t	n_bytes;
	size_t			end_index;
	char			*line;

	line = ft_buffer_leftover(&i, buffer, n_bytes);
	if (i || !line)
		return (line);
	if (!ft_read_continue(fd, buffer, &n_bytes, &end_index))
		return (ft_EOF(line));
	while (end_index == n_bytes)
	{
		line = ft_strljoin(&line, buffer, n_bytes);
		if (!line)
			return (NULL);
		if (!ft_read_continue(fd, buffer, &n_bytes, &end_index))
			return (line);
	}
	line = ft_strljoin(&line, buffer, end_index);
	i = end_index + 1;
	return (line);
}
