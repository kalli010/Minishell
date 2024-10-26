/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:28:06 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/26 14:54:27 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
# include <structs.h>
# include <structs_helper.h>
# include <exuc.h>
# include <libft.h>
# include <fnmatch.h>
# include <dirent.h>

extern t_helper			g_helper;

//main
int		main(int ac, char **av, char **envp);
int		build_and_execute_tree(int hd);
int		ft_minishell(char *line);
void	init_helper(void);
void	init_helper_2(void);
int		check_line_errors(char *line, char **cmd);
int		tokenize_and_create_list(char *cmd, char ***tokens);
int		parser_redirections(char ***tokens);
int		check_and_expand_symbols(void);
int		process_heredocs(int hd, t_heredoc *hdc);

//lparcing
int		checks(t_list *list);
int		symbols_check(t_list *list);
int		check_back_1(t_list *node);
int		check_back_2(t_list *list, int *p);
int		check_parenthesis_error(t_list *list);
int		check_list(t_list *list);
int		check_1(t_list *list);
int		check_2(t_list *list);
int		check_3(t_list *list);
int		check_4(t_list *list);
int		fork_failes(t_open_file *of);
int		open_file(char *redfile, t_heredoc *hd);
int		update_list_with_redirection(\
		t_imp_hc *imh, t_list **list, char ***redfile, int i);
int		process_heredoc_node(\
		t_list **list, t_imp_hc *imh, char ***redfile, int *i);
int		implementing_heredoc(t_list **list, char ***redfile);
int		set_sstr(t_expand_line *xl, char *str);
void	free_xl(t_expand_line *xl);
int		expand_line(char **env, char **str, int d);
int		check_and_open_file(t_open_file *of, char *redfile, t_list *delimiter);
int		write_to_file(t_open_file *of, t_list *delimiter);
void	free_line(t_open_file *of, t_heredoc *hd);
int		read_line(t_open_file *of, t_list *delimiter);
void	heredoc_child_process(t_open_file *of, t_heredoc *hd);
void	sigint_handler(int sig);
void	init_hd(t_heredoc *hd, t_list **list, char ***rf);
void	initialize_heredoc(t_heredoc *hd, int size);
int		heredoc(t_heredoc *hd, int size);
char	*ft_strcpy(char *dest, const char *src);
double	check_heredoc(t_list *list);
int		clean_heredoc(char **redfile, int hd);
int		check_quotes(char *str);
void	set_expande_line(t_expand_line *xl, int d, char *str);
void	quote_cleanup_loop(t_list *list, int *j, int *q_n);
void	remove_quotes(t_list *list);
int		check_unset(char *str);
void	remove_env_var(char ***env, char *content);
int		unset(char ***env, t_list *list);
int		extract_var_name(t_list *list, char **var);
int		validate_var_name(char *var);
char	*extract_value(t_list *list, int start);
int		check_and_update_env(\
		char ***env, char ***xenv, t_set_var *sv, t_list *list);
int		add_var(char **env_or_xenv, char *var, char *value, int index);
char	**allocate_new_env(t_add_env_params *params);
int		copy_old_env(t_add_env_params *params, char **new_env);
int		handle_add_variable(t_add_env_params *params, char **new_env, int len);
char	**add_new_env(t_add_env_params *params);
int		check_content(char *str);
int		set_var(t_list *list, char ***env, char ***xenv);
int		check_cmd_export(t_list *list);
int		check_var(t_list *list, char ***env, char ***xenv);
void	init_params(\
		t_add_env_params *p_env, char **env, char *var, char *value);
int		add_new_var_to_env(char ***env, char ***xenv, t_set_var *sv, int s);
void	init_sv(t_set_var *sv, char *var, char *value);
void	validate_tokens(char *str, int *i, int *s);
void	parse_symbols(char *str, int *i, int *s);
int		validate_tokens_2(char *str, int *i);
int		parse_symbols_2(char *str, int *i);
int		get_var_value(char *env, char **var, char **value);
int		export(char **env);
int		set_1(t_list *list);
int		set_2(t_list *list);
int		token_type(t_list *list);
int		check_e(int *e, char c);
int		quotes_check(char *str);
void	if_root_null(t_tree **r_tree, t_tree **l_node, t_list *list,
			t_tree **root);
void	manage_tree_with_pr(t_list **list, t_tree **r_tree, t_tree **root,
			t_tree **l_node);
t_tree	*creat_tree_with_parenthesis(t_list *list);
void	print_tree(t_tree *root, int spaces);
int		check_tmp(t_list *tmp);
t_tree	*create_tree_node(t_list *list);
void	add_child_to_tree(t_tree *parent, t_tree *child);
void	add_sibling_to_child(t_tree *child, t_tree *sibling);
int		check_parenthesis(t_list *list);
void	add_l_tree(t_tree **l_tree, t_tree **r_tree, t_tree **s_tree);
void	add_s_tree(t_tree **r_tree, t_tree **s_tree);
void	set_to_null(t_tree **s_tree, t_tree **r_tree, t_tree **l_tree);
t_tree	*creat_subtree(t_list **list);
void	attach_node_to_tree(t_tree **l_node, t_list *list, t_tree **r_tree);
void	add_n_node(t_tree **l_node, t_tree *root, t_tree **n_node);
t_tree	*or_and_tree(t_list **lst, t_tree **l_node, t_tree **root,
			t_tree **n_node);
t_tree	*creat_tree(t_list *lst);
void	free_tree(t_tree *root);
int		has_wildcard(t_list *node);
void	skip_wildcards(t_list **list, t_list **tmp, int d);
void	process_wildcard_for_entry(t_list **list, t_list **tmp, DIR *dir);
void	reset_linked_list(t_list **list, t_list *tmp);
int		wildcards(t_list **list);
void	wildcards_linked_list(t_list *list, char *str);
void	clean_wildcards(t_list **list);
int		find_first_non_star(char *wc);
void	check_flag(int *len, int *flag, char *wc);
int		process_substring(char *wc, const char *filename, int *flag, int *len);
void	skip_stars(char *wc, int *len);
t_list	*ft_lstnew_2(char *content);
int		implementing_wildcards(char *wc, const char *filename);
int		check_wildcards(t_list *list);
int		find_exact_match(const char *filename, char *str);
int		find_partial_match(const char *filename, char *str);
int		find_full_match(const char *filename, char *str);
int		ft_find(const char *filename, char *str, int flag);
void	clean_env(char **env);
int		env_size(char **str);
char	**create_env(char **envp);
int		is_special_symbol(char c);
void	handle_special_symbol(char *str, int *i);
void	handle_normal_token(char *str, int *i);
void	handle_complex_token(char *str, int *i);
void	handle_post_symbol_token(char *str, int *i, int *x);
int		finalize_token(int start, int end, t_tokenizer *tk, char *str);
void	free_all_tokens(char **tokens, int j);
int		process_token_2(int *i, int *x, t_tokenizer *tk, char *str);
int		echo_create_tokens(char *str, t_tokenizer *tk);
void	skip_quoted_part(char *str, int *i);
void	skip_quoted_section(int *c, char *str, int *i, int *in_word);
int		count_words(char *str);
int		malloc_str(t_split_tokens *st, char *tokens);
void	skip_extra_spaces(t_split_tokens *st, char *tokens, int *i);
int		split_tokens(char *tokens, char **tkn);
int		echo_check(char *str);
void	parse_symbols_and_words(char *str, int *i);
int		echo_token_count(char *str);
void	parse_token_with_quotes(char *str, int *s, int *i);
int		token_count(char *str);
int		tokenizer(char *str, char ***tokens);
int		process_token(int *i, int s, t_tokenizer *tk);
int		handle_echo_token(int s, t_tokenizer *tk);
void	skip_non_whitespace(char *str, int *i);
int		create_tokens_loop(t_tokenizer *tk);
int		process_command_and_options(t_list **n_list, t_list **tmp,
			t_list *start, t_list **e);
int		add_original_content(t_list **n_list, t_list *list);
void	free_processed_commands(t_list *end);
int		collect_command_and_options(t_list *list, t_list **n_list, t_list *tmp,
			t_list *start);
void	set_token_types(t_list *tmp, t_list *n_list, t_list **lst);
void	set_lst_null(t_list **tmp, t_list **list, t_list **n_list);
int		recreate_linked_list(t_list *list, t_list **lst);
void	clean_linked_list(t_list **list);
void	clean_linked_list_par(t_list **list);
void	free_list(t_list *list);
int		creat_linked_list(t_list **list, char **tokens);
int		check_red_with_cmd(t_list *list);
void	find_command_end(t_list *list, t_list **tmp);
int		update_str(t_split_symbols *ss, char *str);
void	insert_symbol_with_spaces(\
		t_split_symbols *ss, char *str, int *i, int *s);
int		split_symbols(char *str, char **cmd);
void	creat_var(char **sstr, char **var, char **env);
void	free_var_dquotes(t_list **list, t_var_dquotes *dq);
void	init_dq(t_var_dquotes *dq, int d, t_list *list);
int		var_dquotes(char **env, t_list **list, int d);
int		expander(char **env, t_list **list, int d);
int		check_d(char *str, int i);
int		check_squotes(char *str, int i);
int		process_expansion(char **env, t_list **list, int i);
int		check_expander(char **env, t_list **list);
void	init_vs(t_var_split *vs, int *cw, int *end);
int		var_split(char *str, char ***array);
int		replace_list_node(t_list **list, char **array, t_list **n_list,
			t_list **tmp);
int		var_quotes(char **env, t_list **list, int d);
void	ft_cpy(char *n_list, char *str);
char	*get_new_list(char *fstr, char *var, char *tstr);
int		creat_sstr(t_list **list, int *len, char **sstr, int s);
int		check_red_error(t_list **list, t_var_dquotes *dq);
int		find_env_variable(char **env, char *str, int *s);
char	*extract_env_value(char **env, int index, char *str);
char	*ft_getenv(char **env, char *str, int s);
void	get_words(int *i, int *end, char *str);
int		count_quotes(char *str);
int		check_qts(char **str, int *j, int *q_n, char q);
void	remove_quotes_string(char *str);
int		set_words(char **str, t_var_split *vs, char **list);

#endif
