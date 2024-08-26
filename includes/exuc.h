/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exuc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:45:11 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/08/26 06:06:51 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXUC_H
# define EXUC_H
#include <minishell.h>
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
int		execute_command(char *command,char **arg,char **env);
int 	redirect_output(t_tree *root,t_helper *helper);
int		execute(t_tree *root, t_helper *helper);
int     count_arg(t_list *list);
int		redirect_input(t_tree *root, t_helper *helper);
int		execute_pipe(t_tree *root, t_helper *helper);
int 	ft_echo(t_list *list);







#endif
