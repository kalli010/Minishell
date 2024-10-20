/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement_wildcardsi.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 00:38:43 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/20 00:38:46 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	implementing_wildcards(char *wc, const char *filename)
{
	int	i;
	int	len;
	int	flag;

	i = 0;
	len = 0;
	flag = -1;
	if (filename != NULL && filename[0] == '.')
		return (1);
	i = find_first_non_star(wc);
	if (i == -1)
		return (0);
	while (wc[len])
	{
		if (process_substring(wc, filename, &flag, &len) == 1)
			return (1);
		skip_stars(wc, &len);
	}
	return (0);
}
