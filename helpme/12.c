#include <minishell.h>


int export(char **env)
{
  int i = -1;
  char *var;
  char *value;
  
  while(env[++i])
  {
    if(get_var_value(env[i], &var, &value))
      return(1);
    printf("%s", var);
    if(value[0] != '\0')
      printf("=\"%s\"\n", value);
    else {
      printf("\n");
    }
    free(var);
    free(value);
  }
  return(0);
}

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

char *ft_strcpy(char *dest, const char *src)
{
  int i = 0;

  while (src[i] != '\0')
  {
    dest[i] = src[i];
    i++;
  }
  dest[i] = '\0';
  return dest;
}

double check_heredoc(t_list *list)
{
  double i;

  i = 0;
  while(list)
  {
    if(list->type == HEREDOC)
      i++;
    list = list->next;
  }
  return(i);
}