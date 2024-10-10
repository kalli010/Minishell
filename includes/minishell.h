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
//parsing
int quotes_check(char *str);
void check_p_r(char *str, int *i, int *s);
int check_p_r2(char *str,int *i);
char *split_symbols(char *str);
int echo_check(char *str);
int echo_token_count(char *str);
int token_count(char *str);
void echo_create_tokens(char *str, char **tokens, int j);
void create_tokens(char *str, char **tokens);
void remove_quotes(t_list *list);
int check_command(char **str);
char **tokenizer(char *str);
void token_type(t_list *list);
void creat_linked_list(t_list **list, char **tokens, int t);
int check_red_with_cmd(t_list *lins);
t_list *recreate_linked_list(t_list *list);
int check_red(t_list *list);
void create_list_with_red(t_list **list);
int symbols_check(t_list *list);
int set_var(t_list *list, char ***env, char ***xenv);
void check_var(t_list *list, char ***env, char ***xenv);
int check_expander(char **env, t_list **list);
void clean_linked_list(t_list **list);
double check_heredoc(t_list *list);
char **heredoc(t_list **list, int size, char **env);
t_tree *create_tree_node(t_list *list);
void add_child_to_tree(t_tree *parent, t_tree *child);
void add_sibling_to_child(t_tree *child, t_tree *sibling);
int check_parenthesis_error(t_list *list);
int check_parenthesis(t_list *list);
t_tree *creat_subtree(t_list **list);
t_tree *creat_tree_with_parenthesis(t_list *list);
t_tree *creat_tree(t_list *list);
void print_tree(t_tree *root, int spaces);
char *ft_getenv(char **env, char *str);
char **create_env(char **envp);
void export(char **env);
char **unset(char **env, char *str);
int clean_heredoc(char **redfile, int hd);


int wildcards(t_list **list);
int check_Wildcards(t_list *list);
void token_type(t_list *list);

#endif
