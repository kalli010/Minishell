#include <minishell.h>

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

int set_var(t_list *list, char ***env, char ***xenv)
{
  char *var;
  char *value;
  int len;
  int s;

  len = 0;
  s = 0;
  while (list->content[len] && list->content[len] != '=')
    len++;
  var = ft_substr(list->content, 0, len);
  if(var == NULL)
    return(1);
  remove_quotes_string(var);
  if((!ft_isalpha(var[0]) && var[0] != '_' ) || check_content(var))
  {
    free(var);
    return(1);
  }
  if (list->content[len] != '\0')
  {
    if(list->content[len - 1] == ' ')
      return(1);
    len++;
  }
  s = len;
  while (list->content[len])
    len++;
  value = ft_substr(list->content, s, len - s);
  remove_quotes_string(value);
  s = 0;
  while (*env != NULL && (*env)[s] != NULL)
  {
    if (!ft_strncmp((*env)[s], var, ft_strlen(var)) && ((*env)[s][ft_strlen(var)] == '=' || (*env)[s][ft_strlen(var)] == '\0'))
    {
      if(list->content[ft_strlen(var)] == '\0')
      {
        free(var);
        free(value);
        return(0);
      }
      if(add_var(*env, var, value, s))
      {
        free(var);
        free(value);
        return(1);
      }
      if(add_var(*xenv, var, value, s))
      {
        free(var);
        free(value);
        return(1);
      }
      free(var);
      free(value);
      return(0);
    }
    s++;
  }
  *env = add_new_env(*env, s, var, value, 0);
  *xenv = add_new_env(*xenv, s, var, value, 1);
  if(*env == NULL || *xenv == NULL)
  {
    free(var);
    free(value);
    return(1);
  }
  free(var);
  free(value);
  return(0);
}

int check_cmd_export(t_list *list)
{
  while(list)
  {
    if(list->type != OPTIONS)
      return(1);
    list = list->next;
  }
  return(0);
}

int check_var(t_list *list, char ***env, char ***xenv)
{
  g_helper.exit_status = 0;
  if(list->back && (list->back->back != NULL || check_cmd_export(list)))
    return(g_helper.exit_status);
  while(list)
  {
    if(set_var(list, env, xenv))
    {
      printf("not a valid identifier\n");
      g_helper.exit_status = 1;
    }
    list = list->next;
  }
  return(g_helper.exit_status);
}
