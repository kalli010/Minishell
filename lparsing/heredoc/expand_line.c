/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:47:48 by zelkalai          #+#    #+#             */
/*   Updated: 2024/11/02 17:03:27 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	set_sstr(t_expand_line *xl, char *str)
{
	if (str[xl->len] == '?')
		xl->len++;
	else
	{
		while (ft_isalpha(str[xl->len]) || ft_isdigit(str[xl->len])
			|| str[xl->len] == '_')
			xl->len++;
	}
	xl->sstr = ft_substr(str, xl->s + 1, xl->len - (xl->s + 1));
	if (xl->sstr != NULL && !ft_isalpha(xl->sstr[0]) && xl->sstr[0] != '_'
		&& xl->sstr[0] != '?')
	{
		free(xl->fstr);
		free(xl->sstr);
		return (1);
	}
	return (0);
}

void	free_xl(t_expand_line *xl)
{
	free(xl->fstr);
	free(xl->sstr);
	free(xl->tstr);
	free(xl->var);
}

int	expand_line(char **env, char **str, int d)
{
	t_expand_line	xl;

	set_expande_line(&xl, d, *str);
	xl.s = xl.len;
	if ((*str)[xl.len] == '$')
		xl.len++;
	if (set_sstr(&xl, *str))
		return (1);
	xl.s = xl.len;
	while ((*str)[xl.len])
		xl.len++;
	xl.tstr = ft_substr(*str, xl.s, xl.len - xl.s);
	if (xl.sstr)
	{
		if (xl.sstr[0] == '?')
			xl.var = ft_itoa(g_helper.exit_status);
		else
			xl.var = ft_getenv(env, xl.sstr, -1);
	}
	else
		xl.var = ft_getenv(env, xl.sstr, -1);
	free(*str);
	*str = NULL;
	*str = get_new_list(xl.fstr, xl.var, xl.tstr);
	return (free_xl(&xl), 0);
}
