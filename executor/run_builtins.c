/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 05:57:52 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/15 17:48:12 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_builtins(t_tree *root)
{
	if (!ft_strncmp("echo", root->content->content, sizeof("echo")))
		return (true);
	else if (!ft_strncmp("cd", root->content->content, sizeof("cd")))
		return (true);
	else if (!ft_strncmp("export", root->content->content, sizeof("export")))
		return (true);
	else if (!ft_strncmp("env", root->content->content, sizeof("env")))
		return (true);
	else if (!ft_strncmp("pwd", root->content->content, sizeof("pwd")))
		return (true);
	else if (!ft_strncmp("unset", root->content->content, sizeof("unset")))
		return (true);
	else if (!ft_strncmp("exit", root->content->content, sizeof("exit")))
		return (true);
	else
		return (false);
}

int	run_builtins(t_tree *root, t_helper *helper)
{
	if (!ft_strncmp("echo", root->content->content, sizeof("echo")))
		return (ft_echo(root->content));
	else if (!ft_strncmp("cd", root->content->content, sizeof("cd")))
		return (ft_cd(root->content, helper));
	else if (!ft_strncmp("env", root->content->content, sizeof("env")))
		return (ft_env(root->content, helper->xenv));
	else if (!ft_strncmp("pwd", root->content->content, sizeof("pwd")))
		return (ft_pwd(helper));
	else if (!ft_strncmp("unset", root->content->content, sizeof("unset")))
		return (ft_unset(root->content, helper));
	else if (!ft_strncmp("export", root->content->content, sizeof("export")))
	{
		if (root->content->next && root->content->next->type == OPTIONS)
			return (check_var(root->content->next, &helper->envp,
					&helper->xenv));
		else
			return (export(helper->envp));
	}
	else if (!ft_strncmp("exit", root->content->content, sizeof("exit")))
		ft_exit(root, helper);
	return (EXIT_FAILURE);
}
