#include <minishell.h>

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