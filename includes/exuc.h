/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exuc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:45:11 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/08/07 02:25:41 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXUC_H
# define EXUC_H
#include <minishell.h>

char	*get_path(t_helper *help,t_list *list);
void	find_command(t_list *list,t_tree *root, t_helper *helper);
char	**get_opetions(t_helper *helper, t_list *list);
void	free_array(char **arr);


#endif