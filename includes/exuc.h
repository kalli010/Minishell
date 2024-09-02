/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exuc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:45:11 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/09/02 06:11:33 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXUC_H
# define EXUC_H
#include <minishell.h>
#include <dirent.h>
#define RESET      "\001\e[0m\002"
#define BLACK      "\001\e[0;30m\002"
#define RED        "\001\e[0;31m\002"
#define GREEN      "\001\e[0;32m\002"
#define YELLOW     "\001\e[0;33m\002"
#define BLUE       "\001\e[0;34m\002"
#define MAGENTA    "\001\e[0;35m\002"
#define CYAN       "\001\e[0;36m\002"
#define WHITE      "\001\e[0;37m\002"
#define PURPLE      "\001\e[0;35m\002"


#define BOLD_BLACK "\001\e[1;30m\002"
#define BOLD_RED   "\001\e[1;31m\002"
#define BOLD_GREEN "\001\e[1;32m\002"
#define BOLD_YELLOW "\001\e[1;33m\002"
#define BOLD_BLUE  "\001\e[1;34m\002"
#define BOLD_MAGENTA "\001\e[1;35m\002"
#define BOLD_CYAN  "\001\e[1;36m\002"
#define BOLD_WHITE "\001\e[1;37m\002"


#define P_DNIED (126)
#define SUCCESS (0)
#define ERROR_C (127)
# define CALL  PURPLE "[minishell][:)]" CYAN"❯ " WHITE

char	*get_path(t_helper *help,t_list *list);
int		find_command(t_tree *root, t_helper *helper);
char	**get_options(t_helper *helper, t_list *list);
void	free_array(char **arr);
int		here_doc(t_tree *root,t_helper *helper);
int		check_upper(char c);
int		check_if_uppercase(char *line);
char	*check_if_env(char **env,char *line);
int		ft_env(char **env);
int		ft_pwd(t_list *list);
int		is_builtins(t_tree *root);
int		run_builtins(t_tree *root, t_helper *helper);
int		ft_cd(t_list *list);
unsigned char ft_exit(t_tree *root,t_helper *helper);
int 	redirect_output(t_tree *root,t_helper *helper);
int		execute(t_tree *root, t_helper *helper);
int     count_arg(t_list *list);
int		redirect_input(t_tree *root, t_helper *helper);
int		execute_pipe(t_tree *root, t_helper *helper);
int 	ft_echo(t_list *list);
int		check_and_or(t_tree *root, t_helper *helper);
void 	my_free(t_helper *helper);
void	free_list(t_list *list);




#endif
