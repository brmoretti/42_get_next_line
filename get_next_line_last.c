/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_last.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoretti <bmoretti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 21:44:09 by bmoretti          #+#    #+#             */
/*   Updated: 2023/10/23 19:44:05 by bmoretti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>     //to remove
#include <strings.h>   //to remove
#define BUFFER_SIZE 20 // to remove

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

size_t	ft_strlen_till_bslash_n(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[++i - 1] == '\n')
			break ;
	}
	return (i);
}

char	*ft_join_till_bslash_n(char *dst, char *src)
{
	ssize_t	i;
	ssize_t	j;
	char	*joined;

	joined = malloc(ft_strlen(dst) + ft_strlen_till_bslash_n(src) + 1);
	if (!joined)
		return (NULL);
	i = 0;
	while (dst && dst[i])
	{
		joined[i] = dst[i];
		i++;
	}
	if (dst)
		free(dst);
	j = 0;
	while (src && src[j])
	{
		joined[i + j] = src[j];
		if (src[++j - 1] == '\n')
			break ;
	}
	joined[i + j] = '\0';
	return (joined);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
		if (*s++ == (unsigned char)c)
			return ((char *)--s);
	if ((unsigned char)c == '\0')
		return ((char *)s);
	return (NULL);
}
void	ft_move_to_begin(char *to, char *from)
{
	while (*from)
		*(to++) = *(from++);
	while (*to)
		(*to++) = '\0';
}

char	*ft_line_recursive(int fd, char **line, char *buffer, ssize_t read_size)
{
	char	*slash_n;

	*line = ft_join_till_bslash_n(*line, buffer);
	if (!*line)
		return (NULL);
	slash_n = ft_strchr(buffer, '\n');
	if (slash_n)
	{
		ft_move_to_begin(buffer, slash_n + 1);
		return (*line);
	}
	bzero(buffer, BUFFER_SIZE + 1);
	read_size = read(fd, buffer, BUFFER_SIZE);
	if (read_size)
		*line = ft_line_recursive(fd, line, buffer, read_size);
	return (*line);
}

char	*ft_line_iterative(int fd, char **line, char *buffer, ssize_t read_size)
{
	char	*slash_n;

	while (1)
	{
		*line = ft_join_till_bslash_n(*line, buffer);
		if (!*line)
			return (NULL);
		slash_n = ft_strchr(buffer, '\n');
		if (slash_n)
		{
			ft_move_to_begin(buffer, slash_n + 1);
			return (*line);
		}
		bzero(buffer, BUFFER_SIZE + 1);
		read_size = read(fd, buffer, BUFFER_SIZE);
		if (read_size)
			*line = ft_line_recursive(fd, line, buffer, read_size);
	}
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	ssize_t		read_size;
	char		*line;

	if (!*buffer)
		read_size = read(fd, buffer, BUFFER_SIZE);
	if (!read_size)
		return (NULL);
	line = NULL;
	line = ft_line_iterative(fd, &line, buffer, read_size);
	return (line);
}
