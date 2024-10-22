/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:51:45 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/22 06:09:14 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	set_1(t_list *list)
{
	if (list->content[0] == '|' && list->content[1] == '|' \
			&& list->content[2] == '\0')
		return (list->type = OR, 1);
	else if (list->content[0] == '&' && list->content[1] == '&' \
			&& list->content[2] == '\0')
		return (list->type = AND, 1);
	else if (list->content[0] == '<' && list->content[1] == '<' \
			&& list->content[2] == '\0')
		return (list->type = HEREDOC, 1);
	else if (list->content[0] == '>' && list->content[1] == '>' \
			&& list->content[2] == '\0')
		return (list->type = APPEND, 1);
	else if (list->content[0] == '|' && list->content[1] == '\0')
		return (list->type = PIPE, 1);
	else if (list->content[0] == '>' && list->content[1] == '\0')
		return (list->type = OUTPUT, 1);
	else if (list->content[0] == '<' && list->content[1] == '\0')
		return (list->type = INPUT, 1);
	else if ((list->content[0] == ')' && list->content[1] == '\0') \
			|| (list->content[0] == '(' && list->content[1] == '\0'))
		return (list->type = PARENTHESIS, 1);
	else if (list->back != NULL && list->back->type == HEREDOC)
		return (list->type = DELIMITER, 1);
	return (0);
}

int	set_2(t_list *list)
{
	if (list->back != NULL && (list->back->type == OUTPUT \
				|| list->back->type == APPEND || list->back->type == INPUT))
		return (list->type = PATH, 1);
	else if (list->back != NULL && \
			(list->back->type == COMMAND || list->back->type == OPTIONS \
			|| list->back->type == PATH_COMMAND))
		return (list->type = OPTIONS, 1);
	else if (list->content[0] == '/' || list->content[0] == '~' \
			|| !ft_strncmp(list->content, "./", 2))
	{
		if (list->back != NULL)
		{
			if (list->back->type != COMMAND && list->back->type != OPTIONS)
				return (list->type = PATH_COMMAND, 1);
		}
		else if (list->back == NULL)
			return (list->type = PATH_COMMAND, 1);
		else
			return (list->type = PATH, 1);
	}
	return (0);
}

int	token_type(t_list *list)
{
	if (set_1(list))
		return (0);
	else if (set_2(list))
		return (0);
	else
		list->type = COMMAND;
	return (0);
}
