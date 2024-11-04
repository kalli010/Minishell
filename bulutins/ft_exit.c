/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 04:57:51 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/11/04 22:58:48 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_all_isdigit(char *data)
{
	int	i;

	i = 0;
	while (data[i] == ' ' || (data[i] >= 9 && data[i] <= 13))
		i++;
	if (data[i] == '\0')
		return (0);
	if (data[i] == '-')
		i++;
	while (data[i])
	{
		if (data[i] == ' ' || (data[i] >= 9 && data[i] <= 13))
		{
			while (data[i] == ' ' || (data[i] >= 9 && data[i] <= 13))
				i++;
			if (data[i] != '\0')
				return (0);
			return (1);
		}
		if (!ft_isdigit(data[i]))
			return (0);
		if (data[i] != '\0')
			i++;
	}
	return (1);
}

static void	exit_errors(int status, char *arg)
{
	if (status == 1)
	{
		write(2, M_SHELL, 23);
		write(2, "exit: too many arguments\n", 26);
	}
	else if (status == 2)
	{
		write(2, M_SHELL, 23);
		write(2, "exit: ", 6);
		write(2, arg, ft_strlen(arg));
		write(2, ": numeric argument required\n", 29);
	}
}

unsigned char	ft_exit(t_tree *root, t_helper *helper)
{
	int		status;
	char	*arg;

	status = g_helper.exit_status;
	arg = NULL;
	printf("exit\n");
	if (root->content->next)
	{
		arg = root->content->next->content;
		if (!ft_all_isdigit(arg))
		{
			exit_errors(2, arg);
			cleanup(helper, &root);
			exit(g_helper.exit_status = 2);
		}
		if (count_arg(root->content) > 1)
		{
			exit_errors(1, NULL);
			return (g_helper.exit_status = 1);
		}
		status = ft_atoi(arg);
	}
	cleanup(helper, &root);
	exit((unsigned char)status);
}
