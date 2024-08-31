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
  SET_VAR,
  PATH_COMMAND,
  DELIMITER
} t_ttype;

// typedef struct widls
// {
//   struct dirent *entry;
//   DIR *dirc;
//   char *buff;

// } wild_t;

typedef struct heredoc
{
  int fd;
  char *del;

} t_here_doc;

//linked list
typedef struct s_list{
  char *content;
  t_ttype type;
  struct s_list *next;
  struct s_list *back;
} t_list;

//LCRS tree
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
    int   e_status;
    t_here_doc here_doc;
} t_helper;



typedef struct s_free{
  
} t_free;

#endif
