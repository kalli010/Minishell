#include <minishell.h>


int check_Wildcards(t_list *list)
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






int implementing_Wildcards(char *wc, const char *filename)
{
  char *str;
  int i;
  int len;
  int s;
  int pos;

  i = 0;
  len = 0;
  while (wc[len])
  {
    s = len;
    while (wc[len] != '*' && wc[len] != '\0')
        len++;
    str = ft_substr(wc, s, len - s);
    if (str != NULL)
    {
      pos = ft_strnstr(&filename[i], str, ft_strlen(&filename[i]));
      if (pos == 0)
      {
        free(str);
        return 1;
      }
      i += pos;
    }
    free(str);
    while (wc[len] == '*')
      len++;
    if (wc[len] == '\0')
    {
      if(filename[i] == '\0')
        return(0);
      else
        return(1);
    }
  }
  if(filename[i] == '\0')
    return(0);
  else
    return(1);
}

void Wildcards_linked_list(t_list *list, char *str)
{
  t_list *next;

  next = list->next;
  list->next = NULL;
  ft_lstadd_back(&list, ft_lstnew(str));
  list = list->next;
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

  dir = opendir(".");
  if (dir == NULL)
    return 1;
  while (list)
  {
    i = -1;
    while (list->content[++i])
    {
      if (list->content[i] == '*')
      {
        d = 0;
        rewinddir(dir);
        while ((entry = readdir(dir)) != NULL)
        {
          if (!implementing_Wildcards(list->content, entry->d_name))
          {
            Wildcards_linked_list(list, entry->d_name);
            d++;
          }
        }
        if (d != 0)
          clean_wildcards(list);
        break;
      }
    }
    list = list->next;
  }
  closedir(dir);
  return 0;
}
