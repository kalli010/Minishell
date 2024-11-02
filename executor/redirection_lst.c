/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 20:07:14 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/21 01:17:00 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_redirect	*newred(int type, int flag, char *content)
{
	t_redirect	*file;

	file = malloc(sizeof(t_redirect));
	if (file == NULL)
		return (NULL);
	file->filename = ft_strdup(content);
	file->type = type;
	file->flag = flag;
	file->next = NULL;
	return (file);
}

t_redirect	*create_redirect(t_tree **root)
{
	t_redirect	*tmp;
	char		*file;

	tmp = NULL;
	if ((*root)->first_child->next_sibling == NULL)
		file = (*root)->first_child->content->content;
	else
		file = (*root)->first_child->next_sibling->content->content;
	tmp = newred((*root)->content->type, (*root)->content->i, file);
	if (tmp == NULL)
		return (NULL);
	return (tmp);
}

t_redirect	*init_redirect_lst(t_tree **root)
{
	t_redirect	*redlst;
	t_redirect	*tmp;

	redlst = NULL;
	while ((*root) && ((*root)->content->type == OUTPUT
			|| (*root)->content->type == INPUT
			|| (*root)->content->type == APPEND))
	{
		tmp = create_redirect(root);
		if (tmp == NULL)
		{
			free_redirect_list(&redlst);
			return (NULL);
		}
		addred_front(&redlst, tmp);
		*root = (*root)->first_child;
	}
	return (redlst);
}

int	check_file(int type, char *file, int flag)
{
	if (type == INPUT)
	{
		if (flag == 2)
			return (errors(file, 2, 0), g_helper.exit_status);
		if (check_existence(file, 1) || check_read(file))
		{
			return (g_helper.exit_status = 1, 1);
		}
	}
	else if (type == OUTPUT || type == APPEND)
	{
		if (flag == 2)
			return (errors(file, 2, 0), g_helper.exit_status);
		if (!check_existence(file, 0) && check_write_and_dir(file))
		{
			return (g_helper.exit_status = 1, 1);
		}
	}
	return (EXIT_SUCCESS);
}

int	exec_redirections(t_redirect *redlst, t_helper *helper)
{
	int	status;

	(void)helper;
	while (redlst)
	{
		status = check_file(redlst->type, redlst->filename, redlst->flag);
		if (status != EXIT_SUCCESS)
			return (g_helper.exit_status = 1, 1);
		status = open_fd(redlst->filename, redlst->type);
		if (status != EXIT_SUCCESS)
			return (g_helper.exit_status = 1, 1);
		redlst = redlst->next;
	}
	return (EXIT_SUCCESS);
}
