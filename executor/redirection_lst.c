/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 20:07:14 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/11 08:51:15 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_redirect	*newred(int type, int flag, char *content)
{
	t_redirect	*file;

	file = malloc(sizeof(t_redirect));
	if (file == NULL)
	{
		return (NULL);
	}
	file->filename = ft_strdup(content);
	file->type = type;
	file->flag = flag;
	file->next = NULL;
	return (file);
}

void	addred_front(t_redirect **lst, t_redirect *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}

t_redirect	*init_redirect_lst(t_tree **root)
{
    t_redirect	*redlst = NULL;
    t_redirect	*tmp;
    char		*file;

    while ((*root) && ((*root)->content->type == OUTPUT
            || (*root)->content->type == INPUT
            || (*root)->content->type == APPEND))
    {
      if((*root)->first_child->next_sibling && (*root)->first_child->next_sibling->content->type == PATH)
      {
        file = (*root)->first_child->next_sibling->content->content;
        tmp = newred((*root)->content->type, (*root)->content->i, file);
        if (tmp == NULL)
        {
			while (redlst)
            {
                tmp = redlst;
                redlst = redlst->next;
                free(tmp->filename);
                free(tmp);
            }
            return (NULL);
        }
        addred_front(&redlst, tmp);
      }
      *root = (*root)->first_child;
    }
    return (redlst);
}



int	check_file(int type, char *file, int flag)
{
	if (type == INPUT)
	{
		if (flag == 2)
			return (errors(file, 2, 0), g_exit_status);
		if (check_existence(file, 1) || check_read(file))
			return (g_exit_status);
	}
	else if (type == OUTPUT || type == APPEND)
	{
		if (flag == 2)
			return (errors(file, 2, 0), g_exit_status);
		if (!check_existence(file, 0) && check_write_and_dir(file))
			return (g_exit_status);
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
		if (status != 0)
			return (status);
		status = open_fd(redlst->filename, redlst->type);
		if (status != 0)
			return (status);
		redlst = redlst->next;
	}
	return (EXIT_SUCCESS);
}
