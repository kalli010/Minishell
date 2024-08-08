/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 06:50:58 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/08/08 08:42:33 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_if_uppercase(char *line)
{
	int i;

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

char	*check_if_env(char *line)
{
	char	*path_env;

	if (check_if_uppercase(line))
	{
		path_env = getenv(line + 1);
		if (path_env != NULL)
			return (path_env);
	}
	return (NULL);
}

int	here_doc(t_list *list,t_helper *helper)
{
	t_here_doc	*here;
	int			fd;
	int 		pipe_fd[2];
	char		*line;
	here = (t_here_doc *)malloc(sizeof(t_here_doc));
	here->del = ft_strdup(list->next->content);
	
	line = readline("> ");
	while (line)
	{
		line = readline("> ");
		if (ft_strncmp(line,here->del,ft_strlen(line)) == 0)
			break;

	}
	free(line);
	free(here->del);
	free(here);
}
