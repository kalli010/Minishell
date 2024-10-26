/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:51:14 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/25 14:51:16 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_line_errors(char *line, char **cmd)
{
	if (quotes_check(line))
		return (EXIT_FAILURE);
	if (split_symbols(line, cmd))
	{
		free(line);
		return (EXIT_FAILURE);
	}
	free(line);
	return (EXIT_SUCCESS);
}

int	tokenize_and_create_list(char *cmd, char ***tokens)
{
	if (tokenizer(cmd, tokens))
	{
		free(cmd);
		return (EXIT_FAILURE);
	}
	if (creat_linked_list(&g_helper.list, *tokens))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	parser_redirections(char ***tokens)
{
	if (check_red_with_cmd(g_helper.list))
	{
		if (recreate_linked_list(g_helper.list, &g_helper.list))
		{
			free(*tokens);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	check_and_expand_symbols(void)
{
	if (symbols_check(g_helper.list))
	{
		free_list(g_helper.list);
		return (EXIT_FAILURE);
	}
	if (check_parenthesis_error(g_helper.list))
	{
		printf("syntax error\n");
		free_list(g_helper.list);
		return (EXIT_FAILURE);
	}
	if (check_expander(g_helper.envp, &g_helper.list))
	{
		printf("malloc failed.\n");
		free_list(g_helper.list);
		return (EXIT_FAILURE);
	}
	clean_linked_list(&g_helper.list);
	return (EXIT_SUCCESS);
}

int	process_heredocs(int hd, t_heredoc *hdc)
{
  int i;

	if (hd > 16)
	{
		printf("Error.\n");
		return (EXIT_FAILURE);
	}
	else if (hd)
	{
		hdc->env = g_helper.envp;
		hdc->xenv = g_helper.xenv;
		init_hd(hdc, &g_helper.list, &g_helper.redfile);
		if (heredoc(hdc, hd))
    {
      i = -1;
      free(g_helper.redfile);
      free_list(*hdc->list);
			return (EXIT_FAILURE);
    }
  }
	return (EXIT_SUCCESS);
}
