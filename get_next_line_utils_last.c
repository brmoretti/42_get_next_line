/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_last.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoretti <bmoretti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 22:10:41 by bmoretti          #+#    #+#             */
/*   Updated: 2023/10/22 22:53:02 by bmoretti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ptr;
	size_t			i;
	unsigned int	len_s;

	if (!s)
		return (NULL);
	len_s = (unsigned int)ft_strlen(s);
	if (start >= len_s)
		len = 0;
	else if ((size_t)start + len > (size_t)len_s)
		len = (size_t)len_s - (size_t)start;
	ptr = malloc(len + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (start <= len_s && i < len)
		ptr[i++] = s[start++];
	ptr[i] = '\0';
	return (ptr);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*from;
	unsigned char	*to;

	from = (unsigned char *)src;
	to = (unsigned char *)dest;
	if (to < from)
	{
		while (n-- > 0)
			*to++ = *from++;
	}
	else if (to > from)
	{
		while (n-- > 0)
			to[n] = from[n];
	}
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*joined;
	char	*origin;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	joined = malloc(len + 1);
	if (joined == NULL)
		return (NULL);
	origin = joined;
	while (*s1)
		*(joined++) = *(s1++);
	while (*s2)
		*(joined++) = *(s2++);
	*joined = '\0';
	return (origin);
}

char	*ft_strncpy_new_dest(const char *src, size_t size)
{
	size_t	src_len;
	char	*dst;

	dst = malloc(size);
	if (!dst)
		return (NULL);
	if (size > 0)
	{
		while (size-- > 1)
			*(dst++) = *(src++);
		*dst = '\0';
	}
	return (dst);
}
