/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 03:26:42 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/08/25 20:41:29 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	execute(t_tree *root, t_helper *helper)
{
	pid_t	pid;
	int		status;

	pid = fork();
	status = 0;
	helper->cmd = get_path(helper, root->content);
	helper->option = get_options(helper, root->content);
	if (!helper->cmd && !helper->option)
		return (free(helper->cmd), EXIT_FAILURE);
	if (pid == -1)
		return (perror("fork"), (EXIT_FAILURE));
	if (pid == 0)
		if (execve(helper->cmd, helper->option, helper->envp) == -1)
			return (perror("fork"), (EXIT_FAILURE));
	else
		waitpid(pid, &status, 0);
	free(helper->cmd);
	free_array(helper->option);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}
