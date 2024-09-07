/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_sig.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 02:21:52 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/09/07 08:06:26 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


void ctr_c(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("",0);
		printf("\n");
		rl_redisplay();
	}
}

void run_time(pid_t pid)
{
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
	}
}


void signals()
{
	signal(SIGINT,ctr_c);
	signal(SIGQUIT,SIG_IGN);
}