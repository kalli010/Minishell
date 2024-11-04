/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:47:25 by zelkalai          #+#    #+#             */
/*   Updated: 2024/11/04 06:12:16 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_helper	g_helper;

int	build_and_execute_tree(int hd)
{
	int status;
	
	if (check_parenthesis(g_helper.list))
		g_helper.root = creat_tree_with_parenthesis(g_helper.list);
	else
		g_helper.root = creat_tree(g_helper.list);
	clean_linked_list_par(&g_helper.list);
	// print_tree(g_helper.root, 0);
  status = find_command(g_helper.root, &g_helper, &g_helper.root);
	if (status == 130)
		write(1,"\n",1);
	if (hd)
		if (clean_heredoc(g_helper.redfile, hd))
			return (EXIT_FAILURE);
	free(g_helper.redfile);
	free_tree(g_helper.root);
	return (EXIT_SUCCESS);
}

int	ft_minishell(char *line)
{
	char		**tokens;
	char		*cmd;
	int			hd;
	t_heredoc	hdc;

	if (check_line_errors(line, &cmd))
		return (g_helper.exit_status = 2, 2);
	if (tokenize_and_create_list(cmd, &tokens))
		return (g_helper.exit_status = 2, 2);
	if (parser_redirections(&tokens))
		return (g_helper.exit_status = 2, 2);
	if (check_and_expand_symbols())
		return (g_helper.exit_status = 2, 2);
	if (check_wildcards(g_helper.list))
		wildcards(&g_helper.list);
	hd = check_heredoc(g_helper.list);
	if (process_heredocs(hd, &hdc))
		return (g_helper.exit_status = 2, 2);
	clean_linked_list(&g_helper.list);
	remove_quotes(g_helper.list);
	if (build_and_execute_tree(hd))
		return (g_helper.exit_status = 2, 2);
	my_free(&g_helper);
	return (EXIT_SUCCESS);
}
