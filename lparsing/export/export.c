/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:50:43 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/19 21:38:22 by zelkalai         ###   ########.fr       */
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
  if(list->content[start - 1] == '=')
    len++;
	value = ft_substr(list->content, start, len - start);
	remove_quotes_string(value);
	return (value);
}

int	check_and_update_env(char ***env, char ***xenv, char *var, char *value,
		t_list *list)
{
	int	s;

	s = 0;
	while (*env != NULL && (*env)[s] != NULL)
	{
		if (!ft_strncmp((*env)[s], var, ft_strlen(var)) &&
			((*env)[s][ft_strlen(var)] == '='
					|| (*env)[s][ft_strlen(var)] == '\0'))
		{
			if (list->content[ft_strlen(var)] == '\0')
			{
				free(var);
				free(value);
				return (-2);
			}
			if (add_var(*env, var, value, s))
			{
				free(var);
				free(value);
				return (-1);
			}
			if (add_var(*xenv, var, value, s))
			{
				free(var);
				free(value);
				return (-1);
			}
			free(var);
			free(value);
			return (-2);
		}
		s++;
	}
	return (s);
}

int	add_new_var_to_env(char ***env, char ***xenv, char *var, char *value, int s)
{
	*env = add_new_env(*env, s, var, value, 0);
	*xenv = add_new_env(*xenv, s, var, value, 1);
	if (*env == NULL || *xenv == NULL)
	{
		free(var);
		free(value);
		return (1);
	}
	return (0);
}

int	set_var(t_list *list, char ***env, char ***xenv)
{
	char	*var;
	char	*value;
	int		len;
	int		s;

	len = extract_var_name(list, &var);
	if (len == 0 || validate_var_name(var))
		return (1);
	if (list->content[len] != '\0')
	{
		if (list->content[len - 1] == ' ')
			return (1);
		len++;
	}
	value = extract_value(list, len);
	s = check_and_update_env(env, xenv, var, value, list);
	if (s == -1)
		return (1);
	else if (s == -2)
		return (0);
	if (add_new_var_to_env(env, xenv, var, value, s))
		return (1);
	free(var);
	free(value);
	return (0);
}

int	check_cmd_export(t_list *list)
{
	while (list)
	{
		if (list->type != OPTIONS)
			return (1);
		list = list->next;
	}
	return (0);
}

int	check_var(t_list *list, char ***env, char ***xenv)
{
	g_helper.exit_status = 0;
	if (list->back && (list->back->back != NULL || check_cmd_export(list)))
		return (g_helper.exit_status);
	while (list)
	{
		if (set_var(list, env, xenv))
		{
			printf("not a valid identifier\n");
			g_helper.exit_status = 1;
		}
		list = list->next;
	}
	return (g_helper.exit_status);
}
