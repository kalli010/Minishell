/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:38:39 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/25 12:38:40 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	extract_var_name(t_list *list, char **var)
{
	int	len;

	len = 0;
	while (list->content[len] && list->content[len] != '=')
		len++;
	*var = ft_substr(list->content, 0, len);
	if (*var == NULL)
		return (1);
	remove_quotes_string(*var);
	return (len);
}

int	validate_var_name(char *var)
{
	if ((!ft_isalpha(var[0]) && var[0] != '_') || check_content(var))
	{
		free(var);
		return (1);
	}
	return (0);
}

char	*extract_value(t_list *list, int start)
{
	int		len;
	char	*value;

	len = start;
	while (list->content[len])
		len++;
	if (list->content[start - 1] == '=')
		len++;
	value = ft_substr(list->content, start, len - start);
	remove_quotes_string(value);
	return (value);
}

int	check_and_update_env(char ***env, char ***xenv, t_set_var *sv, t_list *list)
{
	int	s;

	s = 0;
	while (*env != NULL && (*env)[s] != NULL)
	{
		if (!ft_strncmp((*env)[s], sv->var, ft_strlen(sv->var)) &&
			((*env)[s][ft_strlen(sv->var)] == '='
					|| (*env)[s][ft_strlen(sv->var)] == '\0'))
		{
			if (list->content[ft_strlen(sv->var)] == '\0')
				return (free(sv->var), free(sv->value), -2);
			if (add_var(*env, sv->var, sv->value, s))
				return (free(sv->var), free(sv->value), -1);
			if (add_var(*xenv, sv->var, sv->value, s))
				return (free(sv->var), free(sv->value), -1);
			return (free(sv->var), free(sv->value), -2);
		}
		s++;
	}
	return (s);
}
