/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoretti <bmoretti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 21:44:09 by bmoretti          #+#    #+#             */
/*   Updated: 2023/10/25 20:38:07 by bmoretti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

void	ft_move_to_begin(char *to, char *from)
{
	while (*from)
		*(to++) = *(from++);
	while (*to)
		(*to++) = '\0';
}

char	*ft_line_iterative(int fd, char *buffer, ssize_t *read_size)
{
	char	*slash_n;
	char	*line;

	line = NULL;
	while (1)
	{
		if (!*buffer)
			*read_size = read(fd, buffer, BUFFER_SIZE);
		if ((!*read_size && !*buffer) || *read_size == -1)
			return (line);
		line = ft_join_till_bslash_n(line, buffer);
		if (!line)
			return (NULL);
		slash_n = ft_strchr(buffer, '\n');
		if (slash_n)
			break ;
		ft_bzero(buffer, BUFFER_SIZE + 1);
	}
	ft_move_to_begin(buffer, slash_n + 1);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;
	ssize_t		read_size;

	read_size = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1023)
		return (NULL);
	if (!buffer[fd])
		buffer[fd] = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!buffer[fd])
		return (NULL);
	line = ft_line_iterative(fd, buffer[fd], &read_size);
	if (read_size == -1 || (buffer[fd] && !*buffer[fd]))
	{
		free (buffer[fd]);
		buffer[fd] = NULL;
	}
	if (line && (read_size == -1 || !*line))
	{
		free (line);
		return (NULL);
	}
	return (line);
}
