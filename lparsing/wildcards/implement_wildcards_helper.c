/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement_wildcards.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:49:11 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/19 23:49:11 by zelkalai         ###   ########.fr       */
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
	if (*len != 0 && *flag == -1)
		*flag = 0;
	else if (wc[*len] == '\0')
		*flag = 2;
	else
		*flag = 1;
}

int	process_substring(char *wc, const char *filename, int *flag, int *len)
{
	int		s;
	char	*str;
	int		i;

	i = 0;
	s = *len;
	while (wc[*len] != '*' && wc[*len] != '\0')
		(*len)++;
	check_flag(len, flag, wc);
	str = ft_substr(wc, s, *len - s);
	if (str != NULL)
	{
		i += ft_find(&filename[i], str, *flag);
		if (i == -1)
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

t_list	*ft_lstnew_2(char *content)
{
	t_list	*a;

	a = malloc(sizeof(t_list));
	if (!a)
		return (NULL);
	a->content = ft_substr(content, 0, ft_strlen(content));
	a->next = NULL;
	a->back = NULL;
	a->i = 0;
	a->in = 0;
	return (a);
}
