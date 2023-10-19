/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoretti <bmoretti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 23:25:38 by bmoretti          #+#    #+#             */
/*   Updated: 2023/10/19 14:09:00 by bmoretti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> //to remove
#include <strings.h> //to remove
#define BUFFER_SIZE 500 //to remove

void	ft_position(size_t *pos)
{
	static size_t	bytes_read;


}

char	*get_next_line(int fd)
{
	static char		buffer[BUFFER_SIZE];
	ssize_t			bytes_read;
	static ssize_t	total_bytes;

	bzero(buffer, BUFFER_SIZE);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	total_bytes += bytes_read;
	printf("bytes_read: %zu\n", bytes_read);
	printf("total_bytes: %zu\n", total_bytes);
	printf("buffer: %s\n", buffer);
	return (buffer);
}
