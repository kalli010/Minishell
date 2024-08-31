/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 02:24:49 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/08/30 04:35:09 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
#include <sys/types.h>
#include <dirent.h>


// int wildcards(t_tree *root,)
void wildcards()
{
    struct dirent *entry;
    DIR *dirc = opendir(".");
    
    if (dirc == NULL) {
        perror("opendir");
        return;
    }
    entry = readdir(dirc);
    while (entry != NULL)
    {
        printf("%s\n", entry->d_name);
		entry = readdir(dirc);
    }
    
    closedir(dirc); 
}

int main()
{
    wildcards();  
    return 0;
}