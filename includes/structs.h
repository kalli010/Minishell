#ifndef STRUCTS_H
# define STRUCTS_H

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
  VAR
} t_ttype;

typedef struct s_list{
  char *content;
  t_ttype type;
  struct s_list *next;
  struct s_list *back;
} t_list;

typedef struct s_tree {
  t_list *content;
  struct s_tree *first_child;
  //int child_counte;
  struct s_tree *next_brother;
} t_tree;

typedef struct helper
{
    char **envp;
    char  *path;
    char  *cmd;
    char  **cmd_flag;
} t_helper;


typedef struct s_free{
  
} t_free;

#endif
