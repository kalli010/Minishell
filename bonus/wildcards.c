/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 02:24:49 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/09/10 16:19:07 by ayel-mou         ###   ########.fr       */
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

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	len;

  if(s == NULL)
    return(NULL);
	len = strlen(s) + 1;
	dup = malloc(len);
	if (dup == NULL)
		return (NULL);
	memcpy(dup, s, len);
	return (dup);
}



    
char **get_wild(char *str)
{
    int count;

    count = 0;
    /*to do call strstr to get wildcards*/
    
}


char **wildcards(char *str)
{
    // struct dirent *entry;
    // DIR *dirc;
    char *cur_dir;
    char **wild;
    int i = 0;

    cur_dir = getcwd(NULL, 0);
    if (!strncmp(str, "*", strlen(str)))
    {
        wild = get_all(cur_dir);
        free(cur_dir);
        return (wild);
    }
    else
        get_wild(str);
    // if (!cur_dir)
    //     return NULL;
    
    // dirc = opendir(cur_dir); 
    // if (!dirc)
    // {
    //     perror("opendir");
    //     free(cur_dir);
    //     return NULL;
    // }


    // closedir(dirc); 
    // free(cur_dir);
    // return NULL;
    return (NULL);
}

int main()
{
    int i = 0;
    char **ar = wildcards("*");
    while (ar[i])
    {
        printf("%s\n", ar[i]);
        free(ar[i]); 
        i++;
    }
    free(ar); 

    return 0;
}
