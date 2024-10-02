/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 21:35:52 by zelkalai          #+#    #+#             */
/*   Updated: 2024/08/26 23:30:43 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	little_len;

	if (*little == '\0')
		return (0);
	if (!big && !len)
		return (0);
	little_len = ft_strlen(little);
	i = 0;
	while (big && (big[i] != '\0' && little_len <= len - i))
	{
		j = 0;
		while (big[i + j] == little[j] && little[j] != '\0')
			j++;
		if (little_len == j)
			return (i + j);
		i++;
	}
	return (0);
}
