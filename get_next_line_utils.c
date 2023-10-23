/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoretti <bmoretti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 23:25:51 by bmoretti          #+#    #+#             */
/*   Updated: 2023/10/21 13:19:10 by bmoretti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*ft_strljoin(char **s1, char *s2, size_t len_s2)
{
	size_t		len;
	char		*joined;
	char		*origin;
	char		*s1_sub;

	if (!s1 || !*s1 || !s2)
		return (NULL);
	s1_sub = *s1;
	len = ft_strlen(s1_sub) + len_s2;
	joined = malloc(len + 1);
	if (joined == NULL)
		return (NULL);
	origin = joined;
	while (*s1_sub)
		*(joined++) = *(s1_sub++);
	while (len_s2--)
		*(joined++) = *(s2++);
	*joined = '\0';
	free (*s1);
	return (origin);
}
