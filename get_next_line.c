/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoretti <bmoretti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 21:44:09 by bmoretti          #+#    #+#             */
/*   Updated: 2023/11/14 15:20:09 by bmoretti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief Calculates the length of a string until the first newline character.
 *
 * @param s The input string.
 * @return The length of the string until the first newline character.
 */
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

/**
 * @brief Joins two strings until the first newline character is encountered
 *        in the second string or until the end if not encountered.
 *
 * @param dst The destination string.
 * @param src The source string.
 * @return The joined string.
 */
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

/**
 * @brief Cut and paste the content of one string to the beginning of another.
 *
 * @param to The destination string.
 * @param from The source string.
 */
void	ft_move_to_begin(char *to, char *from)
{
	while (*from)
		*(to++) = *(from++);
	while (*to)
		(*to++) = '\0';
}

/**
 * @brief Reads lines iteratively from a file descriptor until a newline
 *        character is encountered, the file ends or an read error occur.
 *
 * @param fd The file descriptor.
 * @param buffer The buffer for reading from the file.
 * @param read_size A pointer to the variable storing the read size.
 * @return The next line read from the file.
 */
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

/**
 * @brief Reads the next line from a file descriptor.
 *
 * @param fd The file descriptor.
 * @return The next line read from the file.
 */
char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	ssize_t		read_size;

	read_size = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_line_iterative(fd, buffer, &read_size);
	if (line && (read_size == -1 || !*line))
	{
		free (line);
		return (NULL);
	}
	return (line);
}
