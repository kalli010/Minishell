#ifndef STRUCTS_H
# define STRUCTS_H

#include <stdbool.h>

typedef enum s_ttype{
  WORD,
  COMMAND,
  PIPE, 
  OR, 
  AND, 
	OUTPUT, /*>*/
	HEREDOC, /*<<*/
	INPUT, /*<*/
	APPEND, /*>>*/
  OPTIONS,
  PATH,
  VAR,
  SET_VAR,
  PATH_COMMAND,
  DELIMITER,
  PARENTHESIS,
} t_ttype;

typedef struct helper
{
    char **envp;
    char  *cmd;
    char  **option;
    char **xenv;
    pid_t	pid;
    int exit_status;
    bool flag;
    int redout;
    int redin;
} t_helper;

extern t_helper *g_helper;


typedef struct s_file
{
    char        *file_name;
    t_ttype     type;
    struct s_file *next;
} t_file;

//linked list
typedef struct s_list{
  char *content;
  t_ttype type;
  struct s_list *next;
  struct s_list *back;
  int i;
} t_list;

//LCRS tree
typedef struct s_tree {
  t_list *content;
  struct s_tree *first_child;
  struct s_tree *next_sibling;
} t_tree;


typedef struct s_free{
  
} t_free;

#endif
