/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoretti <bmoretti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:24:15 by bmoretti          #+#    #+#             */
/*   Updated: 2023/10/25 21:11:40 by bmoretti         ###   ########.fr       */
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
	int		fds;
	char	*line;
	char	fl_name[] = "one_line_no_nl.txt";
	int		i;

	fds = open(fl_name, O_RDONLY);
	if (fds == -1)
	{
		printf("Error opening file %s\n", fl_name);
		return (1);
	}
	i = 0;
	while (++i <= 3)
	{
		line = get_next_line(fds);
		printf(" %d: %s", i, line);
		free(line);
	}
	return (0);
}
