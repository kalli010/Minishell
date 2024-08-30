/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 05:57:52 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/08/26 06:09:26 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_builtins(t_list *list, t_helper *helper)
{
	if (!ft_strncmp("echo", list->content, sizeof("echo")))
		return (ft_echo(list));
	else if (!ft_strncmp("cd", list->content, sizeof("cd")))
		return (ft_cd(list));
	else if (!ft_strncmp("export", list->content, sizeof("export")))
		return (ft_export(list));
	else if (!ft_strncmp("env", list->content, sizeof("env")))
		return (ft_env(helper->envp));
	else if (!ft_strncmp("pwd", list->content, sizeof("pwd")))
		return (ft_pwd(list));
	else if (!ft_strncmp("unset", list->content, sizeof("unset")))
		return (ft_unset(list));
	else if (!ft_strncmp("exit", list->content, sizeof("exit")))
		return (ft_unset(list));
	else
		return (EXIT_FAILURE);
}
