/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exuc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:45:11 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/09/07 14:21:10 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXUC_H
# define EXUC_H
#include <minishell.h>
#include <dirent.h>


#define P_DNIED (126)
#define SUCCESS (0)
#define ERROR_C (127)

#define BEFORE  888
#define PARENT  777
#define CHILD  666
#define IN_HERE_DOC  555


char	*get_path(t_helper *help,t_list *list);
int		find_command(t_tree *root, t_helper *helper);
char	**get_options(t_helper *helper, t_list *list);
void	free_array(char **arr);
int		here_doc(t_tree *root,t_helper *helper);
int		check_upper(char c);
int		check_if_uppercase(char *line);
char	*check_if_env(char **env,char *line);
int		ft_env(t_list *list,char **env);
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

int ft_unset(t_list *list,t_helper *helper);
void ctr_c(int sig);
void	signal_handeler(int place);

#endif
