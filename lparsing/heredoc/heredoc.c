/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:50:48 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/19 21:39:08 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	sigint_handler(int sig)
{
	int	i;

	if (sig == SIGINT)
	{
		close(g_helper.fd);
		free_list(g_helper.list);
		if (g_helper.redfile)
		{
			i = -1;
			while (g_helper.redfile[++i])
				free(g_helper.redfile[i]);
			free(g_helper.redfile);
		}
		if (*g_helper.envp != NULL)
			clean_env(g_helper.envp);
		if (*g_helper.xenv != NULL)
			clean_env(g_helper.xenv);
		exit(1);
	}
}

void	init_hd(t_heredoc *hd, t_list **list, char ***rf)
{
	hd->list = list;
	hd->rf = rf;
}

void	initialize_heredoc(t_heredoc *hd, int size)
{
	hd->delimiter = *hd->list;
	hd->i = -1;
	*hd->rf = (char **)malloc(sizeof(char *) * (size + 1));
	while (++hd->i < size)
	{
		(*hd->rf)[hd->i] = (char *)malloc(sizeof(char) * 16);
		(*hd->rf)[hd->i][0] = '\0';
		ft_cpy((*hd->rf)[hd->i], "/tmp/.redfile");
		hd->nbr = ft_itoa(hd->i);
		hd->j = 12;
		hd->n = -1;
		while (hd->nbr[++hd->n])
			(*hd->rf)[hd->i][++hd->j] = hd->nbr[hd->n];
		(*hd->rf)[hd->i][++hd->j] = '\0';
		free(hd->nbr);
	}
	(*hd->rf)[hd->i] = NULL;
}

int	heredoc(t_heredoc *hd, int size)
{
	initialize_heredoc(hd, size);
	hd->i = -1;
	while (hd->delimiter)
	{
		if (hd->delimiter->type == HEREDOC)
		{
			hd->delimiter = hd->delimiter->next;
			if (open_file((*hd->rf)[++hd->i], hd))
			{
				clean_heredoc(*hd->rf, 1);
				return (1);
			}
		}
		hd->delimiter = hd->delimiter->next;
	}
	implementing_heredoc(hd->list, hd->rf);
	return (0);
}
