/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:44:05 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/01 05:52:24 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**get_envp(char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (env[i] == NULL)
		return (NULL);
	return (ft_split(env[i] + 5, ':'));
}

char	*find_in_path(char **dir, t_list *list)
{
	char	*path;
	char	*temp;
	int		i;

	i = 0;
	while (dir[i] != NULL)
	{
		temp = ft_strjoin(dir[i], "/");
		path = ft_strjoin(temp, list->content);
		free(temp);
		if (access(path, F_OK) == 0)
		{
			return (path);
		}
		free(path);
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(t_helper *helper, t_list *list)
{
	char	**dir;
	char	*path;

	dir = get_envp(helper->envp);
	if (dir == NULL)
		return (NULL);
	path = find_in_path(dir, list);
	free_array(dir);
	if (path)
		return (path);
	else
		return (ft_strdup(list->content));
}

char	*get_path_of_cpath(t_helper *helper, t_list *list)
{
	char	**dir;

	dir = get_envp(helper->envp);
	if (access(list->content, F_OK | X_OK) == 0)
	{
		free_array(dir);
		return (ft_strdup(list->content));
	}
	return (ft_strdup(list->content));
}

char	*get_path(t_helper *helper, t_list *list)
{
	char	*path;

	path = NULL;
	if (list->type == COMMAND)
		path = get_cmd_path(helper, list);
	else if (list->type == PATH_COMMAND)
		path = get_path_of_cpath(helper, list);
	return (path);
}
