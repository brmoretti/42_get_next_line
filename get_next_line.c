/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoretti <bmoretti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 23:25:38 by bmoretti          #+#    #+#             */
/*   Updated: 2023/10/20 19:57:34 by bmoretti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>     //to remove
#include <strings.h>   //to remove
#define BUFFER_SIZE 30 // to remove

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
	if (++(*i) == lo_limit)
		*i = 0;
	return (b_leftover);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
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

char	*ft_strljoin(char **s1, char *s2, size_t len_s2)
{
	size_t		len;
	char		*joined;
	char		*origin;
	char		*s1_sub;

	if (!s1 || !*s1 || !s2)
		return (NULL);
	s1_sub = *s1;
	len = ft_strlen(s1_sub) + len_s2;
	joined = malloc(len + 1);
	if (joined == NULL)
		return (NULL);
	origin = joined;
	while (*s1_sub)
		*(joined++) = *(s1_sub++);
	while (len_s2--)
		*(joined++) = *(s2++);
	*joined = '\0';
	free (*s1);
	return (origin);
}

char	*get_next_line(int fd)
{
	static char		buffer[BUFFER_SIZE];
	static size_t	i;
	static size_t	n_bytes;
	size_t			final_bytes;
	char			*line;

	line = ft_buffer_leftover(&i, buffer, n_bytes);
	if (i || !line)
		return (line);
	n_bytes = read(fd, buffer, BUFFER_SIZE);
	final_bytes = ft_seek_end_or_backslash_n(buffer, n_bytes);
	while (final_bytes == n_bytes)
	{
		line = ft_strljoin(&line, buffer, n_bytes);
		if (!line)
			return (NULL);
		final_bytes = ft_seek_end_or_backslash_n(buffer, n_bytes);
	}
	line = ft_strljoin(&line, buffer, final_bytes);
	i = final_bytes + 1;
	if (i == BUFFER_SIZE)
		i = 0;
	return (line);
}
