/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheking_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 13:17:41 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/28 00:19:47 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	get_len_path(char *path)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	if (!path)
		return (0);
	if (path[i] == ':')
		len++;
	while (path[i])
	{
		if (path[i] == ':' && path[i + 1] == ':')
			len += 3;
		else
			len++;
		i++;
	}
	if (path[i - 1] == ':')
		len++;
	return (len);
}

char	*allocate_path(char *path)
{
	char	*new_path;

	if (!path)
		return (NULL);
	new_path = malloc(get_len_path(path) + 1);
	if (!new_path)
		return (NULL);
	return (new_path);
}

void	update_path(char *path, char *new_path)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (path[0] == ':')
		new_path[j++] = '.';
	while (path[i])
	{
		if (path[i] == ':' && path[i + 1] == ':')
		{
			new_path[j++] = ':';
			new_path[j++] = '.';
			new_path[j++] = ':';
			i += 2;
		}
		else
			new_path[j++] = path[i++];
	}
	if (path[i - 1] == ':')
		new_path[j++] = '.';
	new_path[j] = '\0';
}

char	*check_path(char *path)
{
	char	*new_path;

	if((path && path[0] == '\0') || !path)
	{
		new_path = (char *)malloc(sizeof(char) * 2);
		return(ft_memcpy(new_path, ".", 2));
	}
	new_path = allocate_path(path);
	if (!new_path)
		return (NULL);
	update_path(path, new_path);
	free(path);
	return (new_path);
}
