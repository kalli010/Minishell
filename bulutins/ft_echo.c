/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:44:38 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/15 17:51:51 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	count_arg_echo(t_list *list)
{
	t_list	*temp_list;
	int		count;

	count = 0;
	temp_list = list;
	temp_list = temp_list->next;
	while (temp_list && (temp_list->type == OPTIONS))
	{
		count++;
		temp_list = temp_list->next;
	}
	return (count);
} 
static int	check_option(char *str)
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

static void	print_arg(char **arg, int start)
{
	int	i;

	i = start;
	while (arg[i])
	{
		ft_putstr_fd(arg[i], STDOUT_FILENO);
		if (arg[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
}

static int	execute_echo(char **arg)
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
	
	g_helper.exit_status = 0;
	op = NULL;
	count = count_arg_echo(list);
	if (!ft_strncmp("echo", list->content, sizeof("echo")))
	{
		op = (char **)malloc((count + 2) * sizeof(char *));
		if (!op)
			return (g_helper.exit_status);
		op[0] = ft_strdup("echo");
		list = list->next;
		i = 1;
		while (list && (list->type == OPTIONS || list->type == COMMAND))
		{
			op[i++] = ft_strdup(list->content);
			list = list->next;
		}
		op[i] = NULL;
		execute_echo(op);
		free_array(op);
	}
	return (g_helper.exit_status = 0,0);
}
