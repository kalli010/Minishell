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
  while(list->next != NULL)
    list = list->next;
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
  else if(list->content[0] == '-' || ft_strncmp(list->content, "--", 2) == 0\
    || (list->back != NULL && \
      (list->back->type == COMMAND || list->back->type == OPTIONS \
      || list->back->type == PATH_COMMAND)))
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
      && (list->back->type == OUTPUT || list->back->type == APPEND ||\
  list->back->type == INPUT))
      list->type = PATH;
  else if(list->content[0] == '$')
     list->type = VAR;
  else if(list->back != NULL && list->back->type == HEREDOC)
    list->type = DELIMITER;
  else
  {
    //path = ft_strjoin("/usr/bin/",list->content);
    //if(!access(path, F_OK))
    //    list->type = COMMAND;
    //else
        list->type = COMMAND;
    //free(path);
  }
}

void creat_linked_list(t_list **list, char **tokens)
{
  int i;

  i = -1;
  while(tokens[++i])
  {
    ft_lstadd_back(list, ft_lstnew(tokens[i]));
    token_type(*list);
  }
  free(tokens);
}

int check_red(t_list *list)
{
  while(list)
  {
    if(list->type == OUTPUT || list->type == INPUT)
      return(1);
    list = list->next;
  }
  return(0);
}

void create_list_with_red(t_list **list)
{
  t_list *tmp;
  t_list *start;
  t_list *node;

  tmp = *list;
  while(tmp)
  {
    if(tmp->type == OUTPUT || tmp->type == INPUT)
    {
      start = tmp;
      while(tmp->next != NULL && (tmp->next->type == start->type\
        || tmp->next->type == PATH))
        tmp = tmp->next;
      if(tmp->next->type == COMMAND)
      {
        if(start->next != tmp)
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

int check_string_start(t_list *list)
{
  while(list)
  {
    if(list->type == INPUT || list->type == OUTPUT || list->type == HEREDOC || list->type == APPEND)
    {
      if(list->next != NULL && list->next->next != NULL && list->next->next->type == COMMAND)
        return(1);
    }
    list = list->next;
  }
  return(0);
}

void recreat_linked_list(t_list **list)
{
  t_list *start;
  t_list *end;
  t_list *tmp;
  t_list *n_list;
  t_list **n_while;
  t_list *new_linked_list;

  n_while = list;
  new_linked_list = *n_while;
  while(n_while)
  {
    n_list = *n_while;
    tmp = *n_while;
    start =(*n_while)->next->next;
    while(start != NULL && (start->type == tmp->type && start->type == PATH))
      start = start->next;
    if(start != NULL && start->type == COMMAND)
    {
      end = start->next;
      while(end != NULL && end->type == OPTIONS)
        end = end->next;
      
      while(tmp->next != start)
        tmp = tmp->next;
      tmp->next = end;
      if(end != NULL)
        end->back = tmp;
      
      start->back = (*n_while)->back;
      n_list = *n_while;
      if((*n_while)->back != NULL)
        (*n_while)->back->next = start;
      *n_while = n_list;
      n_list = start;
      while(start != NULL && start->next != end)
        start = start->next;
      if(start != NULL)
        start->next = *n_while;
      (*n_while)->back = start;
      if(start->back == NULL)
        *n_while = n_list;
      if(end != NULL && (end->type == INPUT || end->type == OUTPUT || end->type == HEREDOC || end->type == APPEND))
      {
        while(*n_while != end)
          n_while = &((*n_while)->next);
      }
      else 
        n_while = NULL;
    }
    else {
      if(start->type == INPUT || start->type == OUTPUT || start->type == HEREDOC || start->type == APPEND)
      {
        while(*n_while != start)
          n_while = &((*n_while)->next);
      }
      else {
        n_while = NULL;
      }
    }
  }
  *list = new_linked_list;
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
        && list->back->type != DELIMITER)
      {
        printf("9\n");
        printf("syntax error\n");
        return(1);
      }
      else if(list->back != NULL && (list->type == list->back->type) && \
        (list->type != WORD && list->type != OPTIONS))
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
      && list->type != DELIMITER)
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
  while(env[++s])
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

void var_dquotes(char **env, t_list **list)
{
  char *fstr;
  char *sstr;
  char *tstr;
  char *var;
  int len;
  int s;

  s = 0;
  len = 0;
  while((*list)->content[len] && (*list)->content[len] != '$')
    len++;
  fstr = ft_substr((*list)->content, 0, len);
  s = len;
  while((*list)->content[len] && (*list)->content[len] != '"')
    len++;
  sstr = ft_substr((*list)->content,s + 1, len - (s + 1));
  s = len;
  while((*list)->content[len])
    len++;
  tstr = ft_substr((*list)->content, s, len - s);
  if(sstr)
    var = ft_getenv(env, sstr);
  else {
    var = "";
  }
  free(sstr);
  free((*list)->content);
  (*list)->content = get_new_list(fstr, var, tstr);
  free(fstr);
  free(tstr);
}

void var_squotes(t_list **list)
{
  (void)list;
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

void get_words(int *i, int *end, char *str)
{
  char q;

  while(str[*i] && str[*i] == ' ')
    (*i)++;
  *end = *i;
  while(str[*end] && str[*end] != ' ')
  {
    (*end)++;
    if(str[*end] == '"' || str[*end] == '\'')
    {
      q = str[*end];
      while(str[++(*end)] != q);
    }
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
  i = 0;
  list = (char **)malloc(sizeof(char *) * (c + 1));
  c = 0;
  while(str[i])
  {
    get_words(&i, &end, str);
    list[c++] = ft_substr(str, i, end - i);
    i = end;
  }
  list[c] = NULL;
  return(list);
}

void var_quotes(char **env, t_list **list)
{
  char **array;
  t_list *n_list;
  t_list *tmp;
  t_list *back;

  var_dquotes(env, list);
  array = var_split((*list)->content);
  creat_linked_list(&n_list, array);
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
  }
  else {
    (*list) = n_list;
  }
  ft_lstadd_back(list, tmp);
}

void expander(char **env, t_list **list)
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
        var_dquotes(env, list);
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
      var_quotes(env, list);
      break;
    }
    i++;
  }
}

void check_expander(char **env, t_list **list)
{
  int i;
  t_list *tmp;

  while(*list)
  {
    i = -1;
    while((*list)->content[++i])
    {
      if((*list)->content[i] == '$')
      {
        expander(env, list);
        break;
      }
    }
    tmp = *list;
    if(*list != NULL)
      (*list) = (*list)->next;
  }
  *list = tmp;
  while((*list) && (*list)->back != NULL)
    *list = (*list)->back;
}

void set_var(t_list *list, char **env)
{
  char *var;
  char *value;
  int len;
  int s;
  char q;
  char *new_var;

  len = 0;
  s = 0;
  while(list->content[len] != '=')
    len++;
  var = ft_substr(list->content, 0, len);
  s = len++;
  if(list->content[len] == '"' || list->content[len] == '\'')
  {
    q = list->content[len];
    s = len++;
    while(list->content[len] != q)
      len++;
  }
  else
    while(list->content[len++]);
  value = ft_substr(list->content, s + 1, len - (s + 1));
  s = -1;
  while(env[++s] != NULL)
  {
    if(!ft_strncmp(env[s], var, ft_strlen(var)) && env[s][ft_strlen(var)] == '=')
    {
      new_var = (char *)malloc(sizeof(char) * (ft_strlen(var) + ft_strlen(value) + 2));
      new_var[0] = '\0';
      ft_cpy(new_var, var);
      ft_cpy(new_var, "=");
      ft_cpy(new_var, value);
      free(env[s]);
      env[s] = new_var;
      return;
    }
  }
  new_var = (char *)malloc(sizeof(char) * (ft_strlen(var) + ft_strlen(value) + 2));
  new_var[0] = '\0';
  ft_cpy(new_var, var);
  ft_cpy(new_var, "=");
  ft_cpy(new_var, value);
  env[s] = new_var;
  env[s + 1] = NULL;
}

void check_var(t_list *list, char **env)
{
  int i;

  while(list)
  {
    i = -1;
    while(list->content[++i])
    {
      if(list->content[i] == '=')
      {
        if(list->back == NULL || \
          (list->back->type != COMMAND &&\
      list->back->type != OPTIONS &&\
      list->back->type != PATH &&\
      list->back->type != VAR &&\
      list->back->type != PATH_COMMAND))
        list->type = SET_VAR;
        set_var(list, env);
        break;
      }
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
      if(node->back != NULL && \
        ((node->back->type != PIPE && node->back->type != AND \
        && node->back->type != OR) \
        || node->next->type != COMMAND))
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
        ((list->back->type != COMMAND && list->back->type != OPTIONS)\
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
      root = l_node;
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
  printf("%s  (%d)\n",root->content->content,root->content->type);
  child = root->first_child;
  while(child)
  {
    print_tree(child, spaces + 2);
    child = child->next_sibling;
  }
}

void export(t_list *list, char **env)
{
  list = list->next;
  while(list || list->type != OPTIONS)
  {
    set_var(list, env);
    list = list->next;
  }
}
