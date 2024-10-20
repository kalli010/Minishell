/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:51:37 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/20 09:47:22 by zelkalai         ###   ########.fr       */
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
		printf("9\n");
		printf("syntax error\n");
		return (1);
	}
	else if (list->type == PIPE && (list->next->type == AND \
				|| list->next->type == OR))
	{
		printf("11\n");
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
	return (0);
}

int	check_2(t_list *list)
{
	if (list->back != NULL && (list->content[0] == '<' \
				&& list->back->content[0] == '>') && \
			(list->type == INPUT || list->type == HEREDOC) && \
			(list->back->type == OUTPUT || list->back->type == APPEND))
	{
		printf("7\n");
		printf("syntax error\n");
		return (1);
	}
	else if ((list->content[0] == '>' && list->back->content[0] == '<') && \
			(list->type == OUTPUT || list->type == APPEND) && \
			(list->back->type == INPUT || list->back->type == HEREDOC))
	{
		printf("6\n");
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
		printf("5\n");
		printf("syntax error\n");
		return (1);
	}
	else if (list->back != NULL && list->content[0] == '<' \
			&& list->back->content[0] == '<' && (list->type == INPUT \
				|| list->type == HEREDOC) && (list->back->type == INPUT \
					|| list->back->type == HEREDOC))
	{
		printf("4\n");
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
		printf("3\n");
		printf("syntax error\n");
		return (1);
	}
	else if (list->type == HEREDOC && list->back->type == PIPE)
	{
		printf("2\n");
		printf("syntax error\n");
		return (1);
	}
	return (0);
}

int	checks(t_list *list)
{
	if (list->back != NULL)
	{
		while (list->next != NULL)
		{
			if (check_1(list))
				return (1);
			else if (check_2(list))
				return (1);
			else if (check_3(list))
				return (1);
			else if (check_4(list))
				return (1);
			list = list->next;
		}
	}
	if (check_list(list))
	{
		printf("1\n");
		printf("syntax error\n");
		return (1);
	}
	return (0);
}

int	symbols_check(t_list *list)
{
	if (list == NULL)
		return (0);
	if (list->type == PIPE)
	{
		printf("10\n");
		printf("syntax error\n");
		return (1);
	}
	if (list->back == NULL)
	{
		if (list->next != NULL)
			list = list->next;
	}
	return (checks(list));
}

int	check_back_1(t_list *node)
{
	return ((node->back != NULL && \
				(node->back->type != PIPE && node->back->type != AND \
				&& node->back->type != OR \
				&& node->back->content[0] != 40)) || \
			(node->next != NULL && node->next->type != COMMAND \
			&& node->next->type != PATH_COMMAND \
			&& node->next->content[0] != 40));
}

int	check_back_2(t_list *list, int *p)
{
	if (list->next != NULL && ((list->back && list->back->type \
					!= COMMAND && list->back->type != OPTIONS \
					&& list->back->content[0] != 41) \
				|| (list->next->type == COMMAND \
					|| list->next->type == OPTIONS)))
		return (1);
	(*p)--;
	return (0);
}

int	check_parenthesis_error(t_list *list)
{
	int		p;
	t_list	*node;

	node = list;
	p = 0;
	while (node)
	{
		if (node->content[0] == 40)
		{
			if (check_back_1(node))
				return (1);
			p++;
		}
		node = node->next;
	}
	while (list)
	{
		if (list->content[0] == 41)
		{
			if (check_back_2(list, &p))
				return (1);
		}
		list = list->next;
	}
	return (p);
}
