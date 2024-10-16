#include <minishell.h>

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
