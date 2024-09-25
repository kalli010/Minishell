/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 23:46:23 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/09/24 22:48:07 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// static int is_directory(const char *dirc)
// {
//     struct stat dir;
//     if (stat(dirc,&dir) != 0)
//         return (0);
//     return (S_ISDIR(dir.st_mode));
// }
// static void  update_pwd(char *old,char *curr)
// {
//     char  *old_pwd;
//     char *curr_pwd;

//     old_pwd = ft_strjoin("OLDPWD=", old);
//     curr_pwd = ft_strjoin("PWD=",curr);
    
    
// }

static int	cd_errors(void)
{
	write(2, "minishell : cd : too many arguments\n", 37);
	return (EXIT_FAILURE);
}

int ft_cd(t_list *list, t_helper *helper)
{
    char *go_path;
    char *current_dir;
    char *new_dir;
    printf("hello from cd \n");
    current_dir = getcwd(NULL, 0);
    if (!list)
        return (EXIT_FAILURE);
    
    if (count_arg(list) != 1 && count_arg(list) != 0)
        return cd_errors();

    list = list->next;
    if (!list)
    {
        go_path = ft_getenv(helper->envp, "HOME");
        if (!go_path)
            return (EXIT_FAILURE); 
    }
    else

        go_path = ft_strdup(list->content); 
    if (chdir(go_path) != 0)
    {
        write(2, "minishell: cd: ", 15);
        perror(go_path); 
        write(2, "\n", 1);
        free(go_path);
        free(current_dir);
        return (EXIT_FAILURE);
    }
    new_dir = getcwd(NULL, 0); 
    // update_pwd(current_dir, new_dir, helper);

    free(current_dir);
    free(new_dir);
    free(go_path);
    return (EXIT_SUCCESS);
}


