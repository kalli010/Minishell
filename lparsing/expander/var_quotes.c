/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:47:08 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/25 13:12:57 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_vs(t_var_split *vs, int *cw, int *end)
{
	vs->c = cw;
	*end = 0;
	vs->end = end;
}

int	var_split(char *str, char ***array)
{
	t_var_split	vs;
	int			i;
	int			s;
	int			end;
	int			cw;

	init_vs(&vs, &cw, &end);
	remove_quotes_string(str);
	cw = count_words(str);
	vs.list = (char **)malloc(sizeof(char *) * (*vs.c + 1));
	if (vs.list == NULL)
		return (1);
	i = 0;
	vs.i = &i;
	*vs.c = 0;
	while (str[*vs.i])
	{
		get_words(vs.i, vs.end, str);
		s = set_words(&str, &vs, vs.list);
		if (s == 2)
			return (1);
		else if (s == 1)
			break ;
	}
	return (vs.list[*vs.c] = NULL, *array = vs.list, 0);
}

int	replace_list_node(t_list **list, char **array, t_list **n_list,
		t_list **tmp)
{
	t_list	*back;

	if (var_split((*list)->content, &array))
		return (2);
	if (creat_linked_list(n_list, array))
	{
		free(array);
		return (2);
	}
	*tmp = (*list)->next;
	back = (*list)->back;
	if ((*list)->back != NULL)
		(*list)->back->next = NULL;
	free((*list)->content);
	free(*list);
	if (back != NULL)
	{
		*list = back;
		ft_lstadd_back(list, *n_list);
		*list = (*list)->next;
		token_type(*list);
	}
	else
		(*list) = *n_list;
	return (0);
}

int	var_quotes(char **env, t_list **list, int d)
{
	char	**array;
	t_list	*n_list;
	t_list	*tmp;
	int		i;

	array = NULL;
	n_list = NULL;
	i = var_dquotes(env, list, d);
	if (i == 1)
		return (1);
	else if (i == 2)
		return (2);
	if ((*list)->content[0] != '\0')
	{
		if (replace_list_node(list, array, &n_list, &tmp))
			return (2);
		ft_lstadd_back(list, tmp);
	}
	return (0);
}
