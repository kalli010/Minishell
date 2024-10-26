/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:47:38 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/26 12:27:36 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_and_open_file(t_open_file *of, char *redfile, t_list *delimiter)
{
	if (!check_quotes(delimiter->content))
		of->i = 1;
	remove_quotes_string(delimiter->content);
	of->fd = open(redfile, O_CREAT | O_WRONLY, 0644);
	g_helper.fd = of->fd;
	if (of->fd < 0)
	{
		printf("Error creating redfile\n");
		return (1);
	}
	return (0);
}

int	write_to_file(t_open_file *of, t_list *delimiter)
{
	if (!of->line)
	{
		printf("Error: (Ctrl+D)\n");
		return (1);
	}
	if (delimiter->content[0] == '\0')
	{
		if (of->line[0] == '\0')
			return (1);
	}
	else if (!ft_strncmp(of->line, delimiter->content, \
				ft_strlen(delimiter->content)) \
			&& ft_strlen(of->line) == ft_strlen(delimiter->content))
		return (1);
	return (0);
}

void	free_line(t_open_file *of, t_heredoc *hd)
{
	free(of->line);
	close(of->fd);
	free_list(*hd->list);
	of->i = -1;
	while ((*hd->rf)[++of->i])
		free((*hd->rf)[of->i]);
	free(*hd->rf);
	clean_env(hd->env);
	clean_env(hd->xenv);
}

int	read_line(t_open_file *of, t_list *delimiter)
{
	of->line = readline("> ");
	if (write_to_file(of, delimiter))
		return (1);
	return (0);
}

void	heredoc_child_process(t_open_file *of, t_heredoc *hd)
{
	signal(SIGINT, sigint_handler);
	while (1)
	{
		if (read_line(of, hd->delimiter))
			break ;
		if (of->i == 1)
		{
			of->d = check_d(of->line, -1);
			while (of->line[of->d])
			{
				if (expand_line(hd->env, &of->line, of->d))
				{
					free_line(of, hd);
					exit(1);
				}
				else
					of->d = check_d(of->line, of->d);
			}
		}
		write(of->fd, of->line, ft_strlen(of->line));
		write(of->fd, "\n", 1);
		free(of->line);
	}
	free_line(of, hd);
	exit(0);
}
