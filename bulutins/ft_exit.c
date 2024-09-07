/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 04:57:51 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/09/07 08:08:19 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_all_isdigit(char *data)
{
	int	i;

	i = 0;
	while (data[i])
	{
		if (!ft_isdigit(data[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	exit_errors(int status)
{
	if (status == 1)
	{
		write(2, "minishell : exit: too many arguments\n", 38);
		return (EXIT_FAILURE);
	}
	else
	{
		write(2, "minishell : exit numeric argument required", 43);
		exit(EXIT_FAILURE);
	}
}

unsigned char	ft_exit(t_tree *root, t_helper *helper)
{
	unsigned char status;

	status =  g_exit;
	printf("exit\n");
	if (count_arg(root->content) > 1)
		return (exit_errors(1));
	if (root->content->next && root->content->next->content)
    {
        if (!ft_all_isdigit(root->content->next->content))
            return (exit_errors(0));
        status = ft_atoi(root->content->next->content);
    }
	free_list(root->content);
	my_free(helper);
	exit(status);
}
