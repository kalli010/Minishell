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
  VAR,
  PATH_COMMAND
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
  struct s_tree *next_sibling;
} t_tree;

typedef struct helper
{
    char **envp;
    char  *cmd;
    char  **option;
} t_helper;

typedef struct heredoc
{
  int fd;
  char *del;

} t_here_doc;


typedef struct s_free{
  
} t_free;

#endif
