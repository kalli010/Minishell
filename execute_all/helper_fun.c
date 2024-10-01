/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_fun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 06:16:39 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/01 05:48:42 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_file(const char *file)
{
	struct stat	buf;

	if (stat(file, &buf) == 0)
	{
		if (access(file, X_OK) != 0)
		{
			write(2, "minishell: ", 11);
			write(2, file, ft_strlen(file));
			write(2, ": Permission denied\n", 20);
			g_exit_status = 126;
			return (g_exit_status);
		}
	}
	return (EXIT_SUCCESS);
}

void	my_free(t_helper *helper)
{
	if (helper)
	{
		free(helper->cmd);
		helper->cmd = NULL;
		free_array(helper->option);
		helper->option = NULL;
		free(helper);
	}
}

int	check_upper(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (arr == NULL)
		return ;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	count_arg(t_list *list)
{
	t_list	*temp_list;
	int		count;

	count = 0;
	temp_list = list;
	temp_list = temp_list->next;
	while (temp_list && temp_list->type == OPTIONS)
	{
		count++;
		temp_list = temp_list->next;
	}
	return (count);
}
