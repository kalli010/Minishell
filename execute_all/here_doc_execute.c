/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_execute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 03:40:13 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/08/28 09:08:23 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	count_here_doc(t_list *list)
{
	t_list	*temp_list;
	int		count;

	count = 0;
	temp_list = list;
	while (temp_list && temp_list->type == HEREDOC)
	{
		count++;
		temp_list = temp_list->next;
	}
	return (count);
}

int	check_if_uppercase(char *line)
{
	int	i;

	if (line[0] == '$' && line[1] != '\0')
	{
		i = 1;
		while (line[i])
		{
			if (!check_upper(line[i]))
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

char	*check_if_env(char **env, char *line)
{
	char	*path_env;

	if (check_if_uppercase(line))
	{
		path_env = ft_getenv(env, line + 1);
		if (path_env != NULL)
			return (path_env);
	}
	return (NULL);
}
