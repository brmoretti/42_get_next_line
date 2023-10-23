/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_last.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoretti <bmoretti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 21:44:09 by bmoretti          #+#    #+#             */
/*   Updated: 2023/10/23 14:42:21 by bmoretti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>     //to remove
#include <strings.h>   //to remove
#define BUFFER_SIZE 20 // to remove

size_t	ft_strlen(const char *s);

ssize_t	ft_fill_buffer(int fd, char **buffer)
{
	ssize_t	size;

	if (!*buffer)
		*buffer = calloc(BUFFER_SIZE + 1, 1);
	if (!*buffer)
		return (0);
	size = read(fd, *buffer, BUFFER_SIZE);
	if (!size)
		free (*buffer);
	return (size);
}

size_t	ft_strlen_till_bslash_n(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[++i - 1] == '\n')
			break;
	}
	return (i);
}

char	*ft_join_till_bslash_n(char	*dst, char *src)
{
	ssize_t	i;
	ssize_t	j;
	char	*joined;

	joined = malloc(ft_strlen(dst) + ft_strlen_till_bslash_n(src) + 1);
	if (!joined)
		return (NULL);
	i = 0;
	while (dst && dst[i])
		joined[i] = dst[i++];
	j = 0;
	if (dst)
		free (dst);
	while (src && src[j])
	{
		joined[i + j] = src[j];
		if (src[++j - 1] == '\n')
			break;
	}
	joined[i + j] = '\0';
	return (joined);
}

char	*ft_strrchr(const char *s, int c)
{
	char	*occ;

	occ = NULL;
	while (*s)
	{
		if (*s++ == (unsigned char)c)
			occ = (char *)(s - 1);
	}
	if (!(unsigned char)c)
		occ = (char *)(s);
	return (occ);
}

char	*ft_line_recursive(char **line, char **buffer, ssize_t read_size)
{
	char	*slash_n;

	if (!read_size)
		return (NULL);
	*line = ft_join_till_bslash_n(*line, *buffer);
	if (!*line)
		return (NULL);
	slash_n = ft_strrchr(*buffer, '\n');
	if (slash_n)
		*buffer = ft_join_till_bslash_n(*buffer, )
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	ssize_t		read_size;
	char		*line;

	if (!buffer || !*buffer)
		read_size = ft_fill_buffer(fd, &buffer);
	line = NULL;
	line = ft_line_recursive(&line, buffer, read_size);
	return (line);
}
