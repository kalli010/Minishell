#include <minishell.h>

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
          if(list->back->type != COMMAND && list->back->type != OPTIONS)
            list->type = PATH_COMMAND;
        }
        else if(list->back == NULL)
          list->type = PATH_COMMAND;
        else
          list->type = PATH;
      }
  else
    list->type = COMMAND;
}
