/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 23:46:23 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/09/02 04:17:59 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	cd_erros(void)
{
	write(2, "minishell : cd : too many arguments\n", 37);
	return (EXIT_FAILURE);
}
int	ft_cd(t_list *list)
{
	if (count_arg(list) > 1)
		return (cd_erros());
	return (EXIT_SUCCESS);
}
