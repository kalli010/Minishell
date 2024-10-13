#include <minishell.h>
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
  if(sstr != NULL && !ft_isalpha(sstr[0]) && sstr[0] != '_' && sstr[0] != '?')
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