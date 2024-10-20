/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:47:55 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/19 23:47:56 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

double	check_heredoc(t_list *list)
{
	double	i;

	i = 0;
	while (list)
	{
		if (list->type == HEREDOC)
			i++;
		list = list->next;
	}
	return (i);
}

int	clean_heredoc(char **redfile, int hd)
{
	int	i;

	i = -1;
	while (redfile[++i] && hd-- > 0)
	{
		if (unlink(redfile[i]) < 0)
		{
			printf("Error deleting redfile\n");
			return (1);
		}
	}
	return (0);
}

int	check_quotes(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '"' || str[i] == '\'')
			return (1);
	}
	return (0);
}

void	set_expande_line(t_expand_line *xl, int d, char *str)
{
	xl->fstr = NULL;
	xl->sstr = NULL;
	xl->tstr = NULL;
	xl->len = d;
	xl->fstr = ft_substr(str, 0, xl->len);
}
