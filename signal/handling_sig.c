/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_sig.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 02:21:52 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/09/07 12:51:12 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


void ctr_c(int sig)
{
    if (sig == SIGINT)
    {
        if (g_helper->pid == -1)
        {
            rl_on_new_line();       
            rl_replace_line("", 0); 
            printf("\n");          
            rl_redisplay();
		}  
        else
            signal(SIGINT, SIG_DFL);
    }
}



void signals()
{
	signal(SIGINT,ctr_c);
	signal(SIGQUIT,SIG_IGN);
}