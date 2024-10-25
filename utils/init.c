/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:51:18 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/25 14:51:19 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_helper(void)
{
	g_helper.envp = NULL;
	g_helper.xenv = NULL;
	g_helper.exit_status = 0;
	g_helper.root = NULL;
	g_helper.redfile = NULL;
	g_helper.list = NULL;
}

void	init_helper_2(void)
{
	g_helper.root = NULL;
	g_helper.redfile = NULL;
	g_helper.list = NULL;
}
