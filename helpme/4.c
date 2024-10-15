#include <minishell.h>

int check_red_with_cmd(void)
{
  while(g_helper.list)
  {
    if(g_helper.list->type == INPUT || g_helper.list->type == OUTPUT || g_helper.list->type == APPEND)
    {
      if(g_helper.list->next != NULL && g_helper.list->next->next != NULL && (g_helper.list->next->next->type == COMMAND || g_helper.list->next->next->type == OPTIONS))
        return(1);
    }
    g_helper.list = g_helper.list->next;
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
