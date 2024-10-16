#include <minishell.h>

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
        && list->back->type != PATH \
        && list->back->type != SET_VAR && list->back->type != PATH_COMMAND \
        && list->back->type != DELIMITER && list->back->type != PARENTHESIS)
      {
        printf("9\n");
        printf("syntax error\n");
        return(1);
      }
      else if(list->type == PIPE && (list->next->type == AND || list->next->type == OR))
      {
        printf("11\n");
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
      && list->type != PATH \
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
