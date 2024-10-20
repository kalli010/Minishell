/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 23:46:23 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/20 23:19:51 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	cd_errors(void)
{
	g_helper.exit_status = 1;
	write(2, M_SHELL, 23);
	write(2, "cd : too many arguments\n", 25);
	return (g_helper.exit_status);
}

static void	update_pwd(char *old, char *curr, t_helper *helper)
{
	char	*old_pwd;
	char	*curr_pwd;
	t_list	oldpwd_node;
	t_list	currpwd_node;

	old_pwd = ft_strjoin("OLDPWD=", old);
	curr_pwd = ft_strjoin("PWD=", curr);
	oldpwd_node.content = old_pwd;
	oldpwd_node.next = NULL;
	currpwd_node.content = curr_pwd;
	currpwd_node.next = NULL;
	set_var(&oldpwd_node, &helper->envp, &helper->xenv);
	set_var(&currpwd_node, &helper->envp, &helper->xenv);
	free(old_pwd);
	free(curr_pwd);
}

int	change_directory(char *go_path)
{
	struct stat	path_stat;

	if (!stat(go_path, &path_stat) && !S_ISDIR(path_stat.st_mode))
	{
		handle_cd_error(go_path, 3);
		g_helper.exit_status = 1;
		return (g_helper.exit_status);
	}
	if (!S_ISDIR(path_stat.st_mode))
	{
		handle_cd_error(go_path, 1);
		g_helper.exit_status = 1;
		return (g_helper.exit_status);
	}
	if (chdir(go_path) != 0)
	{	
		handle_cd_error(go_path, 2);
		g_helper.exit_status = 1;
		return (g_helper.exit_status);
	}
	return (g_helper.exit_status);
}

char	*cd_path(t_list *list, t_helper *helper)
{
	char	*home_path;
	char	*go_path;

	if (count_arg(list) == 0)
	{
		home_path = ft_getenv(helper->envp, "HOME", -1);
		if (!home_path)
		{
			cd_home_not_set();
			return (NULL);
		}
		go_path = ft_strdup(home_path);
		free(home_path); 
	}
	else
	{
		go_path = get_target_path(list, helper);
		if (!go_path)
		{
			g_helper.exit_status = 1;
			return (NULL);
		}
	}
	return (go_path);
}

int	ft_cd(t_list *list, t_helper *helper)
{
	char	*old_pwd;
	char	*curr_pwd;
	char	*go_path;
	
	if (!list)
		return (g_helper.exit_status = 1, 1);
	if (count_arg(list) != 1 && count_arg(list) != 0)
		return (cd_errors());
	go_path = cd_path(list, helper);
	if (!go_path)
		return (g_helper.exit_status = 1, 1);
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (free(go_path), g_helper.exit_status = 1, 1);
	if (change_directory(go_path) == 0)
	{
		curr_pwd = getcwd(NULL, 0);
		if (curr_pwd)
		{
			update_pwd(old_pwd, curr_pwd, helper);
			free(curr_pwd);
		}
	}
	(free(old_pwd), free(go_path));
	return (g_helper.exit_status = 0, 0);
}
