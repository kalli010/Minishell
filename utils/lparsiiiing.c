#include <minishell.h>

int quotes_check(char *str)
{
  int i;
  char c;
  int e;

  e = 0;
  i = -1;
  while(str[++i])
  {
    if(str[i] == 34 || str[i] == 39)
    {
      c = str[i];
      while(str[++i])
      {
        if(str[i] == c)
        {
          e++;
          break;
        }
      }
      if(e == 1)
        e = 0;
      else
      {
        printf("Error, check %c.\n",c);
        return(1);
      }
    }
  }
  return(0);
}

void check_p_r(char *str, int *i, int *s)
{
  if(str[0] == '|')
  {
    if(str[0 + 1] != '|')
      *s = *s + 2;
    else
    {
      *s = *s + 2;
      *i = *i + 1;
    }
  }
  else if(str[0] == '>')
  {
    if(str[0 + 1] != '>')
      *s = *s + 2;
    else
    {
      *s = *s + 2;
      *i = *i + 1;
    }
  }
  else if(str[0] == '<')
  {
    if(str[0 + 1] != '<')
      *s = *s + 2;
    else
    {
      *s = *s + 2;
      *i = *i + 1;
    }
  }
  else if(str[0] == '&')
  {
    if(str[0 + 1] == '&')
    {
      *s = *s + 2;
      *i = *i + 1;
    }
  }
  else if(str[0] == 40 || str[0] == 41)
      *s = *s + 2;
}

int check_p_r2(char *str,int *i)
{
  if(str[0] == '|')
  {
    if(str[0 + 1] != '|')
      return(1);
    else
    {
      *i = *i + 1;
      return(0);
    }
  }
  else if(str[0] == '>')
  {
    if(str[0 + 1] != '>')
      return(1);
    else
    {
      *i = *i + 1;
      return(0);
    }
  }
  else if(str[0] == '<')
  {
    if(str[0 + 1] != '<')
      return(1);
    else
    {
      *i = *i + 1;
      return(0);
    }
  }
  else if(str[0] == '&')
  {
    if(str[0 + 1] == '&')
    {
      *i = *i + 1;
      return(0);
    }
  }
  else if(str[0] == 40 || str[0] == 41)
      return(1);
  return(-1);
}

int split_symbols(char *str, char **cmd)
{
  int i;
  int s;
  char *tmp;
  char q;
  int check;

  s = 0;
  i = -1;
  while(str[++i])
  {
    if(str[i] == 34 || str[i] == 39)
    {
      q = str[i];
      while(str[++i] != q);
    }
    check_p_r(&str[i], &i, &s);
  }
  tmp = (char *)malloc(sizeof(char) * (i + s + 1));
  if(tmp == NULL)
    return(1);
  i = -1;
  s = 0;
  while(str[++i])
  {
    if(str[i] == 34 || str[i] == 39)
    {
      q = str[i];
      tmp[s++] = str[i];
      while(str[++i] != q)
        tmp[s++] = str[i];
      tmp[s++] = str[i];
    }
    else
    {
      check = check_p_r2(&str[i], &i);
      if(check == 1)
      {
        tmp[s++] = ' ';
        tmp[s++] = str[i];
        tmp[s++] = ' ';
      }
      else if(check == 0)
      {
        tmp[s++] = ' ';
        tmp[s++] = str[i];
        tmp[s++] = str[i];
        tmp[s++] = ' ';
      }
      else
        tmp[s++] = str[i];
    }
  }
  tmp[s] = '\0';
  *cmd = tmp;
  return(0);
}

int echo_check(char *str)
{
  int i;
  int j;

  i = -1;
  j = 0;
  while(str[++i])
  {
    if(str[i] != ' ')
    {
      j = i;
      while(str[++i] != ' ' && str[i] != '\0');
      if(!ft_strncmp(&str[j], "echo", i - j))
        return(1);
      if(str[i] == '\0')
        i--;
    }
  }
  return(0);
}

int echo_token_count(char *str)
{
  int i;
  int c;
  char q;

  c = 0;
  i = -1;
  while(str[++i])
  {
    if(str[i] != ' ')
    {
      c++;
      if(c == 1)
      {
        while(str[i] != '\0' && str[i] != ' ')
          i++;
      }
      else
      {
        if(str[i] == '|' || str[i] == '<' || str[i] == '>' || str[i] == '&' || str[i] == 40 || str[i] == 41)
        {
          while(str[i] != '\0' && str[i] != ' ')
            i++;
        }
        else
        {
          while(str[i] != '\0' && str[i] != '|' && str[i] != '<' && str[i] != '>' && str[i] != '&' && str[i] != ' ' && str[i] != 40 && str[i] != 41)
          {
            if(str[i] == 34 || str[i] == 39)
            {
              q = str[i];
              while(str[++i] != q);
            }
            i++;
          }
        }
      }
      if(str[i] == '|' || str[i] == '<' || str[i] == '>' || str[i] == '&' || str[i] == 40 || str[i] == 41)
        i--;
      if(str[i] == '\0')
        i--;
    }
  }
  return(c);
}

int token_count(char *str)
{
  int i;
  int c;
  char q;
  int s;

  c = 0;
  i = -1;
  while(str[++i])
  {
    if(str[i] != ' ' && (str[i] < 9 || str[i] > 13))
    {
      s = i;
      while(str[i] != '\0' && (str[i] != ' ' && (str[i] < 9 || str[i] > 13)))
      {
        if(str[i] == 34 || str[i] == 39)
        {
          q = str[i];
          while(str[++i] != q);
        }
        i++;
      }
      if(!ft_strncmp(&str[s], "echo", 4))
      {
        c += echo_token_count(&str[s]);
        return(c);
      }
      if(str[i] == '\0')
        i--;
      c++;
    }
  }
  return(c);
}

int count_words(char *str)
{
  int i;
  int c;
  int in_word;
  char q;

  i = -1;
  c = 0;
  in_word = 0;
  if(str == NULL)
    return(0);
  while(str[++i])
  {
    if(str[i] == '"' || str[i] == '\'')
    {
      q = str[i];
      while(str[++i] != q);
    }
    if(str[i] == ' ')
      in_word = 0;
    else if(str[i] != ' ' && in_word == 0)
    {
      c++;
      in_word = 1;
    }
  }
  return(c);
}

int split_tokens(char *tokens, char **tkn)
{
  char *str;
  int len;
  int i;
  int wd;
  char q;

  wd = count_words(tokens);
  i = -1;
  len = 0;
  while(tokens[++i])
  {
    if(tokens[i] == '"' || tokens[i] == '\'')
    {
      q = tokens[i];
      len++;
      while(tokens[++i] != q)
        len++;
    }
    if(tokens[i] != ' ')
      len++;
  }
  str = (char *)malloc(sizeof(char) * (len + (wd - 1) + 1));
  if(str == NULL)
    return(1);
  i = -1;
  len = -1;
  wd = 0;
  while(tokens[++i])
  {
    if(tokens[i] == '"' || tokens[i] == '\'')
    {
      q = tokens[i];
      str[++len] = tokens[i];
      while(tokens[++i] != q)
        str[++len] = tokens[i];
      str[++len] = tokens[i++];
    }
    if(tokens[i] == ' ')
    {
      wd = 0;
      str[++len] = ' ';
      while(tokens[++i] == ' ');
    }
    if(tokens[i] != ' ' && wd == 0)
    {
      wd = 1;
      while(tokens[i] != '\0' && tokens[i] != ' ')
      {
        if(tokens[i] == '"' || tokens[i] == '\'')
        {
          q = tokens[i];
          str[++len] = tokens[i];
          while(tokens[++i] != q)
            str[++len] = tokens[i];
        }
        str[++len] = tokens[i++];
      }
      i--;
    }
  }
  str[++len] = '\0';
  free(tokens);
  *tkn = str;
  return(0);
}

int echo_create_tokens(char *str, int j, char ***tokens)
{
  int i;
  int s;
  int x;
  char q;

  x = 0;
  i = -1;
  while(str[++i])
  {
    if(str[i] != ' ')
    {
      s = i;
      if(x == 0)
        while(str[i] != '\0' && str[i] != ' ' && (str[i] < 9 || str[i] > 13))
        {
          if(str[i] == 34 || str[i] == 39)
            {
              q = str[i];
              while(str[++i] != q);
            }
          i++;
        }
      else
      {
        if(str[i] == '|' || str[i] == '<' || str[i] == '>' || str[i] == '&' || str[i] == '&' || str[i] == 40 || str[i] == 41)
        {
          x = -1;
          while(str[i] != '\0' && str[i] != ' ' && (str[i] < 9 || str[i] > 13))
            i++;
        }
        else if(str[i] == '-')
        {
          while(str[++i] == 'n' || str[i] == '"' || str[i] == '\'');
          if(str[i] != ' ')
          {
            while(str[i] != '\0' && str[i] != '|' && str[i] != '<' && str[i] != '>' && str[i] != '&' && str[i] != 40 && str[i] != 41)
            {
              if(str[i] == 34 || str[i] == 39)
              {
                q = str[i];
                while(str[++i] != q);
              }
              i++;
            }
            while(str[--i] == ' ' && (str[i] < 9 || str[i] > 13));
            i++;
          }
        }
        else
        {
          while(str[i] != '\0' && str[i] != '|' && str[i] != '<' && str[i] != '>' && str[i] != '&' && str[i] != 40 && str[i] != 41)
          {
            if(str[i] == 34 || str[i] == 39)
            {
              q = str[i];
              while(str[++i] != q);
            }
            i++;
          }
          while(str[--i] == ' ' && (str[i] < 9 || str[i] > 13));
          i++;
        }
        
      }
      (*tokens)[j] = ft_substr(str, s, i - s);
      if((*tokens)[j] == NULL)
      {
        i = -1;
        while(++i < j)
          free((*tokens)[i]);
        return (1);
      }
      if(split_tokens((*tokens)[j], &(*tokens)[j]))
      {
        i = -1;
        while(++i < j)
          free((*tokens)[i]);
        return (1);
      }
      j++;
      x++;
      if(str[i] == '|' || str[i] == '<' || str[i] == '>' || str[i] == '&' || str[i] == 40 || str[i] == 41)
        i--;
      if(str[i] == '\0')
        i--;
    }
  }
  (*tokens)[j] = NULL;
  return(0);
}

int create_tokens(char *str, char ***tokens)
{
  int i;
  int s;
  int j;
  char q;

  j = 0;
  i = -1;
  while(str[++i])
  {
    if(str[i] != ' ' && (str[i] < 9 || str[i] > 13))
    {
      s = i;
      while(str[i] != '\0' && str[i] != ' ' && (str[i] < 9 || str[i] > 13))
      {
        if(str[i] == 34 || str[i] == 39)
        {
          q = str[i];
          while(str[++i] != q);
        }
        i++;
      }
      if(!ft_strncmp(&str[s], "echo", 4) || !ft_strncmp(&str[s], "\"echo\"", 6))
      {
        if(echo_create_tokens(&str[s], j, tokens))
          return (1);
        return(0);
      }
      (*tokens)[j] = ft_substr(str, s, i - s);
      if((*tokens)[j] == NULL)
      {
        i = -1;
        while(++i < j)
          free((*tokens)[i]);
        return (1);
      }
      j++;
      if(str[i] == '\0')
        i--;
    }
  }
  (*tokens)[j] = NULL;
  return(0);
}

int tokenizer(char *str, char ***tokens)
{
  int tc;

  tc = token_count(str);
  *tokens = (char **)malloc(sizeof(char *) * (tc + 1));
  if(tokens == NULL)
    return(1);
  if(create_tokens(str, tokens))
    return(1);
  free(str);
  return(0);
}

void token_type(t_list *list)
{
  if(list->content[0] == '|' && list->content[1] == '|' && list->content[2] == '\0')
    list->type = OR;
  else if(list->content[0] == '&' && list->content[1] == '&' && list->content[2] == '\0')
    list->type = AND;
  else if(list->content[0] == '<' && list->content[1] == '<' && list->content[2] == '\0')
    list->type = HEREDOC;
  else if(list->content[0] == '>' && list->content[1] == '>' && list->content[2] == '\0')
    list->type = APPEND;
  else if(list->content[0] == '|' && list->content[1] == '\0')
      list->type = PIPE;
  else if(list->content[0] == '>' && list->content[1] == '\0')
      list->type = OUTPUT;
  else if(list->content[0] == '<' && list->content[1] == '\0')
      list->type = INPUT;
  else if((list->content[0] == ')' && list->content[1] == '\0') || (list->content[0] == '(' && list->content[1] == '\0'))
    list->type = PARENTHESIS;
  else if(list->back != NULL && list->back->type == HEREDOC)
    list->type = DELIMITER;
  else if(list->back != NULL \
      && (list->back->type == OUTPUT || list->back->type == APPEND || \
    list->back->type == INPUT))
      list->type = PATH;
  else if(list->back != NULL && \
      (list->back->type == COMMAND || list->back->type == OPTIONS \
      || list->back->type == PATH_COMMAND))
    list->type = OPTIONS;
  else if(list->content[0] == '/' || list->content[0] == '~' \
      || !ft_strncmp(list->content, "./", 2))
      {
        if(list->back != NULL)
        {
          if(list->back->type != COMMAND && list->back->type != VAR)
            list->type = PATH_COMMAND;
        }
        else if(list->back == NULL)
          list->type = PATH_COMMAND;
        else
          list->type = PATH;
      }
  
  else if(list->back != NULL && list->content[0] == '$')
     list->type = VAR;
  
  else
    list->type = COMMAND;
}

int creat_linked_list(t_list **list, char **tokens)
{
  int i;
  t_list *tmp;

  i = -1;
  while(tokens[++i])
  {
    if(ft_lstadd_back(list, ft_lstnew(tokens[i])))
    {
      free_list(*list);
      free(tokens);
      return(1);
    }
    tmp = *list;
    while(tmp->next != NULL)
      tmp = tmp->next;
    token_type(tmp);
  }
  return(0);
}

int check_red_with_cmd(t_list *list)
{
  while(list)
  {
    if(list->type == INPUT || list->type == OUTPUT || list->type == APPEND)
    {
      if(list->next != NULL && list->next->next != NULL && (list->next->next->type == COMMAND || list->next->next->type == OPTIONS))
        return(1);
    }
    list = list->next;
  }
  return(0);
}

void free_list(t_list *list)
{
  t_list *tmp;
  
  if(list == NULL)
    return;
  while(list)
  {
    tmp = list;
    list = list->next;
    if(tmp->content)
      free(tmp->content);
    free(tmp);
  }
}

int recreate_linked_list(t_list *list, t_list **lst)
{
  t_list *n_list;
  t_list *tmp;
  t_list *start;

  n_list = NULL;
  while(list)
  {
    if(list->type == INPUT || list->type == OUTPUT)
    {
      tmp = list->next;
      while(tmp && (tmp->type == PATH || tmp->type == PATH_COMMAND || tmp->type == INPUT || tmp->type == OUTPUT || tmp->type == APPEND))
        tmp = tmp->next;
      if(tmp && (tmp->type == COMMAND || tmp->type == OPTIONS))
      {
        start = tmp;
        while(tmp && (tmp->type == COMMAND || tmp->type == OPTIONS))
        {
          if(ft_lstadd_back(&n_list, ft_lstnew(tmp->content)))
          {
            free_list(n_list);
            return(1);
          }
          token_type(n_list);
          tmp = tmp->next;
        }
        start->back->next = tmp;
      }
      if(ft_lstadd_back(&n_list, ft_lstnew(list->content)))
      {
        free_list(n_list);
        return(1);
      }
    }
    else
    {
      if(ft_lstadd_back(&n_list, ft_lstnew(list->content)))
      {
        free_list(n_list);
        return(1);
      }
    }
    list = list->next;
  }
  tmp = n_list;
  while(tmp)
  {
    token_type(tmp);
    tmp = tmp->next;
  }
  free_list(*lst);
  *lst = n_list;
  return(0);
}

int symbols_check(t_list *list)
{
  if(list == NULL)
    return(0);
  if(list->type == PIPE)
  {
    printf("10\n");
    printf("syntax error\n");
    return(1);
  }
  if(list->back == NULL)
  {
    if(list->next != NULL)
      list = list->next;
  }
  if(list->back != NULL)
  {
    while(list->next != NULL)
    {
      if(list->type == PIPE && list->back->type != WORD \
        && list->back->type != COMMAND && list->back->type != OPTIONS \
        && list->back->type != VAR && list->back->type != PATH \
        && list->back->type != SET_VAR && list->back->type != PATH_COMMAND \
        && list->back->type != DELIMITER && list->back->type != PARENTHESIS)
      {
        printf("9\n");
        printf("syntax error\n");
        return(1);
      }
      else if(list->back != NULL && (list->type == list->back->type) && \
        (list->type != WORD && list->type != OPTIONS && list->type != PARENTHESIS))
      {
        printf("8\n");
        printf("syntax error\n");
        return(1);
      }
      else if(list ->back != NULL && (list->content[0] == '<' && list->back->content[0] == '>') && \
        (list->type == INPUT || list->type == HEREDOC) &&\
        (list->back->type == OUTPUT || list->back->type == APPEND))
      {
        printf("7\n");
        printf("syntax error\n");
        return(1);
      }
      else if((list->content[0] == '>' && list->back->content[0] == '<') && \
        (list->type == OUTPUT || list->type == APPEND) &&\
        (list->back->type == INPUT || list->back->type == HEREDOC))
      {
        printf("6\n");
        printf("syntax error\n");
        return(1);
      }
      else if(list->content[0] == '|' && list->back->content[0] == '|' && \
        (list->type == OR || list->type == PIPE) &&\
        (list->back->type == OR || list->back->type == PIPE))
      {
        printf("5\n");
        printf("syntax error\n");
        return(1);
      }
      else if(list->back != NULL && list->content[0] == '<' && list->back->content[0] == '<' && \
        (list->type == INPUT || list->type == HEREDOC) &&\
        (list->back->type == INPUT || list->back->type == HEREDOC))
      {
        printf("4\n");
        printf("syntax error\n");
        return(1);
      }
      else if(list->content[0] == '>' && list->back->content[0] == '>' && \
        (list->type == OUTPUT || list->type == APPEND) &&\
        (list->back->type == OUTPUT || list->back->type == APPEND))
      {
        printf("3\n");
        printf("syntax error\n");
        return(1);
      }
      else if(list->type == HEREDOC && list->back->type == PIPE)
      {
        printf("2\n");
        printf("syntax error\n");
        return(1);
      }
      list = list->next;
    }
  }
  if(list->type != WORD && list->type != OPTIONS \
      && list->type != COMMAND \
      && list->type != VAR && list->type != PATH \
      && list->type != PATH_COMMAND \
      && list->type != DELIMITER\
      && list->type != PARENTHESIS)
  {
      printf("1\n");
      printf("syntax error\n");
      return(1);
  }
  return(0);
}

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

t_tree *create_tree_node(t_list *list)
{
  t_tree *n_node;

  n_node = (t_tree *)malloc(sizeof(t_tree));
  if(!n_node)
    return (NULL);
  n_node->content = list;
  n_node->first_child = NULL;
  n_node->next_sibling = NULL;
  return(n_node);
}

void add_child_to_tree(t_tree *parent, t_tree *child)
{
  t_tree *last_sibling;
  
  if(parent == NULL)
    return;
  if(parent->first_child == NULL)
    parent->first_child = child;
  else {
    last_sibling = parent->first_child;
    while(last_sibling->next_sibling!= NULL)
      last_sibling = last_sibling->next_sibling;
    last_sibling->next_sibling = child;
  }
}

void add_sibling_to_child(t_tree *child, t_tree *sibling)
{
  t_tree *l_sibling;

  if(child->next_sibling == NULL)
    child->next_sibling = sibling;
  else {
    l_sibling = child->next_sibling;
    while(l_sibling->next_sibling != NULL)
      l_sibling = l_sibling->next_sibling;
    l_sibling->next_sibling = sibling;
  }
}

int check_parenthesis(t_list *list)
{
  int c;

  c = 0;
  while(list)
  {
    if(list->content[0] == 40 || list->content[0] == 41)
    {
      c++;
      return(c);
    }
    list = list->next;
  }
  return(0);
}

int check_parenthesis_error(t_list *list)
{
  int p;
  t_list *node;

  node = list;
  p = 0;
  while(node)
  {
    if(node->content[0] == 40)
    {
      if((node->back != NULL && \
        (node->back->type != PIPE && node->back->type != AND \
        && node->back->type != OR && node->back->content[0] != 40)) \
        || (node->next != NULL && node->next->type != COMMAND \
        && node->next->type != PATH_COMMAND \
        && node->next->content[0] != 40))
        return(1);
      p++;
    }
    node = node->next;
  }
  while(list)
  {
    if(list->content[0] == 41)
    {
      if(list->next != NULL && \
        ((list->back && list->back->type != COMMAND && list->back->type != OPTIONS && list->back->content[0] != 41)\
        || (list->next->type == COMMAND \
        || list->next->type == OPTIONS)))
        return(1);
      p--;
    }
    list = list->next;
  }
  return(p);
}

t_tree *creat_subtree(t_list **list)
{
  t_tree *s_tree;
  t_tree *r_tree;
  t_tree *l_tree;

  l_tree = NULL;
  s_tree = NULL;
  r_tree = NULL;
  while(*list && (*list)->content[0] != 41)
  {
    if((*list)->content[0] == 40)
    {
      *list = (*list)->next;
      l_tree = creat_subtree(&(*list));
      *list = (*list)->next;
    }
    s_tree = creat_tree(*list);
    
    while((*list)->content[0] != 41)
    {
      (*list)->in = 1;
      if((*list)->content[0] == 40)
        break;
      *list = (*list)->next;
    }
    if(l_tree != NULL)
    {
      if(r_tree != NULL)
        add_child_to_tree(r_tree, l_tree);
      else
      {
        add_sibling_to_child(l_tree, s_tree->first_child);
        s_tree->first_child = l_tree;
      }
    }
    if(r_tree == NULL)
      r_tree = s_tree;
    else if(s_tree != NULL && s_tree->first_child != NULL)
    {
      add_sibling_to_child(r_tree, s_tree->first_child);
      s_tree->first_child = r_tree;
      r_tree = s_tree;
    }
    else if(s_tree != NULL && s_tree->first_child == NULL)
    {
      add_child_to_tree(s_tree, r_tree);
      r_tree = s_tree;
    }
  }
  return(r_tree);
}

t_tree *creat_tree_with_parenthesis(t_list *list)
{
  t_tree *root;
  t_tree *l_node;
  t_tree *r_tree;

  r_tree = NULL;
  l_node = NULL;
  root = NULL;
  while(list)
  {
    if(list->content[0] == 41)
      list = list->next;
    if(list->content[0] == 40)
    {
      list = list->next;
      r_tree = creat_subtree(&list);
      list = list->next;
    }
    if(root != NULL && r_tree != NULL)
    {
      if(root->first_child->next_sibling != NULL)
        add_child_to_tree(root->first_child->next_sibling, r_tree);
      else
        add_child_to_tree(root, r_tree);
    }
    l_node = creat_tree(list);
    
    if(root == NULL)
    {
      if(r_tree != NULL)
      {
        if(l_node != NULL && l_node->first_child != NULL)
        {
          if(l_node->first_child->content->type == COMMAND \
            || l_node->content == list)
          {
            add_sibling_to_child(r_tree, l_node->first_child);
            l_node->first_child = r_tree;
          }
          else {
            add_child_to_tree(l_node->first_child, r_tree);
          }
        }
        else if(l_node != NULL)
          add_child_to_tree(l_node, r_tree);
      }
      if(l_node != NULL)
        root = l_node;
      else {
        root = r_tree;
      }
    }
    else if(l_node != NULL && l_node->first_child != NULL)
    {
      add_sibling_to_child(root, l_node->first_child);
      l_node->first_child = root;
      root = l_node;
    }
    else if(l_node != NULL && l_node->first_child == NULL)
    {
      add_child_to_tree(l_node, root);
      root = l_node;
    }
    while(list != NULL && list->content[0] != 40)
      list = list->next;
    r_tree = NULL;
  }
  if(root == NULL)
    root = r_tree;
  return(root);
}

t_tree *creat_tree(t_list *lst)
{
  t_tree *root;
  t_tree *n_node;
  t_tree *l_node;

  l_node = NULL;
  n_node = NULL;
  root = NULL;
  while(lst)
  {
    if(lst->content[0] == 41 || lst->content[0] == 40)
      return(root);
    n_node = create_tree_node(lst);
    if(root == NULL)
      root = n_node;
    else if( n_node->content->type == PIPE 
        || n_node->content->type == OR 
        || n_node->content->type == AND 
        || n_node->content->type == OUTPUT 
        || n_node->content->type == HEREDOC 
        || n_node->content->type == INPUT 
        || n_node->content->type == APPEND)
    {
      add_child_to_tree(n_node, root);
      root = n_node;
    }
    else
    {
      if(l_node->content->type != COMMAND && root != l_node)
        add_sibling_to_child(l_node, n_node);
      else
        add_child_to_tree(l_node, n_node);
    }
    if(n_node->content->type == OR || n_node->content->type == AND)
    {
      
      l_node = creat_tree(lst->next);
      if(l_node != NULL && (l_node->content->type == OR || l_node->content->type == AND))
      {
        root = l_node;
        while(l_node->first_child->first_child)
          l_node = l_node->first_child;
        add_child_to_tree(n_node, l_node->first_child);
        add_sibling_to_child(n_node, l_node->first_child->next_sibling);
        //l_node->first_child->next_sibling->next_sibling = NULL;
        l_node->first_child->next_sibling = NULL;
        l_node->first_child = n_node;
      }
      else
        add_child_to_tree(n_node, l_node);
      return(root);
    }
    l_node = n_node;
    lst = lst->next;
  }
  return(root);
}

void print_tree(t_tree *root, int spaces)
{
  int i;
  t_tree *child;

  i = -1;
  if(root == NULL)
    return;
  while(++i < spaces)
    printf(" ");
  printf("%s  (%d)\n",root->content->content,root->content->type);
  child = root->first_child;
  while(child)
  {
    print_tree(child, spaces + 2);
    child = child->next_sibling;
  }
}

void free_tree(t_tree *root)
{
  t_tree *child;
  t_tree *next;

  if(root == NULL)
    return;
  child = root->first_child;
  while(child)
  {
    next = child->next_sibling;
    free_tree(child);
    child = next;
  }
  if (root->content->content != NULL)
    free(root->content->content);
  free(root->content);
  free(root);
}

int env_size(char **str)
{
  int s;

  s = 0;
  while(str[s])
    s++;
  return(s);
}

char **create_env(char **envp)
{
  char **env;
  int s;
  int i;
  char ***new_env;

  i = -1;
  s = env_size(envp);
  env = (char **)malloc(sizeof(char *) * (s + 1));
  if(env == NULL)
    return(NULL);
  while(envp[++i])
  {
    env[i] = ft_substr(envp[i], 0, ft_strlen(envp[i]));
    if(env[i] == NULL)
    {
      while(--i >= 0)
        free(env[i]);
      free(env);
    }
  }
  env[i] = NULL;
  new_env = &env;
  return(env);
}

int get_var_value(char *env, char **var, char **value)
{
  int i;
  int s;

  i = -1;
  while(env[++i] && env[i] != '=');
  *var = ft_substr(env, 0, i);
  if(*var == NULL)
    return(1);
  if(env[i] != '\0')
    i++;
  s = i;
  while(env[i++]);
  *value = ft_substr(env, s, i - s);
  return(0);
}

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

int clean_heredoc(char **redfile, int hd)
{
  int i;

  i = -1;
  while(redfile[++i] && hd-- > 0)
  {
    if (unlink(redfile[i]) < 0)
    {
      printf("Error deleting redfile\n");
      return(1);
    }
  }
  return(0);
}

int check_quotes(char *str)
{
  int i;

  i = -1;
  while(str[++i])
  {
    if(str[i] == '"' || str[i] == '\'')
      return(1);
  }
  return(0);
}

int expand_line(char **env, char **str, int d)
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
  fstr = ft_substr((*str), s, len);
  s = len;
  if((*str)[len] == '$')
    len++;
  if((*str)[len] == '?')
    len++;
  else
  {
    while(ft_isalpha((*str)[len]) || ft_isdigit((*str)[len]) || (*str)[len] == '_')
      len++;
  }
  sstr = ft_substr((*str),s + 1, len - (s + 1));
  if(sstr != NULL && !ft_isalpha(sstr[0]) && sstr[0] != '_' && sstr[0] != '?')
  {
    free(fstr);
    free(sstr);
    return(1);
  }
  s = len;
  while((*str)[len])
    len++;
  tstr = ft_substr((*str), s, len - s);
  if(sstr)
  {
    if(sstr[0] == '?')
      var = ft_itoa(g_helper.exit_status);
    else
      var = ft_getenv(env, sstr);
  }
  else
    var = ft_getenv(env, sstr);
  free(sstr);
  free((*str));
  (*str) = get_new_list(fstr, var, tstr);
  free(fstr);
  free(tstr);
  free(var);
  return(0);
}

void clean_env(char **env)
{
  int i;

  i = -1;
  while(env[++i])
    free(env[i]);
  free(env);
}

void sigint_handler(int sig)
{
  int i;

  if (sig == SIGINT)
  {
    free_list(g_helper.list);
    if (g_helper.redfile)
    {
      i = -1;
      while (g_helper.redfile[++i])
        free(g_helper.redfile[i]);
      free(g_helper.redfile);
    }
    if(*g_helper.envp != NULL)
      clean_env(g_helper.envp);
    if(*g_helper.xenv != NULL)
      clean_env(g_helper.xenv);
  exit(1);
  }
}

int open_file(char *redfile, t_list *delimiter, char **env, char **xenv, t_list *list, char ***rf)
{
  int fd;
  char *line;
  pid_t pid;
  int status;
  int d;
  int i;

  i = 0;
  d = -1;
  if(!check_quotes(delimiter->content))
    i = 1;
  remove_quotes_string(delimiter->content);
  fd = open(redfile, O_CREAT | O_WRONLY, 0644);
  if (fd < 0)
  {
    printf("Error creating redfile\n");
    return (1);
  }
  pid = fork();
  if (pid == -1)
  {
    printf("Fork failed");
    close(fd);
    return (1);
  }
  else if (pid == 0)
  {
    signal(SIGINT, sigint_handler);
    while (1)
    {
      line = readline("> ");
      if (!line)
      {
          printf("Error: (Ctrl+D)\n");
          break;
      }
      if (delimiter->content[0] == '\0')
      {
          if (line[0] == '\0')
              break;
      }
      else if (!ft_strncmp(line, delimiter->content, ft_strlen(delimiter->content)))
          break;
      if(i == 1)
      {
        d = check_d(line, -1);
        while(line[d])
        {
          if(expand_line(env, &line, d))
          {
            close(fd);
            free_list(list);
            i = -1;
            while((*rf)[++i])
              free((*rf)[i]);
            free(*rf);
            clean_env(env);
            clean_env(xenv);
            exit(1);
          }
          else
            d = check_d(line, d);
        }
      }
      write(fd, line, ft_strlen(line));
      write(fd, "\n", 1);
      free(line);
    }
    free(line);
    close(fd);
    free_list(list);
    i = -1;
    while((*rf)[++i])
      free((*rf)[i]);
    free(*rf);
    clean_env(env);
    clean_env(xenv);
    exit(0);
  }
  else
  {
    waitpid(pid, &status, 0);
    if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
    {
      printf("^C\n");
      close(fd);
      return (1);
    }
  }
  close(fd);
  return (0);
}

void implementing_heredoc(t_list **list, char ***redfile)
{
  t_list *back;
  t_list *next;
  t_list *tmp;
  int i;
  char *red;

  red = NULL;
  i = -1;
  next = NULL;
  while(*list)
  {
    if((*list)->type == HEREDOC)
    {
      back = (*list)->back;
      next = (*list)->next->next;
      i++;
      while(*list != next)
      {
        tmp = *list;
        *list = (*list)->next;
        if(tmp->content)
          free(tmp->content);
        free(tmp);
      }
      if(back != NULL)
        back->next = NULL;
      red = (char *)malloc(sizeof(char) * 2);
      red[0] = '<';
      red[1] = '\0';
      ft_lstadd_back(&back, ft_lstnew(red));
      if(back->next != NULL)
        back = back->next;
      back->type = INPUT;
      ft_lstadd_back(&back, ft_lstnew((*redfile)[i]));
      back = back->next;
      back->type = PATH;
      if(back != NULL)
        back->next = *list;
      if((*list) != NULL)
        (*list)->back = back;
      else
        *list = back;
      if(*list != NULL && (*list)->back != NULL)
        *list = (*list)->back;
    }
    if(*list && (*list)->next == NULL)
      break;
    if(*list != NULL)
      *list = (*list)->next;
  }
  while(*list && (*list)->back)
    *list = (*list)->back;
}

int heredoc(t_list **list, int size, char **env, char **xenv, char ***rf)
{
  int i;
  char *nbr;
  int j;
  t_list *delimiter;
  int n;

  delimiter = *list;
  i = -1;
  *rf = (char **)malloc(sizeof(char *) * (size + 1));
  while(++i < size)
  {
    (*rf)[i] = (char *)malloc(sizeof(char) * 16);
    (*rf)[i][0] = '\0';
    ft_cpy((*rf)[i], "/tmp/.redfile");
    nbr = ft_itoa(i);
    j = 12;
    n = -1;
    while(nbr[++n])
      (*rf)[i][++j] = nbr[n];
    (*rf)[i][++j] = '\0';
    free(nbr);
  }
  (*rf)[i] = NULL;
  i = -1;
  while(delimiter)
  {
    if(delimiter->type == HEREDOC)
    {
      if(open_file((*rf)[++i], delimiter->next, env, xenv, *list, rf))
      {
        clean_heredoc(*rf, 1);
        return(1);
      }
    }
    delimiter = delimiter->next;
  }
  implementing_heredoc(list, rf);
  return(0);
}

int check_wildcards(t_list *list)
{
  int i;
  char q;

  while(list)
  {
    i = -1;
    while(list->content[++i])
    {
      if(list->content[i] == '"' || list->content[i] == '\'')
      {
        q = list->content[i];
        while(list->content[++i] != q);
      }
      if(list->content[i] == '*')
        return(1);
    }
    list = list->next;
  }
  return(0);
}

int ft_find(const char *filename, char *str, int flag)
{
  int i;
  int j;

  i = 0;
  j = 0;
  if(flag == 0)
  {
    while(str[i] == filename[i])
      i++;
    if(str[i] == '\0')
      return(i);
    else
      return(-1);
  }
  else if(flag == 1)
  {
    while(filename[i] && filename[i] != str[j])
      i++;
    while(str[j] && filename[i] && filename[i] == str[j])
    {
      i++;
      j++;
    }
    if(str[j] == '\0')
      return(i);
    else
      return(-1);
  }
  else
  {
    while(filename[i] && filename[i] != str[j])
      i++;
    while(filename[i] && str[j] && filename[i] == str[j])
    {
      i++;
      j++;
    }
    if(str[j] == '\0' && filename[i] == '\0')
      return(i);
    else
      return(-1);
  }
}

int implementing_wildcards(char *wc, const char *filename)
{
  char *str;
  int i;
  int len;
  int s;
  int flag;

  len = 0;
  flag = -1;
  if(filename != NULL && filename[0] == '.')
    return(1);
  i = -1;
  while(wc[++i] == '*')
  {
    if(wc[i] == '\0')
      return(0);
  }
  i = 0;
  while (wc[len])
  {
    s = len;
    while (wc[len] != '*' && wc[len] != '\0')
        len++;
    if(len != 0 && flag == -1)
      flag = 0;
    else if(wc[len] == '\0')
      flag = 2;
    else
      flag =1;
    str = ft_substr(wc, s, len - s);
    if (str != NULL)
    {
      i += ft_find(&filename[i], str, flag);
      if (i == -1)
      {
        free(str);
        return 1;
      }
    }
    free(str);
    while (wc[len] == '*')
     len++;
  }
  return(0);
}

t_list	*ft_lstnew_2(char *content)
{
	t_list	*a;

	a = malloc(sizeof(t_list));
	if (!a)
		return (NULL);
	a->content = ft_substr(content, 0, ft_strlen(content));
	a->next = NULL;
	a->back = NULL;
  a->i = 0;
  a->in = 0;
  return (a);
}

void wildcards_linked_list(t_list *list, char *str)
{
  t_list *next;

  next = list->next;
  list->next = NULL;
  ft_lstadd_back(&list, ft_lstnew_2(str));
  list = list->next;
  list->type = OPTIONS;
  if (list && next)
  {
    list->next = next;
    next->back = list;
  }
}

void clean_wildcards(t_list *list)
{
  t_list *back;
  t_list *next;

  back = list->back;
  next = list->next;
  free(list->content);
  free(list);
  back->next = next;
  next->back = back;
}

int wildcards(t_list *list)
{
  struct dirent *entry;
  DIR *dir;
  int d;
  int i;
  int f;

  dir = opendir(".");
  if (dir == NULL)
    return 1;
  while (list)
  {
    f = 0;
    i = -1;
    while (list->content[++i])
    {
      if (list->content[i] == '*')
      {
        d = 0;
        rewinddir(dir);
        while ((entry = readdir(dir)) != NULL)
        {
          if (!implementing_wildcards(list->content, entry->d_name))
          {
            wildcards_linked_list(list, entry->d_name);
            d++;
          }
        }
        if (d != 0)
        {
          clean_wildcards(list);
          f++;
        }
        break;
      }
    }
    while(f != 0)
    {
      list = list->back;
      f--;
    }
    list = list->next;
  }
  closedir(dir);
  return 0;
}
