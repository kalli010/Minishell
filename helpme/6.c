#include <minishell.h>


void remove_quotes_string(char *str)
{
  int j;
  int q_n;
  char q;

  j = -1;
  if(str == NULL)
    return;
  q_n = count_quotes(str);
  while(str[++j] && q_n != 0)
  {
    if(str[j] == '"' || str[j] == '\'')
    {
      q = str[j];
      if(str[j + 1] == q)
        return;
      str[j] = str[j + 1];
      while(str[j + 1])
      {
        if(str[j + 1] == q)
          break;
        str[j] = str[j + 1];
        j++;
      }
      j++;
      if(str[j] == '\0')
      {
        str[j - 1] = '\0';
        return;
      }
      while(str[++j])
        str[j - 2] = str[j];
      str[j - 2] = '\0';
      q_n--;
      j = -1;
    }
  }
}

int var_split(char *str, char ***array)
{
  char **list;
  int i;
  int c;
  int end;

  end = 0;
  remove_quotes_string(str);
  c = count_words(str);
  list = (char **)malloc(sizeof(char *) * (c + 1));
  if(list == NULL)
    return(1);
  i = 0;
  c = 0;
  while(str[i])
  {
    get_words(&i, &end, str);
    if(str[i] == '\0')
      break;
    list[c++] = ft_substr(str, i, end - i);
    if(list[c - 1] == NULL)
    {
      i = -1;
      while(++i < c - 1)
        free(list[i]);
      free(list);
      return(1);
    }
    i = end;
  }
  list[c] = NULL;
  *array = list;
  return(0);
}

int var_quotes(char **env, t_list **list, int d)
{
  char **array;
  t_list *n_list;
  t_list *tmp;
  t_list *back;
  int i;

  n_list = NULL;
  i = var_dquotes(env, list, d);
  if(i == 1)
    return(1);
  else if(i == 2)
    return(2);
  if((*list)->content[0] != '\0')
  {
    if(var_split((*list)->content, &array))
      return(2);
    if(creat_linked_list(&n_list, array))
    {
      free(array);
      return(2);
    }
    free(array);
    tmp = (*list)->next;
    back = (*list)->back;
    if((*list)->back != NULL)
      (*list)->back->next = NULL;
    free((*list)->content);
    free((*list));
    if(back != NULL)
    {
      (*list) = back;
      ft_lstadd_back(list, n_list);
      *list = (*list)->next;
    }
    else {
      (*list) = n_list;
    }
    ft_lstadd_back(list, tmp);
  }
  return(0);
}

int expander(char **env, t_list **list, int d)
{
  int i;
  int status;

  i = d;
  while(--d >= 0)
  {
    if((*list)->content[d] == '"')
    {
      while(--d >= 0 && (*list)->content[d] != '"');
      if(d < 0)
      {
        status = var_dquotes(env, list, i);
        if(status == 1)
          return(1);
        else if(status == 2)
          return(2);
        return(0);
      }
    }
  }
  status = var_quotes(env, list, i);
  if(status == 1)
    return(1);
  else if(status == 2)
    return(2);
  return(0);
}

int check_d(char *str, int i)
{
  while(str[++i])
  {
    if(str[i + 1] && str[i] == '$' && str[i + 1] != '$')
      return(i);
  }
  return(i);
}

int check_squotes(char *str, int i)
{
  while(--i >= 0)
  {
    if(str[i] == '\'')
    {
      while(str[--i] != '\'' && i >= 0);
      if(i < 0)
        return(0);
      else
        return(1);
    }
    else if(str[i] == '"')
        return(1);
  }
  return(1);
}