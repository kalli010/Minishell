/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 01:05:27 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/21 01:05:28 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_unset(t_list *list, t_helper *helper)
{
	g_helper.exit_status = 0;
	unset(&helper->envp, list->next);
	unset(&helper->xenv, list->next);
	return (g_helper.exit_status);
}
