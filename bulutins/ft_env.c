/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 06:05:05 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/11/04 22:56:29 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_env(t_list *list, char **env)
{
	int	i;

	(void)list;
	i = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
		{
			ft_putstr_fd(env[i], STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		i++;
	}
	return (g_helper.exit_status = 0, 0);
}
