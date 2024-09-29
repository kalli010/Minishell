#include <minishell.h>


int ft_unset(t_list *list,t_helper *helper)
{
	char **env;
	
	g_exit_status = 1;
	env = helper->envp;
	if(list->back == NULL && list->next->next == NULL)
		helper->envp = unset(helper->envp, list->next->content);
	else
		return(g_exit_status);
	if (helper->envp == NULL)
	{
		helper->envp = env;
		return (g_exit_status);
	}
	return(EXIT_SUCCESS);
}