/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 06:05:05 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/09/05 10:52:03 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_env(t_list *list,char **env)
{
	int	i;

	i = 0;
	if (count_arg(list) > 0)
	{
		write(1, "please enter env  with no options\n", 35);
		return (EXIT_FAILURE);
	}
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
