/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement_wildcards.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 00:38:43 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/27 23:26:15 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	find_first_non_star(char *wc)
{
	int	i;

	i = 0;
	while (wc[i] == '*')
	{
		if (wc[i] == '\0')
			return (-1);
		i++;
	}
	return (i);
}

void	check_flag(int *len, int *flag, char *wc)
{
	if (*len == 0 && *flag == -1)
		*flag = 0;
	else if (wc[*len] == '\0')
		*flag = 2;
	else
		*flag = 1;
}

int	process_substring(char *wc, const char *filename, int *i, int *len)
{
	int		s;
	char	*str;
	int		flag;

	flag = -1;
	s = *len;
	check_flag(len, &flag, wc);
	while (wc[*len] != '*' && wc[*len] != '\0')
		(*len)++;
	str = ft_substr(wc, s, *len - s);
	if (str != NULL)
	{
		*i += ft_find(&filename[*i], str, flag);
		if (*i == -1)
		{
			free(str);
			return (1);
		}
	}
	free(str);
	return (0);
}

void	skip_stars(char *wc, int *len)
{
	while (wc[*len] == '*')
		(*len)++;
}

int	implementing_wildcards(char *wc, const char *filename)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (filename != NULL && filename[0] == '.')
		return (1);
	i = find_first_non_star(wc);
	if (i == -1)
		return (0);
	i = 0;
	while (wc[len])
	{
		if (process_substring(wc, filename, &i, &len))
			return (1);
		skip_stars(wc, &len);
	}
	return (0);
}
