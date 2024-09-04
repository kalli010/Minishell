#include <minishell.h>


int ft_unset(t_list *list,t_helper *helper)
{
	if (!(helper->envp = unset(helper->envp, list->next->content)))
		return (0);
	return(1);
}