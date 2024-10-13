#include <minishell.h>

int open_file(char *redfile, t_list *delimiter, char **env, char **xenv, t_list *list, char ***rf)
{
  int fd;
  char *line;
  pid_t pid;
  int status;
  int d;
  int i;

  i = 0;
  d = -1;
  if(!check_quotes(delimiter->content))
    i = 1;
  remove_quotes_string(delimiter->content);
  fd = open(redfile, O_CREAT | O_WRONLY, 0644);
  if (fd < 0)
  {
    printf("Error creating redfile\n");
    return (1);
  }
  pid = fork();
  if (pid == -1)
  {
    printf("Fork failed");
    close(fd);
    return (1);
  }
  else if (pid == 0)
  {
    signal(SIGINT, sigint_handler);
    while (1)
    {
      line = readline("> ");
      if (!line)
      {
          printf("Error: (Ctrl+D)\n");
          break;
      }
      if (delimiter->content[0] == '\0')
      {
          if (line[0] == '\0')
              break;
      }
      else if (!ft_strncmp(line, delimiter->content, ft_strlen(delimiter->content)))
          break;
      if(i == 1)
      {
        d = check_d(line, -1);
        while(line[d])
        {
          if(expand_line(env, &line, d))
          {
            close(fd);
            free_list(list);
            i = -1;
            while((*rf)[++i])
              free((*rf)[i]);
            free(*rf);
            clean_env(env);
            clean_env(xenv);
            exit(1);
          }
          else
            d = check_d(line, d);
        }
      }
      write(fd, line, ft_strlen(line));
      write(fd, "\n", 1);
      free(line);
    }
    free(line);
    close(fd);
    free_list(list);
    i = -1;
    while((*rf)[++i])
      free((*rf)[i]);
    free(*rf);
    clean_env(env);
    clean_env(xenv);
    exit(0);
  }
  else
  {
    waitpid(pid, &status, 0);
    if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
    {
      printf("^C\n");
      close(fd);
      return (1);
    }
  }
  close(fd);
  return (0);
}

void implementing_heredoc(t_list **list, char ***redfile)
{
  t_list *back;
  t_list *next;
  t_list *tmp;
  int i;
  char *red;

  red = NULL;
  i = -1;
  next = NULL;
  while(*list)
  {
    if((*list)->type == HEREDOC)
    {
      back = (*list)->back;
      next = (*list)->next->next;
      i++;
      while(*list != next)
      {
        tmp = *list;
        *list = (*list)->next;
        if(tmp->content)
          free(tmp->content);
        free(tmp);
      }
      if(back != NULL)
        back->next = NULL;
      red = (char *)malloc(sizeof(char) * 2);
      red[0] = '<';
      red[1] = '\0';
      ft_lstadd_back(&back, ft_lstnew(red));
      if(back->next != NULL)
        back = back->next;
      back->type = INPUT;
      ft_lstadd_back(&back, ft_lstnew((*redfile)[i]));
      back = back->next;
      back->type = PATH;
      if(back != NULL)
        back->next = *list;
      if((*list) != NULL)
        (*list)->back = back;
      else
        *list = back;
      if(*list != NULL && (*list)->back != NULL)
        *list = (*list)->back;
    }
    if(*list && (*list)->next == NULL)
      break;
    if(*list != NULL)
      *list = (*list)->next;
  }
  while(*list && (*list)->back)
    *list = (*list)->back;
}

int heredoc(t_list **list, int size, char **env, char **xenv, char ***rf)
{
  int i;
  char *nbr;
  int j;
  t_list *delimiter;
  int n;

  delimiter = *list;
  i = -1;
  *rf = (char **)malloc(sizeof(char *) * (size + 1));
  while(++i < size)
  {
    (*rf)[i] = (char *)malloc(sizeof(char) * 16);
    (*rf)[i][0] = '\0';
    ft_cpy((*rf)[i], "/tmp/.redfile");
    nbr = ft_itoa(i);
    j = 12;
    n = -1;
    while(nbr[++n])
      (*rf)[i][++j] = nbr[n];
    (*rf)[i][++j] = '\0';
    free(nbr);
  }
  (*rf)[i] = NULL;
  i = -1;
  while(delimiter)
  {
    if(delimiter->type == HEREDOC)
    {
      if(open_file((*rf)[++i], delimiter->next, env, xenv, *list, rf))
      {
        clean_heredoc(*rf, 1);
        return(1);
      }
    }
    delimiter = delimiter->next;
  }
  implementing_heredoc(list, rf);
  return(0);
}
