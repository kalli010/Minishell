/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exuc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:45:11 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/02 03:03:09 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXUC_H
# define EXUC_H
#include <minishell.h>
#include <dirent.h>


#define P_DNIED (126)
#define SUCCESS (0)
#define ERROR_C (127)
#define CMD_NOT_FOUND 127
# define GREEN "\033[1;32m"
# define RESET "\033[0m"

#define BEFORE  888
#define PARENT  777
#define CHILD  666
#define IN_HERE_DOC  555
extern int g_exit_status;

#include <sys/types.h>
#include <sys/stat.h>

char	*get_path(t_helper *help,t_list *list);
int		find_command(t_tree *root, t_helper *helper);
char	**get_options(t_helper *helper, t_list *list);
void	free_array(char **arr);
int		check_upper(char c);
int		ft_env(t_list *list,char **env);
int		ft_pwd(t_list *list);
int		is_builtins(t_tree *root);
int		run_builtins(t_tree *root, t_helper *helper);
int		ft_cd(t_list *list,t_helper *helper);
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
void 	ctr_c(int sig);
void	signal_handeler(int place);
int helper_check_cmd(char *cmd, char *s);
int check_cmd(char *cmd, char *s, char **arg);
int is_only_bs(t_tree *root);
int is_only_slashes(t_tree *root);
void	exit_path(char *s, int status);
void handle_cd_error(const char *path, int error_type);
char *get_target_path(t_list *list, t_helper *helper);
int is_directory(const char *path);
int	errors(char *file,int status, int fd);
int prepare_command(t_tree *root, t_helper *helper);
int	check_file(const char *file);

#endif
