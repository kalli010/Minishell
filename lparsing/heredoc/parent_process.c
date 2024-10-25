/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:47:59 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/25 13:26:41 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	fork_failes(t_open_file *of)
{
	printf("Fork failed");
	close(of->fd);
	return (1);
}

int	open_file(char *redfile, t_heredoc *hd)
{
	t_open_file	of;

	of.i = 0;
	of.d = -1;
	if (check_and_open_file(&of, redfile, hd->delimiter))
		return (1);
	of.pid = fork();
	if (of.pid == -1)
		return (fork_failes(&of));
	else if (of.pid == 0)
		heredoc_child_process(&of, hd);
	else
	{
		waitpid(of.pid, &of.status, 0);
		if (WIFSIGNALED(of.status) && WTERMSIG(of.status) == SIGINT)
		{
			printf("^C\n");
			close(of.fd);
			return (1);
		}
	}
	close(of.fd);
	return (0);
}

int	update_list_with_redirection(\
		t_imp_hc *imh, t_list **list, char ***redfile, int i)
{
	if (imh->back != NULL)
		imh->back->next = NULL;
	imh->red = (char *)malloc(sizeof(char) * 2);
	if (imh->red == NULL)
		return (1);
	imh->red[0] = '<';
	imh->red[1] = '\0';
	ft_lstadd_back(&imh->back, ft_lstnew(imh->red));
	if (imh->back->next != NULL)
		imh->back = imh->back->next;
	imh->back->type = INPUT;
	ft_lstadd_back(&imh->back, ft_lstnew((*redfile)[i]));
	imh->back = imh->back->next;
	imh->back->type = PATH;
	if (imh->back != NULL)
		imh->back->next = *list;
	if (*list != NULL)
		(*list)->back = imh->back;
	else
		*list = imh->back;
	if (*list != NULL && (*list)->back != NULL)
		*list = (*list)->back;
	return (0);
}

int	process_heredoc_node(t_list **list, t_imp_hc *imh, char ***redfile, int *i)
{
	if ((*list)->type == HEREDOC)
	{
		imh->back = (*list)->back;
		imh->next = (*list)->next->next;
		(*i)++;
		while (*list != imh->next)
		{
			imh->tmp = *list;
			*list = (*list)->next;
			if (imh->tmp->content)
				free(imh->tmp->content);
			free(imh->tmp);
		}
		if (update_list_with_redirection(imh, list, redfile, *i))
			return (1);
	}
	return (0);
}

int	implementing_heredoc(t_list **list, char ***redfile)
{
	t_imp_hc	imh;
	int			i;

	imh.red = NULL;
	i = -1;
	imh.next = NULL;
	while (*list)
	{
		if ((*list)->type == HEREDOC)
		{
			if (process_heredoc_node(list, &imh, redfile, &i))
				return (1);
		}
		if (*list && (*list)->next == NULL)
			break ;
		if (*list != NULL)
			*list = (*list)->next;
	}
	while (*list && (*list)->back)
		*list = (*list)->back;
	return (0);
}
