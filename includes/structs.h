/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:12:54 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/26 14:46:13 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum s_ttype
{
	WORD,
	COMMAND,
	PIPE,
	OR,
	AND,
	OUTPUT,
	HEREDOC,
	INPUT,
	APPEND,
	OPTIONS,
	PATH,
	PATH_COMMAND,
	DELIMITER,
	PARENTHESIS,
}						t_ttype;

typedef struct s_malloc
{
	void				*data;
	struct s_malloc		*next;
}						t_malloc;

typedef struct s_redirect
{
	char				*filename;
	int					type;
	int					flag;
	struct s_redirect	*next;
}						t_redirect;

typedef struct s_list
{
	char				*content;
	t_ttype				type;
	struct s_list		*next;
	struct s_list		*back;
	int					i;
	int					in;
}						t_list;

typedef struct s_tree
{
	t_list				*content;
	struct s_tree		*first_child;
	struct s_tree		*next_sibling;
}						t_tree;

typedef struct helper
{
	char				*cmd;
	char				**option;
	char				*pwd;
	char				**envp;
	char				**xenv;
	char				**redfile;
	t_list				*list;
	t_tree				*root;
	int					flag;
	int					exit_status;
	int					fd;
	int					cd;
}						t_helper;

typedef struct s_file
{
	char				*file_name;
	t_ttype				type;
	struct s_file		*next;
}						t_file;

typedef struct s_free
{
}						t_free;

#endif
