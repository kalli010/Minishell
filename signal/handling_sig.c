/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_sig.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 02:21:52 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/09/06 15:20:45 by ayel-mou         ###   ########.fr       */
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

void run_time(int sig)
{
	if (sig == SIGINT)
		signal(SIGINT, SIG_DFL);
}

void ctr_bslash(int sig)
{
	if (sig == SIGQUIT)
	{
		signal(SIGQUIT,SIG_IGN);
		
	}
}