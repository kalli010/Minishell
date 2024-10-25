#ifndef STRUCTS_HELPER_H
# define STRUCTS_HELPER_H

typedef struct s_var_dquotes
{
	char	*fstr;
	char	*sstr;
	char	*tstr;
	char	*var;
	int		len;
	int		s;
}			t_var_dquotes;

typedef struct s_var_split
{
	char	**list;
	int		*i;
	int		*c;
	int		*end;
}			t_var_split;

typedef struct s_insert_new_var
{
	char	**value;
	char	**new_env;
	char	**var;
	char	**env_or_xenv;
	int		len;
}			t_insert_new_var;

typedef struct s_expand_line
{
	char	*fstr;
	char	*sstr;
	char	*tstr;
	char	*var;
	int		len;
	int		s;
}			t_expand_line;

typedef struct s_open_file
{
	int		fd;
	char	*line;
	pid_t	pid;
	int		status;
	int		d;
	int		i;
}			t_open_file;

typedef struct s_heredoc
{
	char	*nbr;
	int		j;
	t_list	*delimiter;
	int		i;
	int		n;
	char	**env;
	char	**xenv;
	char	***rf;
	t_list	**list;
}			t_heredoc;

typedef struct s_imp_hc
{
	t_list	*back;
	t_list	*next;
	t_list	*tmp;
	char	*red;
}			t_imp_hc;

typedef struct s_split_symbols
{
	char	*tmp;
	char	q;
	int		check;
}			t_split_symbols;

typedef struct s_split_tokens
{
	char	*str;
	int		len;
	int		wd;
	char	q;
}			t_split_tokens;

typedef struct s_set_var
{
	char	*var;
	char	*value;
}			t_set_var;

typedef struct s_tokenizer
{
	char	*str;
	char	***tokens;
	int		*j;
}			t_tokenizer;

typedef struct s_add_env_params {
  char **env_or_xenv;
  int s;
  char *var;
  char *value;
  int check;
} t_add_env_params;

#endif
