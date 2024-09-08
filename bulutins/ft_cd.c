/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 23:46:23 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/09/08 13:23:01 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char *get_dir(char *dir)
{
	char *path;
	
	if (!ft_strncmp(dir, "..", 2))
		path = ft_strdup("..");	
	if (!ft_strncmp(dir, "-", 2))
		path = ft_strdup(getenv("OLDPWD"));
	if (!ft_strncmp(dir, "~", 2))
		path = ft_strdup(getenv("HOME"));
	else
		path = ft_strdup(dir);
	return (path);
}

// static get_dir()
static int	cd_errors(void)
{
	write(2, "minishell : cd : too many arguments\n", 37);
	return (EXIT_FAILURE);
}

int	ft_cd(t_list *list)
{
    char *go_path;
    char *current_dir;

    current_dir = getcwd(NULL, 0);

    if (!list)
        return (EXIT_FAILURE);
    
    if (count_arg(list) != 1 && count_arg(list) != 0)
        return cd_errors();
    
    list = list->next;
    
    go_path = NULL;
    if (!list)
	{	
		chdir(getenv("HOME"));
		return(EXIT_SUCCESS);
	}
	else
		go_path = get_dir(list->content);
    if (chdir(go_path) != 0)
    {
        write(2, "minishell: cd: ", 15);
        perror("chdir");
        write(2, "\n", 1);
        free(current_dir);
        free(go_path);
        return (EXIT_FAILURE);
    }
    free(current_dir);
    free(go_path);
    return (EXIT_SUCCESS);
}


