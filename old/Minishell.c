#include <minishell.h>


t_helper g_helper;

void init_helper(void)
{
  g_helper.envp = NULL;
  g_helper.xenv = NULL;
  g_helper.exit_status = 0;
  g_helper.root = NULL;
  g_helper.redfile = NULL;
  g_helper.list = NULL;
}

void init_helper_2(void)
{
  g_helper.root = NULL;
  g_helper.redfile = NULL;
  g_helper.list = NULL;
}

int ft_minishell(char *line)
{
  char **tokens;
  char *cmd;
  int hd;
  t_list *tmp;

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
  if(creat_linked_list(&g_helper.list, tokens))
    return(1);
  if (check_red_with_cmd(g_helper.list))
  {
    if(recreate_linked_list(g_helper.list, &g_helper.list))
    {
      free(tokens);
      return(1);
    }
  }
  if (symbols_check(g_helper.list))
  {
    free_list(g_helper.list);
    free(tokens);
    return (1);
  }
  if (check_parenthesis_error(g_helper.list))
  {
    printf("syntax error\n");
    free_list(g_helper.list);
    free(tokens);
    return 1;
  }
  if(check_expander(g_helper.envp, &g_helper.list))
  {
    printf("malloc failed.\n");
    free_list(g_helper.list);
    free(tokens);
    return(1);
  }
  clean_linked_list(&g_helper.list);
  tmp = g_helper.list;
  while(tmp)
  {
    token_type(tmp);
    tmp = tmp->next;
  }
  if(check_wildcards(g_helper.list))
    wildcards(&g_helper.list);
  hd = check_heredoc(g_helper.list);
  if (hd > 16)
  {
    printf("Error.\n");
    return 1;
  }
  else if (hd)
  {
    if (heredoc(&g_helper.list, hd, g_helper.envp, g_helper.xenv, &g_helper.redfile))
      return 1;
  }
  remove_quotes(g_helper.list);
  if (check_parenthesis(g_helper.list))
    g_helper.root = creat_tree_with_parenthesis(g_helper.list);
  else
    g_helper.root = creat_tree(g_helper.list);
  print_tree(g_helper.root, 0);
  find_command(g_helper.root, &g_helper, &g_helper.root);
  check_signal();
  my_free(&g_helper);
  if (hd)
    if (clean_heredoc(g_helper.redfile, hd))
      return 1;
  free(g_helper.redfile);
  free_tree(g_helper.root);
  return 0;
}

int main(int ac, char **av, char **envp)
{
  char *line;

  (void)ac, (void)av;
  init_helper();
  g_helper.envp = create_env(envp);
  g_helper.xenv = create_env(envp);
  while (1)
  {
    signal_handeler(BEFORE);
    line = readline("(minishell)-> ");
    init_helper_2();
    signal_handeler(PARENT);
    if (line == NULL)
    {
      printf("exit \n");
      free(line);
      printf("%d\n",g_helper.exit_status);
      (clean_env(g_helper.envp),clean_env(g_helper.xenv));
      exit(g_helper.exit_status);
    }
    if (ft_strlen(line) > 0)
      add_history(line);
    if (line)
      ft_minishell(line);
  }
  return (EXIT_SUCCESS);
}


