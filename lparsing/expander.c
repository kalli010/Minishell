#include <minishell.h>

void ft_cpy(char *n_list, char *str)
{
  int i;
  int j;

  if(str == NULL)
    return;
  j = ft_strlen(n_list);
  i = -1;
  while(str[++i])
    n_list[j++] = str[i];
  n_list[j] = '\0';
}

char *get_new_list(char *fstr, char *var, char *tstr)
{
  char *n_list;
  int len;

  n_list = NULL;
  len = ft_strlen(fstr) + ft_strlen(var) + ft_strlen(tstr);
  n_list = (char *)malloc(sizeof(char) * (len + 1));
  if(n_list == NULL)
    return(NULL);
  n_list[0] = '\0';
  ft_cpy(n_list, fstr);
  ft_cpy(n_list, var);
  ft_cpy(n_list, tstr);
  return(n_list);
}

char *ft_getenv(char **env, char *str)
{
  int s;
  int i;
  int st;
  char *new_var;

  s = -1;
  new_var = NULL;
  if(str == NULL)
    return(NULL);
  while(env != NULL && env[++s])
  {
    if(!ft_strncmp(env[s], str, ft_strlen(str)) && env[s][ft_strlen(str)] == '=')
    {
      st = ft_strlen(str);
      st++;
      i = -1;
      while(env[s][++i]);
      new_var = (char *)malloc(sizeof(char) * (i - st + 1));
      if(new_var == NULL)
        return(NULL);
      new_var[0] = '\0';
      ft_cpy(new_var, &env[s][st]);
      new_var[i - st] = '\0';
    }
  }
  return(new_var);
}

int var_dquotes(char **env, t_list **list, int d)
{
  char *fstr;
  char *sstr;
  char *tstr;
  char *var;
  int len;
  int s;

  s = 0;
  fstr = NULL;
  sstr = NULL;
  tstr = NULL;
  len = d;
  fstr = ft_substr((*list)->content, s, len);
  s = len;
  if((*list)->content[len] == '$')
    len++;
  if((*list)->content[len] == '?')
    len++;
  else
  {
    while(ft_isalpha((*list)->content[len]) || ft_isdigit((*list)->content[len]) || (*list)->content[len] == '_')
      len++;
  }
  sstr = ft_substr((*list)->content,s + 1, len - (s + 1));
  if((sstr != NULL && !ft_isalpha(sstr[0]) && sstr[0] != '_' && sstr[0] != '?') || sstr == NULL)
  {
    free(fstr);
    free(sstr);
    return(1);
  }
  s = len;
  while((*list)->content[len])
    len++;
  tstr = ft_substr((*list)->content, s, len - s);
  if(sstr)
  {
    if(sstr[0] == '?')
      var = ft_itoa(g_helper.exit_status);
    else
      var = ft_getenv(env, sstr);
  }
  else
    var = ft_getenv(env, sstr);
  s = count_words(var);
  if(s > 1 && (*list)->back && ((*list)->back->type == APPEND || (*list)->back->type == INPUT \
    || (*list)->back->type == OUTPUT))
  {
    free(fstr);
    free(sstr);
    free(tstr);
    free(var);
    return(1);
  }
  if(s == 0 && tstr == NULL && (*list)->back && ((*list)->back->type == APPEND || (*list)->back->type == INPUT \
    || (*list)->back->type == OUTPUT))
  {
    free(fstr);
    free(sstr);
    free(tstr);
    free(var);
    return(1);
  }
  free(sstr);
  free((*list)->content);
  (*list)->content = get_new_list(fstr, var, tstr);
  free(fstr);
  free(tstr);
  free(var);
  if((*list)->content == NULL)
    return(2);
  return(0);
}

void get_words(int *i, int *end, char *str)
{
  char q;

  while(str[*i] && str[*i] == ' ')
    (*i)++;
  *end = *i;
  while(str[*end] && str[*end] != ' ')
  {
    if(str[*end] == '"' || str[*end] == '\'')
    {
      q = str[*end];
      while(str[++(*end)] != q);
    }
    (*end)++;
  }
}

int count_quotes(char *str)
{
  int i;
  char q;
  int q_n;

  q_n = 0;
  i = -1;
  while(str[++i])
  {
    if(str[i] == '"' || str[i] == '\'')
    {
      q_n++;
      q = str[i];
      while(str[++i])
      {
        if(str[i] == q)
          break;
      }
      if(str[i] == '\0')
        i--;
    }
  }
  return(q_n);
}

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
  int s;

  s = 0;
  while(--i >= 0)
  {
    if(str[i] == '\'')
    {
      s++;
      while(--i >= 0)
      {
        if(str[i] == '\'')
          s++;
      }
      if(s % 2 == 0)
        return(1);
      else
        return(0);
    }
    else if(str[i] == '"')
        return(1);
  }
  return(1);
}

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
