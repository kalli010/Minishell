#include <minishell.h>


int ft_unset(t_list *list,t_helper *helper)
{
	char **env;
	
	g_exit_status = 1;
	env = (*helper->envp);
	// if(list->back == NULL && list->next->next == NULL)
 	// {
	unset(helper->envp, list->next);
	unset(helper->xenv, list->next);
 	//  }
 	//  else
	return(g_exit_status);
	if ((*helper->envp) == NULL)
	{
		(*helper->envp) = env;
		return (g_exit_status);
	}
	return(EXIT_SUCCESS);
}
