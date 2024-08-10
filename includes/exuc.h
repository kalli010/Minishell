/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exuc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:45:11 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/08/10 03:38:48 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXUC_H
# define EXUC_H
#include <minishell.h>

char	*get_path(t_helper *help,t_list *list);
void	find_command(t_list *list,t_tree *root, t_helper *helper);
char	**get_options(t_helper *helper, t_list *list);
void	free_array(char **arr);
int		here_doc(t_list *list,t_helper *helper);
int		check_upper(char c);
int		check_if_uppercase(char *line);
char	*check_if_env(char *line);
int		ft_env(char **env);
int		ft_pwd(void);
void	execute_command(char *command,char **arg,char **env);




#endif