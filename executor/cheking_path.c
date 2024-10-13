/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheking_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 13:17:41 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/13 16:26:31 by ayel-mou         ###   ########.fr       */
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

char	*check_path(char *path)
{
	char	*new_path;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!path)
		return (NULL);
    
	new_path = malloc(get_len_path(path) + 1);
	if (!new_path)
		return (NULL);
    
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
	
	free(path);
	new_path[j] = '\0';
	return (new_path);
}
