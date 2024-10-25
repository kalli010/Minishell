/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_dquotes_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:47:02 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/19 23:47:04 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_cpy(char *n_list, char *str)
{
	int	i;
	int	j;

	if (str == NULL)
		return ;
	j = ft_strlen(n_list);
	i = -1;
	while (str[++i])
		n_list[j++] = str[i];
	n_list[j] = '\0';
}

char	*get_new_list(char *fstr, char *var, char *tstr)
{
	char	*n_list;
	int		len;

	n_list = NULL;
	len = ft_strlen(fstr) + ft_strlen(var) + ft_strlen(tstr);
	n_list = (char *)malloc(sizeof(char) * (len + 1));
	if (n_list == NULL)
		return (NULL);
	n_list[0] = '\0';
	ft_cpy(n_list, fstr);
	ft_cpy(n_list, var);
	ft_cpy(n_list, tstr);
	return (n_list);
}

int	creat_sstr(t_list **list, int *len, char **sstr, int s)
{
	if ((*list)->content[*len] == '$')
		(*len)++;
	if ((*list)->content[*len] == '?')
		(*len)++;
	else
	{
		while (ft_isalpha((*list)->content[*len])
			|| ft_isdigit((*list)->content[*len])
			|| (*list)->content[*len] == '_')
			(*len)++;
	}
	*sstr = ft_substr((*list)->content, s + 1, *len - (s + 1));
	if ((*sstr != NULL && !ft_isalpha((*sstr)[0]) && (*sstr)[0] != '_'
			&& (*sstr)[0] != '?') || (*sstr) == NULL)
		return (1);
	return (0);
}

int	check_red_error(t_list **list, t_var_dquotes *dq)
{
	int	s;

	s = count_words(dq->var);
	if (s > 1 && (*list)->back && ((*list)->back->type == APPEND
			|| (*list)->back->type == INPUT || (*list)->back->type == OUTPUT))
	{
		free(dq->fstr);
		free(dq->sstr);
		free(dq->tstr);
		free(dq->var);
		return (1);
	}
	if (s == 0 && dq->tstr == NULL && (*list)->back
		&& ((*list)->back->type == APPEND || (*list)->back->type == INPUT
			|| (*list)->back->type == OUTPUT))
	{
		free(dq->fstr);
		free(dq->sstr);
		free(dq->tstr);
		free(dq->var);
		return (1);
	}
	return (0);
}
