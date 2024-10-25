/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 06:06:59 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/25 10:51:37 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_list(t_list *list)
{
	return (list->type != WORD && list->type != COMMAND && list->type != OPTIONS
		&& list->type != PATH && list->type != PATH_COMMAND
		&& list->type != DELIMITER && list->type != PARENTHESIS);
}

int	check_1(t_list *list)
{
	if (list->type == PIPE && check_list(list->back))
	{
		printf("syntax error\n");
		return (1);
	}
	else if (list->type == PIPE && (list->next->type == AND \
				|| list->next->type == OR))
	{
		printf("syntax error\n");
		return (1);
	}
	else if (list->back != NULL && (list->type == list->back->type) && \
			(list->type != WORD && list->type != OPTIONS \
			&& list->type != PARENTHESIS))
	{
		printf("syntax error\n");
		return (1);
	}
	else if (list->content[0] == '&' && list->content[1] == '\0')
	{
		printf("syntax error\n");
		return (1);
	}
	return (0);
}

int	check_2(t_list *list)
{
	if (list->back != NULL && (list->content[0] == '<' \
				&& list->back->content[0] == '>') && \
			(list->type == INPUT || list->type == HEREDOC) && \
			(list->back->type == OUTPUT || list->back->type == APPEND))
	{
		printf("syntax error\n");
		return (1);
	}
	else if ((list->content[0] == '>' && list->back->content[0] == '<') && \
			(list->type == OUTPUT || list->type == APPEND) && \
			(list->back->type == INPUT || list->back->type == HEREDOC))
	{
		printf("syntax error\n");
		return (1);
	}
	return (0);
}

int	check_3(t_list *list)
{
	if (list->content[0] == '|' && list->back->content[0] == '|' && \
			(list->type == OR || list->type == PIPE) && \
			(list->back->type == OR || list->back->type == PIPE))
	{
		printf("syntax error\n");
		return (1);
	}
	else if (list->back != NULL && list->content[0] == '<' \
			&& list->back->content[0] == '<' && (list->type == INPUT \
				|| list->type == HEREDOC) && (list->back->type == INPUT \
					|| list->back->type == HEREDOC))
	{
		printf("syntax error\n");
		return (1);
	}
	return (0);
}

int	check_4(t_list *list)
{
	if (list->content[0] == '>' && list->back->content[0] == '>' && \
			(list->type == OUTPUT || list->type == APPEND) && \
			(list->back->type == OUTPUT || list->back->type == APPEND))
	{
		printf("syntax error\n");
		return (1);
	}
	else if (list->type == HEREDOC && list->back->type == PIPE)
	{
		printf("syntax error\n");
		return (1);
	}
	return (0);
}
