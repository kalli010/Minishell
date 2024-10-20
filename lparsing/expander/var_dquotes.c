/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_dquotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:50:38 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/19 23:51:38 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	creat_var(char **sstr, char **var, char **env)
{
	if (*sstr)
	{
		if ((*sstr)[0] == '?')
			*var = ft_itoa(g_helper.exit_status);
		else
			*var = ft_getenv(env, *sstr, -1);
	}
	else
		*var = ft_getenv(env, *sstr, -1);
}

void	free_var_dquotes(t_list **list, t_var_dquotes *dq)
{
	free(dq->sstr);
	free((*list)->content);
	(*list)->content = get_new_list(dq->fstr, dq->var, dq->tstr);
	free(dq->fstr);
	free(dq->tstr);
	free(dq->var);
}

void	init_dq(t_var_dquotes *dq, int d, t_list *list)
{
	dq->var = NULL;
	dq->sstr = NULL;
	dq->tstr = NULL;
	dq->len = d;
	dq->fstr = ft_substr(list->content, 0, dq->len);
	dq->s = dq->len;
}

int	var_dquotes(char **env, t_list **list, int d)
{
	t_var_dquotes	dq;

	init_dq(&dq, d, *list);
	if (creat_sstr(list, &dq.len, &dq.sstr, dq.s))
	{
		free(dq.fstr);
		free(dq.sstr);
		return (1);
	}
	dq.s = dq.len;
	while ((*list)->content[dq.len])
		dq.len++;
	dq.tstr = ft_substr((*list)->content, dq.s, dq.len - dq.s);
	creat_var(&dq.sstr, &dq.var, env);
	if (check_red_error(list, &dq))
		return (1);
	free_var_dquotes(list, &dq);
	if ((*list)->content == NULL)
		return (2);
	return (0);
}
