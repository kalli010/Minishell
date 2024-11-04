/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exuc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:45:11 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/11/04 07:41:56 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXUC_H
# define EXUC_H

# include <minishell.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <stdbool.h>

# define GREEN "\033[1;32m"
# define RED "\033[1;31m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define MAGENTA "\033[1;35m"
# define CYAN "\033[1;36m"
# define WHITE "\033[1;37m"
# define BLACK "\033[0;30m"
# define M_SHELL "\033[1;31mminishell: \033[0m"
# define P_DNIED 126
# define SUCCESS 0
# define ERROR_C 127
# define CMD_NOT_FOUND 127
# define MAX_PATH 4096
# define BEFORE 888
# define PARENT 777
# define CHILD 666
# define IN_HERE_DOC 555

int 			has_slash(char *str);
char			*get_path(t_helper *help, t_list *list);
int				find_command(t_tree *root, t_helper *helper, t_tree **rt);
char			**get_options(t_helper *helper, t_list *list);
void			free_array(char **arr);
int				command_not_found(char *cmd);
int				is_dir(char *dir);
int				ft_env(t_list *list, char **env);
int				ft_pwd(t_helper *helper);
int				is_builtins(t_tree *root);
int				run_builtins(t_tree *root, t_helper *helper);
int				ft_cd(t_list *list, t_helper *helper);
unsigned char	ft_exit(t_tree *root, t_helper *helper);
int				execute(t_tree *root, t_helper *helper, t_tree **rt);
int				count_arg(t_list *list);
int				execute_pipe(t_tree *root, t_helper *helper, t_tree **rt);
int				ft_echo(t_list *list);
int				check_and_or(t_tree *root, t_helper *helper, t_tree **rt);
void			my_free(t_helper *helper);
char			*get_target_path(t_list *list, t_helper *helper);
void			free_list(t_list *list);
int				ft_unset(t_list *list, t_helper *helper);
void			ctr_c(int sig);
void			signal_handeler(int place);
int				is_only_bs(t_tree *root);
void			handle_cd_error(const char *path, int error_type);
char			*get_target_path(t_list *list, t_helper *helper);
int				errors(char *file, int status, int fd);
int				prepare_command(t_tree *root, t_helper *helper);
int				check_write_and_dir(char *file);
int				check_read(char *file);
int				check_permission(char *file);
int				check_existence(char *file, int flag);
int				get_permission(char *file);
int				open_fd(char *file, int type);
t_redirect		*init_redirect_lst(t_tree **root);
int				exec_redirections(t_redirect *redlst, t_helper *helper);
int				redirect_all(t_tree *root, t_helper *helper, t_tree **rt);
void			free_redirect_list(t_redirect **redlst);
char			*get_path_of_cpath(t_list *list);
int				no_file_no_dir(char *cmd);
int				get_len_path(char *path);
char			*check_path(char *path);
void			cleanup(t_helper *helper, t_tree **rt);
int				cd_home_not_set(void);
void			addred_front(t_redirect **lst, t_redirect *new);
int				open_fd(char *file, int type);
int				open_files(char *file, int type);
int				duplicate_fd(int fd, int duped_fd, char *file);
int				execute_parenthesis(t_tree *root, t_helper *helper,
					t_tree **rt);
#endif
