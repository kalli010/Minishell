/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpe_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:55:57 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/08/29 23:27:49 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	parser_error_status(void)
{
	ft_putstr_fd("syntax error near unexpected `\n' \n", 2);
	exit(EXIT_PARSER);
}
