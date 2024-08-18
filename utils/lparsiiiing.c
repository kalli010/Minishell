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

int check_command(char **str)
{
  int i;
  char *path;
  char *dest;
  int j;

  dest = NULL;
  if(*str == NULL)
    return(-1);
  j = -1;
  while(str[++j])
  {
    i = 0;
    if(str[j][0] == '"')
    {
      if(str[j][1] == '$')
        return(0);
      i++;
      while(str[j][i] != '"')
        i++;
      ft_strlcpy(&dest,&str[j][1],i);
      path = ft_strjoin("/usr/bin/",dest);
      if(!(access(path, F_OK)))
      {
        free(path);
        free(dest);
        return(j);
      }
      free(path);
      free(dest);
    }
  }
  return(-1);
}

void remove_quotes(char *tokens)
{
  int j;
  char q;

  j = -1;
  while(tokens[++j])
  {
    if(tokens[j] == '"')
    {
      q = tokens[j];
      tokens[j] = tokens[j + 1];
      while(tokens[j + 1] != q)
      {
        tokens[j] = tokens[j + 1];
        j++;
      }
      j++;
      while(tokens[++j])
        tokens[j - 2] = tokens[j];
      tokens[j - 2] = '\0';
      j = -1;
    }
  }
}

char **tokenizer(char *str)
{
  char **tokens;
  int tc;
  int i;

  tc = token_count(str);
  tokens = (char **)malloc(sizeof(char *) * (tc + 1));
  create_tokens(str, tokens);
  i = check_command(tokens);
  while(i != -1)
  {
    remove_quotes(tokens[i]);
    i = check_command(tokens);
  }
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
  else if(list->content[0] == '-' || ft_strncmp(list->content, "--", 2) == 0\
    || (list->back != NULL && \
      (list->back->type == COMMAND || list->back->type == OPTIONS)))
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
    path = ft_strjoin("/usr/bin/",list->content);
    if(!access(path, F_OK))
        list->type = COMMAND;
    
    else
        list->type = COMMAND;
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
        && list->back->type != VAR && list->back->type != PATH)
      {
        printf("9\n");
        printf("syntax error\n");
        return(1);
      }
      else if((list->type == list->back->type) && \
        (list->type != WORD && list->type != OPTIONS))
      {
        printf("8\n");
        printf("syntax error\n");
        return(1);
      }
      else if((list->content[0] == '<' && list->back->content[0] == '>') && \
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
      else if(list->content[0] == '<' && list->back->content[0] == '<' && \
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

t_tree *create_tree_node(t_list *list)
{
  t_tree *n_node;

  n_node = (t_tree *)malloc(sizeof(t_tree));
  if(!n_node)
    return (NULL);
  n_node->content = list;
  n_node->first_child = NULL;
  n_node->next_sibling = NULL;
  n_node->i = 0;
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
      p++;
    node = node->next;
  }
  while(list)
  {
    if(list->content[0] == 41)
      p--;
    list = list->next;
  }
  return(p);
}

t_tree *creat_tree_with_parenthesis(t_list *list)
{
  t_tree *root;
  t_tree *s_tree;
  t_tree *l_node;
  t_tree *r_tree;
  int i;

  r_tree = NULL;
  l_node = NULL;
  s_tree = NULL;
  root = NULL;
  i = 0;
  while(list)
  {
    if(list->content[0] == 41)
    {
      list = list->next;
      i++;
    }
    if(list != NULL && (list->content[0] == 40 || i < 0))
    {
      if(list->content[0] == 40)
      {
        list = list->next;
        i--;
      }
      s_tree = creat_tree(list);
      while(list->content[0] != 41)
      {
        if(list->content[0] == 40)
          break;
        list = list->next;
      }
    }
    if(i < 0)
    {
      if(r_tree == NULL)
        r_tree = s_tree;
      else if(s_tree != NULL && s_tree->first_child != NULL &&\
          s_tree->first_child->next_sibling == NULL)
      {
        add_sibling_to_child(r_tree, s_tree->first_child);
        s_tree->first_child = r_tree;
        r_tree = s_tree;
      }
      else if(s_tree != NULL && s_tree->first_child != NULL &&\
          s_tree->first_child->next_sibling != NULL)
        add_child_to_tree(r_tree, s_tree);
      else if(s_tree != NULL)
      {
        add_child_to_tree(s_tree, r_tree);
        r_tree = s_tree;
      }
      
    }
    else
    {
      if(list == NULL)
        add_child_to_tree(root, r_tree);
      else
      {
        if(root != NULL)
          add_child_to_tree(root, r_tree);
        l_node = creat_tree(list);
        if(root == NULL)
        {
          if(l_node != NULL && r_tree != NULL)
          {
            add_sibling_to_child(r_tree, l_node->first_child);
            l_node->first_child = r_tree;
          }
          root = l_node;
        }
        else
        {
          add_sibling_to_child(root, l_node->first_child);
          l_node->first_child = root;
          root = l_node;
        }
        while(list != NULL && list->content[0] != 40)
          list = list->next;
        r_tree = NULL;
      }
    }
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
        while(l_node->first_child->first_child->first_child != NULL)
          l_node = l_node->first_child;
        add_child_to_tree(n_node, l_node->first_child);
        add_sibling_to_child(n_node, l_node->first_child->next_sibling);
        l_node->first_child->next_sibling->next_sibling = NULL;
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
