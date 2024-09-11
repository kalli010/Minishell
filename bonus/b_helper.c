/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_helper.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:10:42 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/09/10 16:12:00 by ayel-mou         ###   ########.fr       */
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
# include <sys/types.h>
# include <dirent.h>

static int count_wild(void)
{
    struct dirent *entry;
    int count;
    DIR *dirc;
    char *cur_dir;

    count = 0;
    cur_dir = getcwd(NULL, 0);
    if (!cur_dir)
        return (0);
    dirc = opendir(cur_dir); 
    if (!dirc)
    {
        free(cur_dir);
        return (0);
    }
    entry = readdir(dirc);
    while (entry != NULL)
    {
        count++;
        entry = readdir(dirc);
    }
    closedir(dirc);
    free(cur_dir);
    return count;
}

char **get_all(const char *cur_dir)
{
    struct dirent *entry;
    int count;
    DIR *dirc;
    char **wild;
    int i;
    
    i = -1;
    count = count_wild();
    if (!count)
        return NULL;
    dirc = opendir(cur_dir); 
    wild = (char **)malloc(sizeof(char *) * (count + 1));
    if (!wild)
        return (closedir(dirc),NULL);
    entry = readdir(dirc);
    while (entry != NULL)
    {
        wild[++i] = ft_strdup(entry->d_name);
        entry = readdir(dirc);
    }
    wild[count] = NULL;
    closedir(dirc);
    return wild;
}
