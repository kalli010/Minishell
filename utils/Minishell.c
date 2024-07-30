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
      while(str[i] != ' ' && str[i++] != '\0');
      if(!ft_strncmp(&str[j], "echo", i - j))
        return(1);
      else 
        return(0);
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
        if(str[i] == '|' || str[i] == '<' || str[i] == '>')
        {
          while(str[i] != '\0' && str[i] != ' ')
            i++;
        }
        else
        {
          while(str[i] != '\0' && str[i] != '|' && str[i] != '<' && str[i] != '>')
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
      if(str[i] == '|' || str[i] == '<' || str[i] == '>')
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

  c = 0;
  i = -1;
  while(str[++i])
  {
    if(str[i] != ' ')
    {
      c++;
      while(str[i] != '\0' && str[i] != ' ')
      {
        if(str[i] == 34 || str[i] == 39)
        {
          q = str[i];
          while(str[++i] != q);
        }
        i++;
      }
      if(str[i] == '\0')
        i--;
    }
  }
  return(c);
}

void echo_create_tokens(char *str, char **tokens)
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
      if(j == 0)
        while(str[i] != '\0' && str[i] != ' ')
          i++;
      else
      {
        if(str[i] == '|' || str[i] == '<' || str[i] == '>')
        {
          while(str[i] != '\0' && str[i] != ' ')
            i++;
        }
        else
        {
          while(str[i] != '\0' && str[i] != '|' && str[i] != '<' && str[i] != '>' )
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
      tokens[j] = ft_substr(str, s, i - s);
      j++;
      if(str[i] == '|' || str[i] == '<' || str[i] == '>')
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
  if(echo_check(str))
    echo_create_tokens(str, tokens);
  else 
  {
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
        tokens[j] = ft_substr(str, s, i - s);
        j++;
        if(str[i] == '\0')
          i--;
      }
    }
    tokens[j] = NULL;
  }
}

void remove_quotes(char **tokens)
{
  //int i;
  int j;
  char q;

  //i = -1;
  //while(tokens[++i])
  //{
    j = -1;
    while(tokens[0][++j])
    {
      if(tokens[0][j] == '"' /*|| tokens[0][j] == 39*/)
      {
        q = tokens[0][j];
        tokens[0][j] = tokens[0][j + 1];
        while(tokens[0][j + 1] != q)
        {
          tokens[0][j] = tokens[0][j + 1];
          j++;
        }
        j++;
        while(tokens[0][++j])
          tokens[0][j - 2] = tokens[0][j];
        tokens[0][j - 2] = '\0';
        j = -1;
      }
    }
  //}
}

int check_command(char *str)
{
  int i;
  char *path;
  char *dest;

  i = 0;
  dest = NULL;
  if(!str)
    return(0);
  if(str[0] == '"')
  {
    if(str[1] == '$')
      return(0);
    while(str[++i] != '"');
    ft_strlcpy(&dest,&str[1],i);
    path = ft_strjoin("/usr/bin/",dest);
    if(!(access(path, F_OK)))
    {
      free(path);
      free(dest);
      return(1);
    }
    free(path);
    free(dest);
  }
  return(0);
}

char **tokenizer(char *str)
{
  char **tokens;
  int tc;

  if(echo_check(str))
    tc = echo_token_count(str);
  else
    tc = token_count(str);
  tokens = (char **)malloc(sizeof(char *) * (tc + 1));
  create_tokens(str, tokens);
  if(check_command(tokens[0]))
    remove_quotes(tokens);
  
  return(tokens);
}

void token_type(t_list *list)
{
  char *path;

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
  else if(list->content[0] == '-' || ft_strncmp(list->content, "--", 2) == 0)
    list->type = OPTIONS;
  else if(list->content[0] == '/' || list->content[0] == '~' \
      || !ft_strncmp(list->content, "./", 2))
      list->type = PATH;
  else if(list->content[0] == '$')
     list->type = VAR;
  else
  {
    path = ft_strjoin("/usr/bin/",list->content);
    if(!access(path, F_OK))
        list->type = COMMAND;
    else
        list->type = WORD;
    free(path);
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

int symbols_check(t_list *list)
{
  if(list == NULL)
    return(0);
  if(list->type == PIPE)
  {
    printf("syntax error\n");
    return(1);
  }
  if(list->back == NULL)
    list = list->next;
  if(list == NULL)
    return(0);
  while(list->next != NULL)
  {
    if(list->type == PIPE && list->back->type != WORD \
      && list->back->type != COMMAND && list->back->type != OPTIONS \
      && list->back->type != VAR && list->back->type != PATH)
    {
      printf("syntax error\n");
      return(1);
    }
    else if((list->type == list->back->type) && \
      (list->type != WORD && list->type != OPTIONS))
    {
      printf("syntax error\n");
      return(1);
    }
    else if((list->content[0] == '<' && list->back->content[0] == '>') && \
      (list->type == INPUT || list->type == HEREDOC) &&\
      (list->back->type == OUTPUT || list->back->type == APPEND))
    {
      printf("syntax error\n");
      return(1);
    }
    else if((list->content[0] == '>' && list->back->content[0] == '<') && \
      (list->type == OUTPUT || list->type == APPEND) &&\
      (list->back->type == INPUT || list->back->type == HEREDOC))
    {
      printf("syntax error\n");
      return(1);
    }
    else if(list->content[0] == '|' && list->back->content[0] == '|' && \
      (list->type == OR || list->type == PIPE) &&\
      (list->back->type == OR || list->back->type == PIPE))
    {
      printf("syntax error\n");
      return(1);
    }
    else if(list->content[0] == '<' && list->back->content[0] == '<' && \
      (list->type == INPUT || list->type == HEREDOC) &&\
      (list->back->type == INPUT || list->back->type == HEREDOC))
    {
      printf("syntax error\n");
      return(1);
    }
    else if(list->content[0] == '>' && list->back->content[0] == '>' && \
      (list->type == OUTPUT || list->type == APPEND) &&\
      (list->back->type == OUTPUT || list->back->type == APPEND))
    {
      printf("syntax error\n");
      return(1);
    }
    else if(list->type == HEREDOC && list->back->type == PIPE)
    {
      printf("syntax error\n");
      return(1);
    }
    list = list->next;
  }
  if(list->type != WORD && list->type != OPTIONS \
      && list->type != COMMAND && list->type != OPTIONS \
      && list->type != VAR && list->type != PATH)
  {
      printf("syntax error\n");
      return(1);
  } 
  return(0);
}

void add_child_to_tree(t_tree *parent, t_tree *child)
{
  t_tree *bro;

  if(parent->first_child == NULL)
    parent->first_child = child;
  else
  {
    bro = parent->first_child;
    while(bro->next_brother != NULL)
      bro = bro->next_brother;
    bro->next_brother = child;
  }
}

t_tree *create_tree_node(t_list *list)
{
  t_tree *tree_node;

  tree_node = (t_tree *)malloc(sizeof(t_tree));
  if(!tree_node)
    return (NULL);
  tree_node->content = list;
  tree_node->first_child = NULL;
  tree_node->next_brother = NULL;
  return(tree_node);
}

void add_brother_to_child(t_tree *child, t_tree *bro)
{
  t_tree *l_bro;

  if(child->next_brother == NULL)
    child->next_brother = bro;
  else {
    l_bro = child->next_brother;
    while(l_bro->next_brother != NULL)
      l_bro = l_bro->next_brother;
    l_bro->next_brother = child;
  }
}

t_tree *creat_tree(t_list *list)
{
  t_tree *root;
  t_tree *n_node;
  t_tree *last_node;

  root = NULL;
  while(list)
  {
    n_node = create_tree_node(list);
    if(root == NULL)
      root = n_node;
     else if(list->type == PIPE || list->type == OR \
        || list->type == AND ||  list->type == OUTPUT \
        ||  list->type == INPUT ||  list->type == HEREDOC \
        ||  list->type == APPEND)
    {
      add_child_to_tree(n_node, root);
      root = n_node;
    }
    else
    {
      if(last_node->content->type != COMMAND && root != last_node)
        add_brother_to_child(last_node, n_node);
      else
        add_child_to_tree(last_node, n_node);
    }
    last_node = n_node;
    list = list->next;
  }
  return(root);
}

void print_tree(t_tree *node, int d)
{
  int i = 0;
  t_tree *child;

  while(i < d)
  {
    printf("  ");
    i++;
  }
  printf("%s\n", node->content->content);
  child = node->first_child;
  while (child != NULL)
  {
    print_tree(child, d + 1);
    child = child->next_brother;
  }
}

void ft_minishell(char *line)
{
  t_list *list;
  char **tokens;
  char *cmd;
  t_tree *root;

  list = NULL;
  if(quotes_check(line))
      return;
  cmd = split_symbols(line);
  free(line);
  tokens = tokenizer(cmd);
  creat_linked_list(&list, tokens);
  if (symbols_check(list))
    return;
  root = creat_tree(list);
  print_tree(root,0);
  return;
}

int main()
{
  char *line;

  while(1)
  {
    line = readline("minishell -> ");
    if(line)
      ft_minishell(line); 
  }
  return(0);
}
