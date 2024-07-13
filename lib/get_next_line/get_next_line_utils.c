/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 23:56:52 by zelkalai          #+#    #+#             */
/*   Updated: 2024/07/04 23:56:53 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s)
{
	char	*str;
	int		count;

	count = 0;
	while (s[count])
		count++;
	str = malloc((count + 1) * sizeof(char));
	if (!str)
		return (NULL);
	count = 0;
	while (s[count])
	{
		str[count] = s[count];
		count++;
	}
	str[count] = '\0';
	return (str);
}

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (s[count])
		count++;
	return (count);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == 0)
		return ((char *)s);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	y;
	size_t	x;

	if (!s1 && !s2)
		return (NULL);
	if (!s1 && s2)
		return (ft_strdup(s2));
	if (s1 && !s2)
		return (ft_strdup(s1));
	else
		ptr = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	x = 0;
	y = 0;
	while (s1 && s1[x])
		ptr[y++] = s1[x++];
	x = 0;
	while (s2 && s2[x])
		ptr[y++] = s2[x++];
	ptr[y] = '\0';
	return (ptr);
}
