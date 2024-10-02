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

char *split_symbols(char *str)
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
  return(tmp);
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
    if(str[i] != ' ')
    {
      s = i;
      while(str[i] != '\0' && str[i] != ' ')
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

char *split_tokens(char *tokens)
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
  return(str);
}

void echo_create_tokens(char *str, char **tokens, int j)
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
        while(str[i] != '\0' && str[i] != ' ')
          i++;
      else
      {
        if(str[i] == '|' || str[i] == '<' || str[i] == '>' || str[i] == '&' || str[i] == '&' || str[i] == 40 || str[i] == 41)
        {
          x = -1;
          while(str[i] != '\0' && str[i] != ' ')
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
            while(str[--i] == ' ');
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
          while(str[--i] == ' ');
          i++;
        }
        
      }
      tokens[j] = ft_substr(str, s, i - s);
      tokens[j] = split_tokens(tokens[j]);
      j++;
      x++;
      if(str[i] == '|' || str[i] == '<' || str[i] == '>' || str[i] == '&' || str[i] == 40 || str[i] == 41)
        i--;
      if(str[i] == '\0')
        i--;
    }
  }
  tokens[j] = NULL;
}

void create_tokens(char *str, char **tokens)
{
  int i;
  int s;
  int j;
  char q;

  j = 0;
  i = -1;
  while(str[++i])
  {
    if(str[i] != ' ')
    {
      s = i;
      while(str[i] != '\0' && str[i] != ' ')
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
        echo_create_tokens(&str[s], tokens, j);
        return;
      }
      tokens[j] = ft_substr(str, s, i - s);
      j++;
      if(str[i] == '\0')
        i--;
    }
  }
  tokens[j] = NULL;
}

char **tokenizer(char *str)
{
  char **tokens;
  int tc;

  tc = token_count(str);
  tokens = (char **)malloc(sizeof(char *) * (tc + 1));
  create_tokens(str, tokens);
  return(tokens);
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
  else if(list->back != NULL \
      && (list->back->type == OUTPUT || list->back->type == APPEND || \
    list->back->type == INPUT))
      list->type = PATH;
  else if(list->back != NULL && list->content[0] == '$')
     list->type = VAR;
  else if(list->back != NULL && list->back->type == HEREDOC)
    list->type = DELIMITER;
  else
    list->type = COMMAND;
}

void creat_linked_list(t_list **list, char **tokens, int t)
{
  int i;
  t_list *tmp;

  i = -1;
  while(tokens[++i])
  {
    ft_lstadd_back(list, ft_lstnew(tokens[i]));
    tmp = *list;
    while(tmp->next != NULL)
      tmp = tmp->next;
    token_type(tmp);
  }
  if(!t)
    free(tokens);
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
  tmp = list;
  while(list)
  {
    list = list->next;
    free(tmp->content);
    free(tmp);
    tmp = list;
  }
}

t_list *recreate_linked_list(t_list *list)
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
      while(tmp && (tmp->type == PATH || tmp->type == list->type))
        tmp = tmp->next;
      if(tmp && (tmp->type == COMMAND || tmp->type == OPTIONS))
      {
        start = tmp;
        while(tmp && (tmp->type == COMMAND || tmp->type == OPTIONS))
        {
          ft_lstadd_back(&n_list, ft_lstnew(tmp->content));
          token_type(n_list);
          tmp = tmp->next;
        }
        start->back->next = tmp;
      }
      ft_lstadd_back(&n_list, ft_lstnew(list->content));
      token_type(n_list);
    }
    else
    {
      ft_lstadd_back(&n_list, ft_lstnew(list->content));
      token_type(n_list);
    }
    list = list->next;
  }
  free_list(list);
  return(n_list);
}

int check_red(t_list *list)
{
  while(list)
  {
    if(list->type == OUTPUT || list->type == INPUT || list->type == APPEND)
      return(1);
    list = list->next;
  }
  return(0);
}

void create_list_with_ap(t_list **start, t_list **tmp)
{
  t_list *node;
  t_list *end;
  t_list *last;

  last = (*tmp)->back;
  node = (*start)->next;
  (*start)->next = *tmp;
  (*tmp)->back = *start;
  tmp = &(*tmp)->next;
  end = (*tmp)->next;
  (*tmp)->next = node;
  node->back = *tmp;
  last->next = end;
  if(end != NULL)
    end->back = last;
}

void create_list_with_red(t_list **list)
{
  t_list *tmp;
  t_list *start;
  t_list *node;

  tmp = *list;
  while(tmp)
  {
    if(tmp->type == OUTPUT || tmp->type == INPUT || tmp->type == APPEND)
    {
      start = tmp;
      while(tmp->next != NULL && (tmp->next->type == OUTPUT || tmp->next->type == INPUT || tmp->next->type == APPEND\
        || tmp->next->type == PATH))
        tmp = tmp->next;
      if(start->next && start->next != tmp)
      {
        if(tmp->back->type == APPEND)
          create_list_with_ap(&start->back, &tmp->back);
        else
        {
          node = start->next->next;
          start->next->back = tmp->back;
          start->next->next = tmp->next;
          tmp->back->next = start->next;
          if(tmp->next != NULL)
            tmp->next->back = start->next;
          tmp->back = start;
          tmp->next = node;
          node->back = tmp;
          start->next = tmp;
        }
      }
    }
    tmp = tmp->next;
  }
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
  char *new_var;

  s = -1;
  new_var = NULL;
  while(env != NULL && env[++s])
  {
    if(!ft_strncmp(env[s], str, ft_strlen(str)) && env[s][ft_strlen(str)] == '=')
    {
      i = ft_strlen(str);
      while(env[s][++i]);
      new_var = (char *)malloc(sizeof(char) * (i + 1));
      new_var[0] = '\0';
      ft_cpy(new_var, &env[s][ft_strlen(str) + 1]);
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
  len = 0;
  fstr = NULL;
  sstr = NULL;
  tstr = NULL;
  while(( d != 0 && (*list)->content[len] && ((*list)->content[len] != '$' || ((*list)->content[len + 1] \
    && (*list)->content[len + 1] == '$'))) || d > 0)
  {
    d--;
    len++;
  }
  fstr = ft_substr((*list)->content, 0, len);
  s = len;
  if((*list)->content[len] == '$')
    len++;
  if((*list)->content[len] == '?')
    len++;
  else
  {
    while((*list)->content[len] && (*list)->content[len] != '"' && (*list)->content[len] != '\'' \
      && (*list)->content[len] != '$')
      len++;
  }
  sstr = ft_substr((*list)->content,s + 1, len - (s + 1));
  s = len;
  while((*list)->content[len])
    len++;
  tstr = ft_substr((*list)->content, s, len - s);
  if(sstr)
  {
    if(sstr[0] == '?')
      var = ft_itoa(g_exit_status);
    else
      var = ft_getenv(env, sstr);
  }
  else
    var = "";
  s = count_words(var);
  if(s > 1 && (*list)->back && ((*list)->back->type == APPEND || (*list)->back->type == INPUT \
    || (*list)->back->type == OUTPUT))
    return(1);
  if(s == 0 && tstr == NULL && (*list)->back && ((*list)->back->type == APPEND || (*list)->back->type == INPUT \
    || (*list)->back->type == OUTPUT))
    return(1);
  free(sstr);
  free((*list)->content);
  (*list)->content = get_new_list(fstr, var, tstr);
  free(fstr);
  free(tstr);
  return(0);
}

void var_squotes(t_list **list)
{
  (void)list;
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

char **var_split(char *str)
{
  char **list;
  int i;
  int c;
  int end;

  end = 0;
  c = count_words(str);
  list = (char **)malloc(sizeof(char *) * (c + 1));
  i = 0;
  c = 0;
  while(str[i])
  {
    get_words(&i, &end, str);
    if(str[i] == '\0')
      break;
    list[c++] = ft_substr(str, i, end - i);
    i = end;
  }
  list[c] = NULL;
  return(list);
}

int var_quotes(char **env, t_list **list, int d)
{
  char **array;
  t_list *n_list;
  t_list *tmp;
  t_list *back;

  n_list = NULL;
  if(var_dquotes(env, list, d))
    return(1);
  if((*list)->content[0] != '\0')
  {
    array = var_split((*list)->content);
    creat_linked_list(&n_list, array, 0);
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

  i = 0;
  while((*list)->content[i])
  {
    if((*list)->content[i] == '"')
    {
      while((*list)->content[++i] && (*list)->content[i] != '$')
      {
        if((*list)->content[i] == '"')
          break;
      }
      if((*list)->content[i] == '$')
      {
        if(var_dquotes(env, list, d))
          return(1);
        break;
      }
    }
    else if((*list)->content[i] == '\'')
    {
      while((*list)->content[++i] && (*list)->content[i] != '$')
      {
        if((*list)->content[i] == '\'')
          break;
      }
      if((*list)->content[i] == '$')
      {
        var_squotes(list);
        break;
      }
    }
    else if((*list)->content[i] == '$')
    {
      if(var_quotes(env, list, d))
        return(1);
      break;
    }
    i++;
  }
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

int check_expander(char **env, t_list **list)
{
  t_list *tmp;
  int i;

  tmp = NULL;
  i = -1;
  while(*list)
  {
    i = check_d((*list)->content, -1);
    while((*list)->content[i])
    {
      if(expander(env, list, i))
      {
        (*list)->back->i = 2;
        break;
      }
      token_type(*list);
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

void set_var(t_list *list, char ***env, char ***xenv)
{
  char *var;
  char *value;
  int len;
  int s;
  char q;
  char *new_var;
  char **n_env;
  char **n_xenv;

  len = 0;
  s = 0;
  while(list->content[len] && list->content[len] != '=')
    len++;
  var = ft_substr(list->content, 0, len);
  s = len;
  if(list->content[len] != '\0')
    len++;
  if(list->content[len] && (list->content[len] == '"' || list->content[len] == '\''))
  {
    q = list->content[len];
    s = len++;
    while(list->content[len] != q)
      len++;
  }
  else
    while(list->content[len++]);
  value = ft_substr(list->content, s + 1, len - (s + 1));
  s = 0;
  while(*env != NULL && (*env)[s] != NULL)
  {
    if(!ft_strncmp((*env)[s], var, ft_strlen(var)) && ((*env)[s][ft_strlen(var)] == '=' || (*env)[s][ft_strlen(var)] == '\0'))
    {
      new_var = (char *)malloc(sizeof(char) * (ft_strlen(var) + ft_strlen(value) + 2));
      new_var[0] = '\0';
      ft_cpy(new_var, var);
      ft_cpy(new_var, "=");
      ft_cpy(new_var, value);
      free((*env)[s]);
      free((*xenv)[s]);
      (*xenv)[s] = new_var;
      (*env)[s] = new_var;
      return;
    }
    s++;
  }
  new_var = (char *)malloc(sizeof(char) * (ft_strlen(var) + ft_strlen(value) + 2));
  new_var[0] = '\0';
  ft_cpy(new_var, var);
  if(list->content[ft_strlen(var)] != '\0')
  ft_cpy(new_var, "=");
  ft_cpy(new_var, value);
  n_env = (char **)malloc(sizeof(char *) * (s + 2));
  if(value == NULL)
    n_xenv = (char **)malloc(sizeof(char *) * s);
  else
    n_xenv = (char **)malloc(sizeof(char *) * (s + 2));
  len = 0;
  while(*env && (*env)[len])
  {
    n_env[len] = ft_substr((*env)[len], 0, ft_strlen((*env)[len]));
    n_xenv[len] = ft_substr((*env)[len], 0, ft_strlen((*env)[len]));
    free((*env)[len]);
    free((*xenv)[len]);
    len ++;
  }
  n_env[len] = new_var;
  n_env[++len] = NULL;
  n_xenv[len] = NULL;
  if(value != NULL)
  {
    n_xenv[len] = new_var;
    n_xenv[++len] = NULL;
  }
  free(*env);
  free(*xenv);
  *env = n_env;
  *xenv = n_xenv;
}

void check_var(t_list *list, char ***env, char ***xenv)
{
  int i;

  while(list)
  {
    i = -1;
    //while(list->content[++i])
    //{
    //  if(list->content[i] == '=')
    //  {
    //    if(list->back == NULL && list->next == NULL)
    //    {
    //      list->type = SET_VAR;
    //      set_var(list, xenv);
    //    }
    //    else if(list->back->back == NULL && !ft_strncmp(list->back->content, "export", 6) && list->back->content[6] == '\0' && list->next == NULL)
    //    {
    //      list->type = SET_VAR;
    //      set_var(list, env);
    //    }
    //    break;
    //  }
    //}
    if(list->back != NULL && list->back->back == NULL && !ft_strncmp(list->back->content, "export", 6) && list->back->content[6] == '\0' && list->next == NULL)
    {
      list->type = SET_VAR;
      set_var(list, env, xenv);
    }
    list = list->next;
  }
}

void remove_quotes(t_list *list)
{
  int j;
  char q;

  while(list)
  {
    j = -1;
    while(list->content[++j])
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

t_tree *creat_tree(t_list *list)
{
  t_tree *root;
  t_tree *n_node;
  t_tree *l_node;

  l_node = NULL;
  n_node = NULL;
  root = NULL;
  while(list)
  {
    if(list->content[0] == 41 || list->content[0] == 40)
      return(root);
    n_node = create_tree_node(list);
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
      
      l_node = creat_tree(list->next);
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
    list = list->next;
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
  printf("%s  (%d)\n",root->content->content,root->content->in);
  child = root->first_child;
  while(child)
  {
    print_tree(child, spaces + 2);
    child = child->next_sibling;
  }
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

  i = -1;
  s = env_size(envp);
  env = (char **)malloc(sizeof(char *) * (s + 1));
  while(envp[++i])
    env[i] = ft_substr(envp[i], 0, ft_strlen(envp[i]));
  env[i] = NULL;
  return(env);
}

void export(char **env)
{
  int i = -1;

  while(env[++i])
    printf("%s\n",env[i]);
}

char **unset(char **env, char *str)
{
  int s;
  char **new_env;
  int size;
  int i;

  size = env_size(env);
  new_env = NULL;
  s = 0;
  i = 0;
  while(*env != NULL && env[s] != NULL)
  {
    if(!ft_strncmp(env[s], str, ft_strlen(str)))
    {
      new_env = (char **)malloc(sizeof(char *) * size);
      size = 0;
      while(*env && env[size + i])
      {
        if(size == s)
        {
          free(env[s]);
          i = 1;
        }
        else
        {
          new_env[size] = ft_substr(env[size + i], 0, ft_strlen(env[size + i]));
          free(env[size + i]);
          size++;
        }
      }
      free(env);
      new_env[size] = NULL;
      break;
    }
    s++;
  }
  return(new_env);
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

int open_file(char *redfile, t_list *delimiter)
{
  int fd;
  char *line;
  pid_t pid;
  int status;

  fd = open(redfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
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
    signal(SIGINT, SIG_DFL);
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
      write(fd, line, ft_strlen(line));
      write(fd, "\n", 1);
      free(line);
    }
    free(line);
    close(fd);
    exit(0);
  }
  else
  {
    waitpid(pid, &status, 0);
    if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
    {
      close(fd);
      clean_heredoc(&redfile, 1);
      return (1);
    }
  }
  return (0);
}

//  cat  grep awk  sed  sort  uniq  tr  wc  tee  tail  head  dd bc python 
int check_command_type(char *content)
{
  if(!ft_strncmp(content, "cat", 3) || !ft_strncmp(content, "grep", 4) || \
  !ft_strncmp(content, "awk", 3) || !ft_strncmp(content, "sed", 3) || \
  !ft_strncmp(content, "sort", 4) || !ft_strncmp(content, "uniq", 4) || \
  !ft_strncmp(content, "tr", 2) || !ft_strncmp(content, "wc", 2) || \
  !ft_strncmp(content, "tee", 3) || !ft_strncmp(content, "tail", 4) || \
  !ft_strncmp(content, "head", 4) || !ft_strncmp(content, "dd", 2) || \
  !ft_strncmp(content, "bc", 2) || !ft_strncmp(content, "python", 6))
    return(1);
  return(0);
}

void implementing_heredoc(t_list **list, char **redfile)
{
  t_list *back;
  t_list *next;
  t_list *tmp;
  int i;

  i = -1;
  next = NULL;
  while(*list)
  {
    if((*list)->type == HEREDOC)
    {
      back = (*list)->back;
      while(back && back->type != COMMAND)
        back = back->back;
      next = (*list)->next->next;
      if(back && check_command_type(back->content))
      {
        while(back && back->next->type != HEREDOC)
          back = back->next;
        back->next = NULL;
        ft_lstadd_back(&back, ft_lstnew("<"));
        back = back->next;
        back->type = INPUT;
        ft_lstadd_back(&back, ft_lstnew(redfile[++i]));
        back = back->next;
        back->type = OPTIONS;
        tmp = *list;
        while(*list != next)
        {
          *list = (*list)->next;
          free(tmp->content);
          free(tmp);
          tmp = *list;
        }
        back->next = *list;
        if((*list) != NULL)
          (*list)->back = back;
        else
          *list = back;
        *list = (*list)->back;
      }
      else
      {
        while(back && back->next->type != HEREDOC)
          back = back->next;
        if(back != NULL)
          back->next = NULL;
        tmp = *list;
        while(*list != next)
        {
          *list = (*list)->next;
          free(tmp->content);
          free(tmp);
          tmp = *list;
        }
        if(back != NULL)
          back->next = *list;
        if((*list) != NULL)
          (*list)->back = back;
        else
          *list = back;
        if((*list)->back != NULL)
          *list = (*list)->back;
      }
    }
    if(*list && (*list)->next == NULL)
      break;
    if(*list != NULL)
      *list = (*list)->next;
  }
  while(*list && (*list)->back)
    *list = (*list)->back;
}

char **heredoc(t_list **list, int size)
{
  char **redfile;
  int i;
  char *nbr;
  int j;
  t_list *delimiter;

  delimiter = *list;
  i = -1;
  redfile = (char **)malloc(sizeof(char *) * (size + 1));
  while(++i < size)
  {
    redfile[i] = (char *)malloc(sizeof(char) * 16);
    redfile[i] = ft_strcpy(redfile[i], "/tmp/.redfile");
    nbr = ft_itoa(i);
    j = 12;
    while(*nbr)
    {
      redfile[i][++j] = *nbr;
      nbr++;
    }
    redfile[i][++j] = '\0';
  }
  redfile[i] = NULL;
  i = -1;
  while(delimiter)
  {
    if(delimiter->type == HEREDOC)
    {
      if(open_file(redfile[++i], delimiter->next))
        return(NULL);
    }
    delimiter = delimiter->next;
  }
  implementing_heredoc(list, redfile);
  return(redfile);
}


int check_Wildcards(t_list *list)
{
  int i;

  while(list)
  {
    i = -1;
    while(list->content[++i])
    {
      if(list->content[i] == '*')
        return(1);
    }
    list = list->next;
  }
  return(0);
}

int implementing_Wildcards(char *wc, const char *filename)
{
  char *str;
  int i;
  int len;
  int s;

  len = 0;
  i = 0;
  str = NULL;
  while(wc[len])
  {
    s = len;
    while(wc[len] != '*')
      len++;
    str = ft_substr(wc, s, len - s);
    if(str != NULL)
    {
      i = ft_strnstr(&filename[i], str, ft_strlen(filename));
      if(i == 0)
      {
        free(str);
        return(1);
      }
    }
    while(wc[len] == '*')
      len++;
    if(wc[len] == '\0')
      while(filename[i++]);
  }
  if(filename[i] == '\0')
    return(0);
  return(1);
}

void Wildcards_linked_list(t_list **list, char *str)
{
  t_list *next;

  next = (*list)->next;
  (*list)->next = NULL;
  ft_lstadd_back(list, ft_lstnew(str));
  *list = (*list)->next;
  (*list)->next = next;
}

int wildcards(t_list **list)
{
  struct dirent *entry;
  DIR *dir;
  int i;
  int d;

  d = 0;
  dir = opendir(".");
  if (dir == NULL)
    return 1;
  while(*list)
  {
    i = -1;
    while((*list)->content[++i])
    {
      if((*list)->content[i] == '*')
      {
        entry = readdir(dir);
        while(entry != NULL)
        {
          if(!implementing_Wildcards((*list)->content, entry->d_name))
          {
            Wildcards_linked_list(list, entry->d_name);
            *list = (*list)->next;
            d++;
          }
          entry = readdir(dir);
        }
      }
    }
    *list = (*list)->next;
  }
  closedir(dir);
  if(d == 0)
    return(1);
  return(0);
}

