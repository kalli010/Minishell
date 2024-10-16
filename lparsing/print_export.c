#include <minishell.h>

int get_var_value(char *env, char **var, char **value)
{
  int i;
  int s;

  i = -1;
  while(env[++i] && env[i] != '=');
  *var = ft_substr(env, 0, i);
  if(*var == NULL)
    return(1);
  if(env[i] != '\0')
    i++;
  s = i;
  while(env[i++]);
  *value = ft_substr(env, s, i - s);
  return(0);
}

int export(char **env)
{
  int i = -1;
  char *var;
  char *value;
  
  while(env[++i])
  {
    if(get_var_value(env[i], &var, &value))
      return(1);
    ft_putstr_fd(var, STDOUT_FILENO);
    if(value[0] != '\0')
    {
      ft_putchar_fd('=', STDOUT_FILENO);
      ft_putchar_fd('"', STDOUT_FILENO);
      ft_putstr_fd(value, STDOUT_FILENO);
      ft_putchar_fd('"', STDOUT_FILENO);
      ft_putchar_fd('\n', STDOUT_FILENO);
    }
    else
      ft_putchar_fd('\n', STDOUT_FILENO);
    free(var);
    free(value);
  }
  return(0);
}
