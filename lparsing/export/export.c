/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:50:43 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/28 01:18:49 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	set_var(t_list *list, char ***env, char ***xenv)
{
	char		*var;
	char		*value;
	int			len;
	int			s;
	t_set_var	sv;

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
	init_sv(&sv, var, value);
	s = check_and_update_env(env, xenv, &sv, list);
	if (s == -1)
		return (1);
	else if (s == -2)
		return (0);
	if (add_new_var_to_env(env, xenv, &sv, s))
		return (1);
	return (free(var), free(value), 0);
}

int	check_cmd_export(t_list *list)
{
	while (list)
	{
		if (list->type != OPTIONS)
		{
			if (list && (list->type == AND || list->type == OR))
				return (0);
			return (1);
		}
		list = list->next;
	}
	return (0);
}

int	check_cmd_export_2(t_list *list)
{
	if (list->back != NULL && (list->back->type == OR
			|| list->back->type == AND))
	{
		list->e = 1;
		return (1);
	}
	return (0);
}

int	check_var(t_list *list, char ***env, char ***xenv)
{
	if (list == NULL || ft_strncmp("export", list->content, sizeof("export"))
		|| ((list->back == NULL || list->e == 1)
			&& check_cmd_export(list->next)))
		return (0);
	list = list->next;
	while (list)
	{
		if (list->type == OR || list->type == AND)
			break ;
		if (set_var(list, env, xenv))
		{
			printf("not a valid identifier\n");
			g_helper.exit_status = 1;
		}
		list = list->next;
	}
	return (0);
}
