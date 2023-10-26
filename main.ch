/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoretti <bmoretti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:24:15 by bmoretti          #+#    #+#             */
/*   Updated: 2023/10/25 19:05:55 by bmoretti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*get_next_line(int fd);

int	main(void)
{
//to not forget to remove the main
	int		*fds;
	int		n_files;
	char	*line;
	int		i;
	int		j;
	char	fl_name[] = "text0.txt";

	n_files = 4;
	fds = malloc(sizeof(int) * n_files);
	i = -1;
	while (++i < n_files)
	{
		fl_name[4] = i + '0';
		fds[i] = open(fl_name, O_RDONLY);
		if (fds[i] == -1)
		{
			printf("Error opening file %s\n", fl_name);
			return (1);
		}
		//printf("File %s opened with fd %d\n", fl_name, fds[i]);
	}
	i = -1;
	while (i++ < 15)
	{
		j = 0;
		while (j < n_files)
		{
			line = get_next_line(fds[j++]);
			printf("%d: %s", i, line);
			free(line);
		}
	}
	free(fds);
	return (0);
}
