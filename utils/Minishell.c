#include <minishell.h>

void ft_minishell(char *line,char **env)
{
  t_list *list;
  char **tokens;
  char *cmd;
  t_tree *root;
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
  //find_command(list,root,env);
  (void)env;
  return;
}

int main(int ac,char **av,char **env)
{
  char *line;

  (void)ac, (void)av,(void)env;
  while(1)
  {
    line = readline("minishell -> ");
    if(line)
    {
      ft_minishell(line,env);
      

    }

    //add_history(line);
  }
  return(0);
}
