#include <minishell.h>

int check_expander(char **env, t_list **list)
{
  t_list *tmp;
  int i;
  int status;

  tmp = NULL;
  i = -1;
  while(*list)
  {
    i = check_d((*list)->content, -1);
    while((*list)->content[i])
    {
      if(check_squotes((*list)->content, i))
      {
        status = expander(env, list, i);
        if(status == 1)
        {
          if((*list)->back != NULL)
            (*list)->back->i = 2;
          break;
        }
        else if(status == 2)
          return(1);
        //token_type(*list);
        if(*list)
          i = check_d((*list)->content, i - 1);
        else
          break;
      }
      else
        i = check_d((*list)->content, i);
    }
    tmp = *list;
    if(*list != NULL)
      (*list) = (*list)->next;
  }
  *list = tmp;
  if(*list != NULL)
    while((*list)->back != NULL)
      *list = (*list)->back;
  return(0);
}

void clean_linked_list(t_list **list)
{
  t_list *tmp;
  t_list *back;
  t_list *next;

  tmp = *list;
  while(tmp)
  {
    if(tmp->content[0] == '\0')
    {
      back = tmp->back;
      next = tmp->next;
      free(tmp->content);
      free(tmp);
      if(back == NULL)
        *list = next;
      else
        back->next = next;
      if(next != NULL)
        next->back = back;
      tmp = *list;
    }
    else
      tmp = tmp->next;
  }
}

int add_var(char **env_or_xenv, char *var, char *value, int index)
{
  char *new_var;

  new_var = (char *)malloc(sizeof(char) * (ft_strlen(var) + ft_strlen(value) + 2));
  if(new_var == NULL)
    return(1);
  new_var[0] = '\0';
  ft_cpy(new_var, var);
  if(value != NULL)
  {
    ft_cpy(new_var, "=");
    ft_cpy(new_var, value);
  }
  free(env_or_xenv[index]);
  env_or_xenv[index] = new_var;
  return(0);
}

char **add_new_env(char **env_or_xenv, int s, char *var, char *value, int check)
{
  char **new_env;
  int len;

  len = 0;
  if(check == 0)
  {
    new_env = (char **)malloc(sizeof(char *) * (s + 2));
    if(new_env == NULL)
      return(NULL);
  }
  else
  {
    if(value != NULL)
    {
      new_env = (char **)malloc(sizeof(char *) * (s + 2));
      if(new_env == NULL)
        return(NULL);
    }
    else
    {
      new_env = (char **)malloc(sizeof(char *) * (s + 1));
      if(new_env == NULL)
        return(NULL);
    }
  }
  while (env_or_xenv && env_or_xenv[len])
  {
    new_env[len] = ft_substr(env_or_xenv[len], 0, ft_strlen(env_or_xenv[len]));
    if(new_env[len] == NULL)
    {
      check = -1;
      while(++check < len)
        free(new_env[check]);
      while(env_or_xenv && env_or_xenv[len])
        free(env_or_xenv[len++]);
      free(new_env);
      return(NULL);
    }
    free(env_or_xenv[len]);
    len++;
  }
  new_env[len] = NULL;
  if(check == 1)
  {
    if(value != NULL)
    {
      if(add_var(new_env, var, value, len))
      {
        while(--len >= 0)
          free(new_env[len]);
        free(new_env);
        free(env_or_xenv);
        return(NULL);
      }
      new_env[++len] = NULL;
    }
  }
  else
  {
    if(add_var(new_env, var, value, len))
    {
      while(--len >= 0)
        free(new_env[len]);
      free(new_env);
      free(env_or_xenv);
      return(NULL);
    }
    new_env[++len] = NULL;
  }
  free(env_or_xenv);
  return new_env;
}

int check_content(char *str)
{
  int i;
  
  i = 0;
  while(str[++i])
  {
    if(!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_')
      return(1);
  }
  return(0);
}