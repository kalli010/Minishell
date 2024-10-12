/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_sig.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 02:21:52 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/03 01:28:51 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void check_signal(void)
{
	if (g_helper.exit_status == 131)
	{
		write(2, "Quit (core dumped)\n", \
				ft_strlen("Quit (core dumped)\n"));
	}
	if (g_helper.exit_status == 130)
		write(2,"\n",1);
}
void	ctr_c(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_handeler(int place)
{
	if (place == BEFORE)
	{
		signal(SIGINT, ctr_c);
		signal(SIGQUIT, SIG_IGN);
	}
	if (place == PARENT)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	if (place == CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	if (place == IN_HERE_DOC)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
	}
}
