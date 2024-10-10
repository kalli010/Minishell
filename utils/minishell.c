#include <minishell.h>

int g_exit_status;

t_helper *init_helper(char ***env,char ***xenv)
{
    t_helper *helper;
    helper = (t_helper *)malloc(sizeof(t_helper));

    helper->envp = *env;
    helper->cmd = NULL;
    helper->xenv = *xenv;
    helper->option = NULL;
    helper->flag = false;
    return (helper);
}

int ft_minishell(char *line, char ***env, char ***xenv)
{
  t_list *list;
  char **tokens;
  char *cmd;
  t_tree *root;
  int hd;
  char **redfile;
  t_helper *helper;
  t_list *tmp;

  list = NULL;
  redfile = NULL;
  if (quotes_check(line))
    return 1;
  if(split_symbols(line, &cmd))
  {
    free(line);
    return(1);
  }
  free(line);
  if(tokenizer(cmd, &tokens))
  {
    free(cmd);
    return(1);
  }
  if(creat_linked_list(&list, tokens, 0))
    return(1);
  if (check_red_with_cmd(list))
  {
    if(recreate_linked_list(list, &list))
    {
      free(tokens);
      return(1);
    }
  }
  if (symbols_check(list))
  {
    free_list(list);
    free(tokens);
    return (1);
  }
  if (check_parenthesis_error(list))
  {
    printf("syntax error\n");
    free_list(list);
    free(tokens);
    return 1;
  }
  if(check_expander(*env, &list))
  {
    printf("malloc failed.\n");
    free_list(list);
    free(tokens);
    return(1);
  }
  clean_linked_list(&list);
  tmp = list;
  while(tmp)
  {
    token_type(tmp);
    tmp = tmp->next;
  }
  check_var(list, env, xenv);
  if(check_Wildcards(list))
    wildcards(list);
  hd = check_heredoc(list);
  if (hd > 16)
  {
    printf("Error.\n");
    return 1;
  }
  else if (hd)
  {
    if (heredoc(&list, hd, *env, &redfile, &tokens))
      return 1;
  }
  remove_quotes(list);
  if (check_parenthesis(list))
    root = creat_tree_with_parenthesis(list);
  else
    root = creat_tree(list);
  print_tree(root,0);
  helper =  init_helper(env,xenv);
  find_command(root, helper);
  my_free(helper);
  if (hd)
    if (clean_heredoc(redfile, hd))
      return 1;
  free_tree(root);
  return 0;
}

int main(int ac, char **av, char **envp)
{
  char *line;
  char **env;
  char **xenv;

  (void)ac, (void)av;
  env = create_env(envp);
  xenv = create_env(envp);
  while (1)
  {
    signal_handeler(BEFORE);
    line = readline("(minishell)-> ");
    signal_handeler(PARENT);
    if (line == NULL)
    {
      printf("exit \n");
      free(line);
      printf("%d\n",g_exit_status);
      exit(g_exit_status);
    }
    if (ft_strlen(line) > 0)
      add_history(line);
    if (line)
      ft_minishell(line, &env, &xenv);
  }
  return (EXIT_SUCCESS);
}
