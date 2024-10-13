#include <minishell.h>



int clean_heredoc(char **redfile, int hd)
{
  int i;

  i = -1;
  while(redfile[++i] && hd-- > 0)
  {
    if (unlink(redfile[i]) < 0)
    {
      printf("Error deleting redfile\n");
      return(1);
    }
  }
  return(0);
}

int check_quotes(char *str)
{
  int i;

  i = -1;
  while(str[++i])
  {
    if(str[i] == '"' || str[i] == '\'')
      return(1);
  }
  return(0);
}

int expand_line(char **env, char **str, int d)
{
  char *fstr;
  char *sstr;
  char *tstr;
  char *var;
  int len;
  int s;

  s = 0;
  fstr = NULL;
  sstr = NULL;
  tstr = NULL;
  len = d;
  fstr = ft_substr((*str), s, len);
  s = len;
  if((*str)[len] == '$')
    len++;
  if((*str)[len] == '?')
    len++;
  else
  {
    while(ft_isalpha((*str)[len]) || ft_isdigit((*str)[len]) || (*str)[len] == '_')
      len++;
  }
  sstr = ft_substr((*str),s + 1, len - (s + 1));
  if(sstr != NULL && !ft_isalpha(sstr[0]) && sstr[0] != '_' && sstr[0] != '?')
  {
    free(fstr);
    free(sstr);
    return(1);
  }
  s = len;
  while((*str)[len])
    len++;
  tstr = ft_substr((*str), s, len - s);
  if(sstr)
  {
    if(sstr[0] == '?')
      var = ft_itoa(g_helper.exit_status);
    else
      var = ft_getenv(env, sstr);
  }
  else
    var = ft_getenv(env, sstr);
  free(sstr);
  free((*str));
  (*str) = get_new_list(fstr, var, tstr);
  free(fstr);
  free(tstr);
  free(var);
  return(0);
}

void clean_env(char **env)
{
  int i;

  i = -1;
  while(env[++i])
    free(env[i]);
  free(env);
}

void sigint_handler(int sig)
{
  int i;

  if (sig == SIGINT)
  {
    free_list(g_helper.list);
    if (g_helper.redfile)
    {
      i = -1;
      while (g_helper.redfile[++i])
        free(g_helper.redfile[i]);
      free(g_helper.redfile);
    }
    if(*g_helper.envp != NULL)
      clean_env(g_helper.envp);
    if(*g_helper.xenv != NULL)
      clean_env(g_helper.xenv);
  exit(1);
  }
}