/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:47:25 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/26 14:56:27 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_helper	g_helper;

int	build_and_execute_tree(int hd)
{
	if (check_parenthesis(g_helper.list))
		g_helper.root = creat_tree_with_parenthesis(g_helper.list);
	else
		g_helper.root = creat_tree(g_helper.list);
	clean_linked_list_par(&g_helper.list);
	print_tree(g_helper.root, 0);
	find_command(g_helper.root, &g_helper, &g_helper.root);
	check_signal();
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
		return (g_helper.exit_status = 2,2);
	if (tokenize_and_create_list(cmd, &tokens))
		return (g_helper.exit_status = 2,2);
	if (parser_redirections(&tokens))
		return (g_helper.exit_status = 2,2);
	if (check_and_expand_symbols())
		return (g_helper.exit_status = 2,2);
	if (check_wildcards(g_helper.list))
		wildcards(&g_helper.list);
	hd = check_heredoc(g_helper.list);
	if (process_heredocs(hd, &hdc))
		return (g_helper.exit_status = 2,2);
	remove_quotes(g_helper.list);
	clean_linked_list(&g_helper.list);
	if (build_and_execute_tree(hd))
		return (g_helper.exit_status = 2,2);
	my_free(&g_helper);
	return (EXIT_SUCCESS);
}

// int ft_minishell(char *line)
// {
//   char **tokens;
//   char *cmd;
//   int hd;
//   t_list *tmp;
// 	t_heredoc	hdc;
//
//   if (quotes_check(line))
//     return (1);
//   if(split_symbols(line, &cmd))
//   {
//     free(line);
//     return(1);
//   }
//   free(line);
//   if(tokenizer(cmd, &tokens))
//   {
//     free(cmd);
//     return(1);
//   }
//   if(creat_linked_list(&g_helper.list, tokens))
//     return(1);
//   if (check_red_with_cmd(g_helper.list))
//   {
//     if(recreate_linked_list(g_helper.list, &g_helper.list))
//     {
//       free(tokens);
//       return(1);
//     }
//   }
//   if (symbols_check(g_helper.list))
//   {
//     free_list(g_helper.list);
//     free(tokens);
//     return (1);
//   }
//   if (check_parenthesis_error(g_helper.list))
//   {
//     printf("syntax error\n");
//     free_list(g_helper.list);
//     free(tokens);
//     return (1);
//   }
//   if(check_expander(g_helper.envp, &g_helper.list))
//   {
//     printf("malloc failed.\n");
//     free_list(g_helper.list);
//     free(tokens);
//     return(1);
//   }
//   clean_linked_list(&g_helper.list);
//   tmp = g_helper.list;
//   while(tmp)
//   {
//     token_type(tmp);
//     tmp = tmp->next;
//   }
//   if(check_wildcards(g_helper.list))
//     wildcards(&g_helper.list);
//   hd = check_heredoc(g_helper.list);
//   if (hd > 16)
//   {
//     printf("Error.\n");
//     return (1);
//   }
//   else if (hd)
//   {
//     hdc.env =  g_helper.envp;
//     hdc.xenv =  g_helper.xenv;
//     init_hd(&hdc, &g_helper.list, &g_helper.redfile);
//     if (heredoc(&hdc, hd))
//       return (1);
//   }
//   remove_quotes(g_helper.list);
//   if (check_parenthesis(g_helper.list))
//     g_helper.root = creat_tree_with_parenthesis(g_helper.list);
//   else
//     g_helper.root = creat_tree(g_helper.list);
//   print_tree(g_helper.root, 0);
//   find_command(g_helper.root, &g_helper, &g_helper.root);
//   check_signal();
//   my_free(&g_helper);
//   if (hd)
//     if (clean_heredoc(g_helper.redfile, hd))
//       return (1);
//   free(g_helper.redfile);
//   free_tree(g_helper.root);
//   return (0);
// }
//
// int main(int ac, char **av, char **envp)
// {
//   char *line;
//
//   (void)ac, (void)av;
//   init_helper();
//   g_helper.envp = create_env(envp);
//   g_helper.xenv = create_env(envp);
//   while (1)
//   {
//     signal_handeler(BEFORE);
//     line = readline("(minishell)-> ");
//     init_helper_2();
//     signal_handeler(PARENT);
//     if (line == NULL)
//     {
//       printf("exit \n");
//       free(line);
//       printf("%d\n",g_helper.exit_status);
//       (clean_env(g_helper.envp),clean_env(g_helper.xenv));
//       exit(g_helper.exit_status);
//     }
//     if (ft_strlen(line) > 0)
//       add_history(line);
//     if (line)
//       ft_minishell(line);
//   }
//   return (EXIT_SUCCESS);
// }
//
