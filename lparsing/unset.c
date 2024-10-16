#include <minishell.h>

int check_unset(char *str)
{
  int i;

  i = -1;
  while(str[++i])
  {
    if(str[i] == '=')
      return(1);
  }
  return(0);
}

int unset(char ***env, t_list *list)
{
  int s;
  int i;

  while(list && list->type == OPTIONS)
  {
    if(!check_unset(list->content))
    {
      s = 0;
      i = 0;
      while(**env != NULL && (*env)[s] != NULL)
      {
        if(!ft_strncmp((*env)[s], list->content, ft_strlen(list->content)) && ((*env)[s][ft_strlen(list->content)] == '=' || (*env)[s][ft_strlen(list->content)] == '\0' ))
        {
          free((*env)[s]);
          i = s;
          while((*env)[++s]);
          (*env)[i] = (*env)[s - 1];
          (*env)[s - 1] = NULL;
          break;
        }
        s++;
      }
    }
    list = list->next;
  }
  return(0);
}
