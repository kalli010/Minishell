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
  if(check_red(list))
    create_list_with_red(&list);
  if(check_input_herdoc(list))
    creat_linked_list_for_inp_herd(&list);
  if (symbols_check(list))
    return;
  if(check_parenthesis_error(list))
  {
    printf("Error check paranthesis.\n");
    return;
  }
  check_var(list, env);
  check_expander(env, &list);
  remove_quotes(list);
  if(check_parenthesis(list))
    root = creat_tree_with_parenthesis(list);
  else
    root = creat_tree(list);
  print_tree(root,0);
  //helper = init_helper(env);
  //find_command(root,helper);
  //free(list);
  //free(helper);
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
