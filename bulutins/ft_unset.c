#include <minishell.h>


int ft_unset(t_list *list,t_helper *helper)
{
	char **env;

	env = helper->envp;
	if(list->back == NULL && list->next->next == NULL)
		helper->envp = unset(helper->envp, list->next->content);
	else
		return(1);
	if (helper->envp == NULL)
	{
		helper->envp = env;
		return (1);
	}
	return(0);
}