/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:51:18 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/19 20:51:21 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_e(int *e, char c)
{
	if (*e == 1)
		*e = 0;
	else
	{
		printf("Error, check %c.\n", c);
		return (1);
	}
	return (0);
}

int	quotes_check(char *str)
{
	int		i;
	char	c;
	int		e;

	e = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			c = str[i];
			while (str[++i])
			{
				if (str[i] == c)
				{
					e++;
					break ;
				}
			}
			if (check_e(&e, c))
				return (1);
		}
	}
	return (0);
}
