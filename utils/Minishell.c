#include <minishell.h>

t_helper *init_helper(char **env)
{
  t_helper *helper;

  helper = (t_helper *)malloc(sizeof(t_helper));
  helper->envp = env;
  helper->cmd = NULL;
  helper->option = NULL;
  return (helper);
}
void ft_minishell(char *line,char **env)
{
  t_list *list;
  char **tokens;
  char *cmd;
 t_tree *root;
  //t_helper *helper;
  (void)env;
  list = NULL;
  if(quotes_check(line))
      return;
  cmd = split_symbols(line);
  free(line);
  tokens = tokenizer(cmd);
  creat_linked_list(&list, tokens);
  if (symbols_check(list))
    return;
  root = creat_tree(list);
  print_tree(root,0);
  helper = init_helper(env);
  find_command(root,helper);
  free(list);
  free(helper);
  return;
}

int main(int ac,char **av,char **env)
{
  char *line;

  (void)ac, (void)av;
  while(1)
  {
    line = readline("minishell -> ");
    if (ft_strlen(line) > 0)
      add_history(line);
    if(line)
      ft_minishell(line,env);

  }
  return(0);
}
