/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoretti <bmoretti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 23:25:38 by bmoretti          #+#    #+#             */
/*   Updated: 2023/10/20 00:07:24 by bmoretti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> //to remove
#include <strings.h> //to remove
#define BUFFER_SIZE 30 //to remove

char	*ft_buffer_leftover(size_t *i, char *buffer, size_t lo_limit)
{
	size_t	j;
	char	*b_leftover;
	char	*ptr;

	j = *i;
	while (*i && *i < lo_limit && buffer[*i] != '\n')
		(*i)++;
	b_leftover = malloc((*i - j) + 1);
	if (!b_leftover)
		return (NULL);
	ptr = b_leftover;
	while (j < *i)
		*(ptr++) = buffer[j++];
	*ptr = '\0';
	if (++(*i) == BUFFER_SIZE)
		*i = 0;
	printf("b_leftover: %s\n", b_leftover);
	return(b_leftover);
}

char	*get_next_line(int fd)
{
	static char		buffer[BUFFER_SIZE];
	static size_t	i;
	static ssize_t	n_bytes;
	char			*line;

	line = ft_buffer_leftover(&i, buffer, n_bytes);
	if (i || !line)
		return (line);
	n_bytes = read(fd, buffer, BUFFER_SIZE);
	if (n_bytes < BUFFER_SIZE)
		bzero(&buffer[n_bytes], BUFFER_SIZE - n_bytes - 1);
	printf("fd: %p\n", &fd);
	printf("n_bytes: %zu ", n_bytes);
	printf("%s\n", buffer);
	return (buffer);
}
