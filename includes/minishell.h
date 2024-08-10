# ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
# include <structs.h>
# include <exuc.h>
# include <libft.h>

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
void remove_quotes(char *tokens);
int check_command(char **str);
char **tokenizer(char *str);
void token_type(t_list *list);
void creat_linked_list(t_list **list, char **tokens);
int symbols_check(t_list *list);
t_tree *create_tree_node(t_list *list);
void add_child_to_tree(t_tree *parent, t_tree *child);
void add_sibling_to_child(t_tree *child, t_tree *sibling);
t_tree *creat_tree(t_list *list);
void print_tree(t_tree *root, int spaces);

#endif
