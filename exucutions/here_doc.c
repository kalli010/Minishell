/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 06:50:58 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/08/09 02:57:22 by ayel-mou         ###   ########.fr       */
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
	char		*env_path;
	int 		pipe_fd[2];
	char		*line;
	(void)helper;
	here = (t_here_doc *)malloc(sizeof(t_here_doc));
	here->del = ft_strdup(list->next->content);
	if (!here->del)
	{
		free(here);
		return (0);
	}
	if (pipe(pipe_fd) == -1)
	{
		free(here);
		free(here->del);
	}
	while (1)
	{
		line = readline("> ");
		if (ft_strncmp(line,here->del,ft_strlen(line)) == 0 || ft_strlen(line) == 0) 
			break;
		env_path =  check_if_env(line);
		if (env_path != NULL)
			write(pipe_fd[1],env_path,ft_strlen(env_path));
		else
			write(pipe_fd[1],line,ft_strlen(line));
		write(pipe_fd[1],"\n",1);
		free(line);
	}
	close(pipe_fd[1]);
	free(line);
	free(here->del);
	free(here);
	return (pipe_fd[0]);
}
