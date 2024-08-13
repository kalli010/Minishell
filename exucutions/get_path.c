/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:44:05 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/08/13 12:21:24 by ayel-mou         ###   ########.fr       */
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

char	*get_cmd_path(t_helper *helper, t_list *list)
{
	char	*path;
	char	**dir;
	char	*temp;
	int		i;

	i = 0;
	dir = get_envp(helper->envp);
	if (dir == NULL)
		return (NULL);
	while (dir[i] != NULL)
	{
		temp = ft_strjoin(dir[i], "/");
		path = ft_strjoin(temp, list->content);
		free(temp);
		if (access(path, F_OK) == 0)
		{
			free_array(dir);
			return (path);
		}
		free(path);
		i++;
	}
	return (NULL);
}

char	*get_path_of_cpath(t_helper *helper, t_list *list)
{
	char	**dir;

	dir = get_envp(helper->envp);
	if (access(list->content, F_OK) == 0)
	{
		free_array(dir);
		return (ft_strdup(list->content));
	}
	return (NULL);
}

char	*get_path(t_helper *helper, t_list *list)
{
	char	*path;

	if (list->type == COMMAND)
		path = get_cmd_path(helper, list);
	if (list->type == PATH_COMMAND)
		path = get_path_of_cpath(helper, list);
	return (path);
}

char	**get_options(t_helper *helper, t_list *list)
{
	int		i;
	int		count;
	char	**op;

	count = count_arg(list);
	if (get_path(helper, list) == NULL)
	{
		printf("%s: command not found \n", list->content);
		return (NULL);
	}
	op = (char **)malloc((count + 2) * sizeof(char *));
	if (!op)
		return (NULL);
	op[0] = get_path(helper, list);
	if (!op[0])
		return (free(op), (NULL));
	list = list->next;
	i = 1;
	while (list && list->type == OPTIONS)
	{
		op[i++] = ft_strdup(list->content);
		list = list->next;
	}
	op[i] = NULL;
	return (op);
}
