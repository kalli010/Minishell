#include <minishell.h>


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

int check_schar(t_list *list)
{
  if(list->type == PIPE || list->type == OR \
    || list->type == AND || list->type == OUTPUT \
    || list->type == HEREDOC || list->type == INPUT \
    || list->type == APPEND)
    return(1);
  return(0);
}

int check_var(t_list *list, char ***env, char ***xenv)
{
  int i;

  g_helper.exit_status = 0;
  i = 0;
  while(list)
  {
    if(((list->back != NULL && !ft_strncmp(list->back->content, "export", 6) \
      && list->back->content[6] == '\0' ) || i == 1) && !check_schar(list))
    {
      i = 1;
      if(set_var(list, env, xenv))
      {
        printf("not a valid identifier\n");
        g_helper.exit_status = 1;
      }
    }
    else if(check_schar(list))
      i = 0;
    list = list->next;
  }
  return(g_helper.exit_status);
}

void remove_quotes(t_list *list)
{
  int j;
  char q;
  int q_n;

  if(list == NULL)
    return;
  while(list)
  {
    q_n = count_quotes(list->content);
    j = -1;
    while(list->content[++j] && q_n != 0)
    {
      if(list->content[j] == '"' || list->content[j] == '\'')
      {
        q = list->content[j];
        list->content[j] = list->content[j + 1];
        while(list->content[j + 1] != q)
        {
          list->content[j] = list->content[j + 1];
          j++;
        }
        j++;
        while(list->content[++j])
          list->content[j - 2] = list->content[j];
        list->content[j - 2] = '\0';
        q_n--;
        j = -1;
      }
    }
    list = list->next;
  }
}