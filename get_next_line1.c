/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoretti <bmoretti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:58:28 by bmoretti          #+#    #+#             */
/*   Updated: 2023/10/22 08:27:52 by bmoretti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>     //to remove
#include <strings.h>   //to remove
#define BUFFER_SIZE 30 // to remove

ssize_t	ft_read_safe(int fd, char *buffer, char **pos)
{
	unsigned int	i;

	if (fd <= 0)
		return (0);
	i = 0;
	while (i < BUFFER_SIZE)
		buffer[i++] = '\0';
	*pos = buffer;
	return (read(fd, buffer, BUFFER_SIZE));
}

size_t	ft_seek_end_or_backslash_n(char *str, int *bslash)
{
	char	*mover;

	mover = str;
	while (*mover && *mover != '\n')
		mover++;
	if (*mover == '\n')
		*bslash = 1;
	else
		*bslash = 0;
	return ((size_t)(mover - str));
}

char	*ft_text_till_bslash_n_or_end(char **pos, int *bslash)
{
	char	*text;
	char	*mover;
	char	*mover2;

	mover2 = *pos;
	text = malloc(ft_seek_end_or_backslash_n(*pos, bslash) + 1);
	if (!text)
		return (NULL);
	mover = text;
	while (*mover2 && *mover2 != '\n')
		*(mover++) = *(mover2++);
	*mover = '\0';
	*pos = mover2 + 1;
	return (text);
}

int	ft_join(char **s1, char **s2, char *dest)
{
	char	*origin;
	char	*s1_mover;
	char	*s2_mover;

	s1_mover = *s1;
	s2_mover = *s2;
	if (dest)
	{
		origin = dest;
		while (*s1_mover)
			*(dest++) = *(s1_mover++);
		while (*s2_mover)
			*(dest++) = *(s2_mover++);
		*dest = '\0';
	}
	free (*s1);
	free (*s2);
	if (!dest)
		return (0);
	*s1 = origin;
	return (1);
}

int	ft_strjoin_finish(char **s1, char **pos)
{
	int		bslash;
	char	*s2;
	char	*text;

	s2 = ft_text_till_bslash_n_or_end(pos, &bslash);
	if (!s2)
		return (-1);
	else if (!*s1)
		*s1 = s2;
	else
	{
		text = malloc((ft_strlen(*s1) + ft_strlen(s2) + 1)); //entrar na ft_join
		if(!ft_join(s1, &s2, text))
			return (-1);
	}
	if (bslash)
		return (1);
	return (0);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	static char	*pos;
	ssize_t		n_bytes;
	char		*line;

	line = NULL;
	n_bytes = 0;
	if (!pos || !(buffer < pos && pos < &buffer[BUFFER_SIZE]))
		n_bytes = ft_read_safe(fd, buffer, &pos);
	if (!n_bytes)
		return (NULL);
	while (n_bytes || (buffer < pos && pos < &buffer[BUFFER_SIZE]))
	{
		if (ft_strjoin_finish(&line, &pos))
			return (line);
		n_bytes = ft_read_safe(fd, buffer, &pos);
	}
	return (line);
}
