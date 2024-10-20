/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:52:08 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/19 20:52:09 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_unset(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
			return (1);
	}
	return (0);
}

void	remove_env_var(char ***env, char *content)
{
	int	s;
	int	i;

	s = 0;
	i = 0;
	while ((*env)[s] != NULL)
	{
		if (!ft_strncmp((*env)[s], content, ft_strlen(content))
			&& ((*env)[s][ft_strlen(content)] == '='
				|| (*env)[s][ft_strlen(content)] == '\0'))
		{
			free((*env)[s]);
			i = s;
			while ((*env)[++s])
				;
			(*env)[i] = (*env)[s - 1];
			(*env)[s - 1] = NULL;
			break ;
		}
		s++;
	}
}

int	unset(char ***env, t_list *list)
{
	while (list && list->type == OPTIONS)
	{
		if (!check_unset(list->content))
			remove_env_var(env, list->content);
		list = list->next;
	}
	return (0);
}
