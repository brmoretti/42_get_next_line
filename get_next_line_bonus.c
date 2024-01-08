/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmoretti <brmoretti@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 19:16:35 by brmoretti         #+#    #+#             */
/*   Updated: 2024/01/08 13:32:54 by brmoretti        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * Merges the right string with the left string, up to a specified number of
 * characters from the right string.
 * 
 * @param left The left string to merge.
 * @param right The right string to merge.
 * @param n_right The number of characters from the right string to merge.
 * @return The merged string, or NULL if memory allocation fails.
 */
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
	free(left);
	return (merged);
}

/**
 * Merges the characters from the buffer with the existing line until a newline
 * character is encountered. If no newline character is encountered, the
 * function merges all the characters from the buffer with the existing line.
 * 
 * @param line The existing line to merge with.
 * @param buf The buffer containing the characters to merge.
 * @return The merged line.
 */
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

/**
 * @brief Reads from a file descriptor and constructs a line by merging the
 * read data until a newline character is encountered.
 * 
 * This function iteratively reads from the file descriptor `fd` and merges the
 * read data with the existing `line` until a newline character is encountered.
 * It uses a type buffer `buf` to store the read data and keep track of the
 * current position in the buffer as well as whether a newline character has
 * been encountered.
 * 
 * @param buf The buffer used to store the read data and track the current
 * position.
 * @param fd The file descriptor to read from.
 * @param line The current line being constructed.
 * @return A pointer to the constructed line, or NULL if an error occurs or the
 * end of file is reached.
 */
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

/**
 * @brief Reads the next line from a file descriptor.
 * 
 * This function reads the next line from the file descriptor specified by
 * `fd`.
 * It uses a static array of buffers to store the data read from the file.
 * The function returns a pointer to the line read, or NULL if an error occurs
 * or if the end of the file has been reached.
 * 
 * @param fd The file descriptor to read from.
 * @return A pointer to the line read, or NULL if an error occurs or if the end
 * of the file has been reached.
 */
char	*get_next_line(int fd)
{
	static t_buffer	*arr[1024];
	char			*line;

	if (fd < 0 || BUFFER_SIZE < 1 || fd >= 1024)
		return (NULL);
	if (!arr[fd])
		arr[fd] = ft_calloc(1, sizeof(t_buffer));
	if (!arr[fd])
		return (NULL);
	arr[fd]->bslash = 0;
	line = ft_calloc(1, sizeof(char));
	if (line)
		line = line_iterative(arr[fd], fd, line);
	if (!line)
	{
		free (arr[fd]);
		arr[fd] = NULL;
	}
	return (line);
}
