#include <minishell.h>


int ft_unset(t_list *list,t_helper *helper)
{
	g_helper.exit_status = 0;
	unset(&helper->envp, list->next);
	unset(&helper->xenv, list->next);
	return(g_helper.exit_status);
}
