# ifndef MINISHELL_H
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
# include <exuc.h>
# include <libft.h>
#include <fnmatch.h>
#include <dirent.h>

#define EXIT_PARSER (2)

//lparsiiiiiiing
int quotes_check(char *str);
void check_p_r(char *str, int *i, int *s);
int check_p_r2(char *str,int *i);
int split_symbols(char *str, char **cmd);
int echo_check(char *str);
int echo_token_count(char *str);
int token_count(char *str);
int count_words(char *str);
int split_tokens(char *tokens, char **tkn);
int echo_create_tokens(char *str, int j, char ***tokens);
int create_tokens(char *str, char ***tokens);
int tokenizer(char *str, char ***tokens);
void token_type(t_list *list);
int creat_linked_list(t_list **list, char **tokens);
int check_red_with_cmd(t_list *list);
void free_list(t_list *list);
int recreate_linked_list(t_list *list, t_list **lst);
int symbols_check(t_list *list);
void ft_cpy(char *n_list, char *str);
char *get_new_list(char *fstr, char *var, char *tstr);
char *ft_getenv(char **env, char *str);
int var_dquotes(char **env, t_list **list, int d);
void get_words(int *i, int *end, char *str);
int count_quotes(char *str);
void remove_quotes_string(char *str);
int var_split(char *str, char ***array);
int var_quotes(char **env, t_list **list, int d);
int expander(char **env, t_list **list, int d);
int check_d(char *str, int i);
int check_squotes(char *str, int i);
int check_expander(char **env, t_list **list);
void clean_linked_list(t_list **list);
int add_var(char **env_or_xenv, char *var, char *value, int index);
char **add_new_env(char **env_or_xenv, int s, char *var, char *value, int check);
int set_var(t_list *list, char ***env, char ***xenv);
int check_schar(t_list *list);
int check_var(t_list *list, char ***env, char ***xenv);
void remove_quotes(t_list *list);
t_tree *create_tree_node(t_list *list);
void add_child_to_tree(t_tree *parent, t_tree *child);
void add_sibling_to_child(t_tree *child, t_tree *sibling);
int check_parenthesis(t_list *list);
int check_parenthesis_error(t_list *list);
t_tree *creat_subtree(t_list **list);
t_tree *creat_tree_with_parenthesis(t_list *list);
t_tree *creat_tree(t_list *list);
void print_tree(t_tree *root, int spaces);
void free_tree(t_tree *root);
int env_size(char **str);
char **create_env(char **envp);
int get_var_value(char *env, char **var, char **value);
int export(char **env);
int unset(char ***env, t_list *list);
char *ft_strcpy(char *dest, const char *src);
double check_heredoc(t_list *list);
int clean_heredoc(char **redfile, int hd);
int check_quotes(char *str);
int expand_line(char **env, char **str, int d);
int open_file(char *redfile, t_list *delimiter, char **env, char **xenv, t_list *list, char ***rf);
int check_command_type(char *content);
void implementing_heredoc(t_list **list, char ***redfile);
int heredoc(t_list **list, int size, char **env, char **xenv, char ***rf);
int check_wildcards(t_list *list);
int implementing_wildcards(char *wc, const char *filename);
void wildcards_linked_list(t_list *list, char *str);
void clean_wildcards(t_list **list);
int wildcards(t_list **list);
void clean_env(char **env);



#endif
