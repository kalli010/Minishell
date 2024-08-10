/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 03:26:42 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/08/10 03:37:41 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void execute_command(char *command,char **arg,char **env)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		if (execve(command, arg,env) == -1)
		{
			perror("error on execve :");
			exit(EXIT_FAILURE);
		}
		
	}
	else
		wait(NULL);

}