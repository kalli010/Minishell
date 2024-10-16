#include <minishell.h>

int check_wildcards(t_list *list)
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

int ft_find(const char *filename, char *str, int flag)
{
  int i;
  int j;

  i = 0;
  j = 0;
  if(flag == 0)
  {
    while(str[i] == filename[i])
      i++;
    if(str[i] == '\0')
      return(i);
    else
      return(-1);
  }
  else if(flag == 1)
  {
    while(filename[i] && filename[i] != str[j])
      i++;
    while(str[j] && filename[i] && filename[i] == str[j])
    {
      i++;
      j++;
    }
    if(str[j] == '\0')
      return(i);
    else
      return(-1);
  }
  else
  {
    while(filename[i] && filename[i] != str[j])
      i++;
    while(filename[i] && str[j] && filename[i] == str[j])
    {
      i++;
      j++;
    }
    if(str[j] == '\0' && filename[i] == '\0')
      return(i);
    else
      return(-1);
  }
}

int implementing_wildcards(char *wc, const char *filename)
{
  char *str;
  int i;
  int len;
  int s;
  int flag;

  len = 0;
  flag = -1;
  if(filename != NULL && filename[0] == '.')
    return(1);
  i = -1;
  while(wc[++i] == '*')
  {
    if(wc[i] == '\0')
      return(0);
  }
  i = 0;
  while (wc[len])
  {
    s = len;
    while (wc[len] != '*' && wc[len] != '\0')
        len++;
    if(len != 0 && flag == -1)
      flag = 0;
    else if(wc[len] == '\0')
      flag = 2;
    else
      flag =1;
    str = ft_substr(wc, s, len - s);
    if (str != NULL)
    {
      i += ft_find(&filename[i], str, flag);
      if (i == -1)
      {
        free(str);
        return 1;
      }
    }
    free(str);
    while (wc[len] == '*')
     len++;
  }
  return(0);
}

t_list	*ft_lstnew_2(char *content)
{
	t_list	*a;

	a = malloc(sizeof(t_list));
	if (!a)
		return (NULL);
	a->content = ft_substr(content, 0, ft_strlen(content));
	a->next = NULL;
	a->back = NULL;
  a->i = 0;
  a->in = 0;
  return (a);
}

void wildcards_linked_list(t_list *list, char *str)
{
  t_list *next;

  next = list->next;
  list->next = NULL;
  ft_lstadd_back(&list, ft_lstnew_2(str));
  list = list->next;
  list->type = OPTIONS;
  if (list && next)
  {
    list->next = next;
    next->back = list;
  }
}

void clean_wildcards(t_list **list)
{
  t_list *back;
  t_list *next;

  back = (*list)->back;
  next = (*list)->next;
  next->type = COMMAND;
  free((*list)->content);
  free(*list);
  if(back)
  {
    back->next = next;
  }
  if(next)
  {
    next->back = back;
    if(back == NULL)
      *list = next;
    else
      *list = back;
  }
}

int wildcards(t_list **list)
{
  struct dirent *entry;
  DIR *dir;
  int d;
  int i;
  t_list *tmp;

  dir = opendir(".");
  if (dir == NULL)
    return 1;
  while (*list)
  {
    i = -1;
    while ((*list)->content[++i])
    {
      if ((*list)->content[i] == '*')
      {
        d = 0;
        rewinddir(dir);
        while ((entry = readdir(dir)) != NULL)
        {
          if (!implementing_wildcards((*list)->content, entry->d_name))
          {
            wildcards_linked_list(*list, entry->d_name);
            d++;
          }
        }
        if (d != 0)
        {
          clean_wildcards(list);
          tmp = *list;
          while(*list && d > 0)
          {
            *list = (*list)->next;
            d--;
          }
        }
        break;
      }
    }
    if(*list)
      *list = (*list)->next;
  }
  *list = tmp;
  while((*list)->back)
    *list = (*list)->back;
  closedir(dir);
  return 0;
}
