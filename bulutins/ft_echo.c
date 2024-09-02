/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:44:38 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/09/02 01:53:38 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_option(char *str)
{
	int	i;

	if (!ft_strncmp(str, "-n", 2))
	{
		i = 2;
		while (str[i] == 'n')
			i++;
		if (str[i] == '\0')
			return (true);
	}
	return (false);
}

void	print_arg(char **arg, int start)
{
	int	i;

	i = start;
	while (arg[i])
	{
		ft_putstr_fd(arg[i], STDOUT_FILENO);
		if (arg[i + 1])
			ft_putchar_fd('a', STDOUT_FILENO);
		i++;
	}
}

int	execute_echo(char **arg)
{
	int	check_n;
	int	start;
	int	j;

	check_n = false;
	start = 1;
	if (arg[1] != NULL)
	{
		j = 1;
		while (arg[j] != NULL)
		{
			if (check_option(arg[j]) == true)
			{
				check_n = true;
				start++;
			}
			else
				break ;
			j++;
		}
		print_arg(arg, start);
	}
	if (check_n == false)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

int	ft_echo(t_list *list)
{
	int		i;
	int		count;
	char	**op;

	op = NULL;
	count = count_arg(list);
	if (!ft_strncmp("echo", list->content, sizeof("echo")))
	{
		op = (char **)malloc((count + 2) * sizeof(char *));
		if (!op)
			return (EXIT_FAILURE);
		op[0] = ft_strdup("echo");
		list = list->next;
		i = 1;
		while (list && list->type == OPTIONS)
		{
			op[i++] = ft_strdup(list->content);
			list = list->next;
		}
		op[i] = NULL;
		execute_echo(op);
		free_array(op);
	}
	return (EXIT_SUCCESS);
}
