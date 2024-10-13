#include <minishell.h>


void free_tree(t_tree *root)
{
  t_tree *child;
  t_tree *next;

  if(root == NULL)
    return;
  child = root->first_child;
  while(child)
  {
    next = child->next_sibling;
    free_tree(child);
    child = next;
  }
  if (root->content->content != NULL)
    free(root->content->content);
  free(root->content);
  free(root);
}

int env_size(char **str)
{
  int s;

  s = 0;
  while(str[s])
    s++;
  return(s);
}

char **create_env(char **envp)
{
  char **env;
  int s;
  int i;
  char ***new_env;

  i = -1;
  s = env_size(envp);
  env = (char **)malloc(sizeof(char *) * (s + 1));
  if(env == NULL)
    return(NULL);
  while(envp[++i])
  {
    env[i] = ft_substr(envp[i], 0, ft_strlen(envp[i]));
    if(env[i] == NULL)
    {
      while(--i >= 0)
        free(env[i]);
      free(env);
    }
  }
  env[i] = NULL;
  new_env = &env;
  return(env);
}

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