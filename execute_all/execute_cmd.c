// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   execute_cmd.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/08/10 03:26:42 by ayel-mou          #+#    #+#             */
// /*   Updated: 2024/10/02 06:54:09 by ayel-mou         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include <minishell.h>

// // int	ft_isspace(char c)
// // {
// // 	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
// // 		|| c == '\r')
// // 		return (true);
// // 	return (false);
// // }


// // void	exit_path(char *s, int status, int flag)
// // {
// // 	if (status == ERROR_C && flag == 0)
// // 	{
// // 		write(2, "minishell: ", 11);
// // 		write(2, s, ft_strlen(s));
// // 		write(2, ": No such file or directory\n", 28);
// // 	}
// // 	else if (status == P_DNIED)
// // 	{
// // 		write(2, "minishell: ", 11);
// // 		write(2, s, ft_strlen(s));
// // 		write(2, ": Permission denied\n", 20);
// // 	}
// // 	else if (status == CMD_NOT_FOUND)
// // 	{
// // 		write(2, "minishell: ", 11);
// // 		write(2, s, ft_strlen(s));
// // 		write(2, ": command not found\n", 20);
// // 	}
// // 	else
// // 	{
// // 		write(2, "minishell: ", 11);
// // 		write(2, s, ft_strlen(s));
// // 		write(2, ": unknown error\n", 16);
// // 	}
// // }

// // static int	finish_status(pid_t pid)
// // {
// // 	int	status;

// // 	waitpid(pid, &status, 0);
// // 	if (WIFEXITED(status))
// // 	{
// // 		g_exit_status = WEXITSTATUS(status);
// // 		return (WEXITSTATUS(status));
// // 	}
// // 	else if (WIFSIGNALED(status))
// // 	{
// // 		g_exit_status = WTERMSIG(status) + 128;
// // 		if (WTERMSIG(status))
// // 		{
// // 			write(1, "\n", 1);
// // 			return (WTERMSIG(status) + 128);
// // 		}
// // 	}
// // 	return (EXIT_FAILURE);
// // }

// // int prepare_command(t_tree *root, t_helper *helper)
// // {
// // 	struct stat buf;

// // 	helper->cmd = get_path(helper, root->content);  // Get the command or full path
// // 	helper->option = get_options(helper, root->content);  // Parse options

// // 	// Command not found
// // 	if (!helper->cmd || helper->cmd[0] == '\0')
// // 	{
// // 		exit_path(root->content->content, CMD_NOT_FOUND, 1);  // "command not found"
// // 		g_exit_status = 127;
// // 		return (127);
// // 	}

// // 	// Check if it's a valid path (if it's not in PATH, or is relative/absolute path)
// // 	if (stat(helper->cmd, &buf) != 0)
// // 	{
// // 		exit_path(helper->cmd, ERROR_C, 0);  // "No such file or directory"
// // 		g_exit_status = 127;
// // 		return (127);
// // 	}

// // 	// If the command is a directory


// // 	// If it's not executable
// // 	if (access(helper->cmd, X_OK) != 0)
// // 	{
// // 		exit_path(helper->cmd, P_DNIED, 1);  // "Permission denied"
// // 		g_exit_status = 126;
// // 		return (126);
// // 	}

// // 	return (EXIT_SUCCESS);  // Command is valid
// // }

// // int	execute(t_tree *root, t_helper *helper)
// // {
// // 	pid_t	pid;

// // 	if (prepare_command(root, helper) != 0)
// // 		return (g_exit_status);

// // 	pid = fork();
// // 	if (pid == -1)
// // 	{
// // 		perror("fork");
// // 		return (EXIT_FAILURE);
// // 	}
// // 	if (pid == 0)
// // 	{
// // 		signal_handeler(CHILD);
// // 		if (execve(helper->cmd, helper->option, helper->envp) == -1)  // Execute command
// // 		{
// // 			perror("execve");  // If execve fails, print the error
// // 			exit(127);  // Exit with 127 if command execution fails
// // 		}
// // 	}
// // 	else  // Parent process
// // 	{
// // 		g_exit_status = finish_status(pid);  // Wait for child and get exit status
// // 	}
// // 	return (g_exit_status);
// // }



// // void exit_path(char *s, int status)
// // {
// //     struct stat buf;

// //     write(2, "minishell: ", 11);
// //     write(2, s, ft_strlen(s));
// //     if (status == P_DNIED && stat(s, &buf) == 0)
// //         write(2, ": Permission denied\n", 21);
// //     else if (status == ERROR_C || status == CMD_NOT_FOUND)
// //     {
// //         if ((s[0] == '/' || s[0] == '.') && stat(s, &buf) != 0)
// //             write(2, ": No such file or directory\n", 29);
//         els
// //             write(2, ": command not found\n", 20);
// //     }
// //     else if (S_ISDIR(buf.st_mode))
// //     {
// //         write(2, ": Is a directory\n", 18);
// //     }
// // }



// // static int finish_status(pid_t pid)
// // {
// //     int status;

// //     waitpid(pid, &status, 0);
// //     if (WIFEXITED(status))
// //     {
// //         g_exit_status = WEXITSTATUS(status);
// //         return (WEXITSTATUS(status));
// //     }
// //     else if (WIFSIGNALED(status))
// //     {
// //         g_exit_status = WTERMSIG(status) + 128;
// //         if (WTERMSIG(status))
// //         {
// //             write(1, "\n", 1);
// //             return (WTERMSIG(status) + 128);
// //         }
// //     }
// //     return (EXIT_FAILURE);
// // }

// // int prepare_command(t_tree *root, t_helper *helper)
// // {
// //     struct stat buf;

// //     char *cmd = root->content->content;

// //     if (stat(cmd, &buf) == 0) {
// //         if (S_ISDIR(buf.st_mode)) {
// //             exit_path(cmd, CMD_NOT_FOUND);
// //             return CMD_NOT_FOUND;
// //         }

// //         if (access(cmd, X_OK) != 0) {
// //             exit_path(cmd, P_DNIED);
// //             return P_DNIED;
// //         }
// //     } else {
// //         exit_path(cmd, ERROR_C);
// //         return ERROR_C;
// //     }
// //     helper->cmd = get_path(helper, root->content);
// //     helper->option = get_options(helper, root->content);
// //         if (!helper->cmd || helper->cmd[0] == '\0') {
// //         exit_path(cmd, CMD_NOT_FOUND);
// //         return CMD_NOT_FOUND;
// //     }
// //     if (stat(helper->cmd, &buf) == 0) {
// //         if (S_ISDIR(buf.st_mode)) {
// //             exit_path(helper->cmd, CMD_NOT_FOUND);
// //             return CMD_NOT_FOUND;
// //         }

// //         if (access(helper->cmd, X_OK) != 0) {
// //             exit_path(helper->cmd, P_DNIED);
// //             return P_DNIED;
// //         }
// //     } else {
// //         exit_path(helper->cmd, CMD_NOT_FOUND);
// //         return CMD_NOT_FOUND;
// //     }

// //     return EXIT_SUCCESS;
// // }



// // int execute(t_tree *root, t_helper *helper)
// // {
// //     int status;
// //     pid_t pid;

// //     // if (prepare_command(root, helper) != 0)

// //     pid = fork();
// //     if (pid == -1)
// //     {
// //         perror("fork");
// //         return (EXIT_FAILURE);
// //     }

// //     if (pid == 0)
// //     {
// //         signal_handeler(CHILD);
// //         execve(helper->cmd, helper->option, helper->envp);
// //         exit_path(helper->cmd, CMD_NOT_FOUND);
// //         exit(CMD_NOT_FOUND);
// //     }
// //     else 
// //     {
// //         status = finish_status(pid);
// //         g_exit_status = status;
// //     }
// //     return status;
// // }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 03:26:42 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/09/25 04:47:07 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void exit_path(char *s, int status)
{
	if (status == ERROR_C)
	{
		if (s[0] == '/')
		{
			write(2, s, ft_strlen(s));
			write(2, ": No such file or directory\n", 28);
			g_exit_status = 127;
		}
		else
		{
			write(2, s, ft_strlen(s));
			write(2, ": command not found\n", 20);
			g_exit_status = 127;
		}
	}
	else if (status == P_DNIED)
	{
		write(2, s, ft_strlen(s));
		write(2, ": permission denied\n", 20);
		g_exit_status = 126;
	}
}

static int finish_status(pid_t pid)
{
	int status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		g_exit_status = WEXITSTATUS(status);
		return (WEXITSTATUS(status));
	}
	else if (WIFSIGNALED(status))
	{
		g_exit_status = WTERMSIG(status) + 128;
		if (WTERMSIG(status))
		{
			write(1, "\n", 1);
			return (WTERMSIG(status) + 128);
		}
	}
	return (EXIT_FAILURE);
}

int prepare_command(t_tree *root, t_helper *helper)
{
	helper->cmd = get_path(helper, root->content);
	helper->option = get_options(helper, root->content);

	if (!helper->cmd)
	{
		exit_path(root->content->content, ERROR_C);
		g_exit_status = ERROR_C;
		return (ERROR_C);
	}
	return (EXIT_SUCCESS);
}

int execute(t_tree *root, t_helper *helper)
{
	int status;
	pid_t pid;

	if (prepare_command(root, helper) != 0)
		return (ERROR_C);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), EXIT_FAILURE);
	if (pid == 0)
	{
		signal_handeler(CHILD);
		execve(helper->cmd, helper->option, helper->envp);
		status = check_cmd(helper->cmd, root->content->content, helper->option);
		g_exit_status = status;
		exit(status);
	}
	else
	{
		status = finish_status(pid);
		g_exit_status = status;
	}
	return status;
}




