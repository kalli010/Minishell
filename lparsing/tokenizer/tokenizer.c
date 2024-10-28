/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:51:50 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/19 22:00:30 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	tokenizer(char *str, char ***tokens)
{
	int			tc;
	t_tokenizer	tk;

	tk.str = str;
	tk.tokens = tokens;
	tc = token_count(str);
	*tokens = (char **)malloc(sizeof(char *) * (tc + 1));
	if (*tokens == NULL)
		return (1);
	if (create_tokens_loop(&tk))
		return (1);
	free(str);
	return (0);
}
