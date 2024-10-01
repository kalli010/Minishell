/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 05:52:36 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/01 05:52:50 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**get_options(t_helper *helper, t_list *list)
{
	int		i;
	int		count;
	char	**op;

	count = count_arg(list);
	if (count < 1)
		return (NULL);
	op = (char **)malloc((count + 2) * sizeof(char *));
	if (!op)
		return (NULL);
	op[0] = get_path(helper, list);
	if (!op[0])
		return (free(op), NULL);
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
