/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:21:08 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/16 17:12:01 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int check_root_content(t_tree  *root)
{
    if (!ft_strncmp(root->content->content,".", sizeof(".")))
    {
        printf("minishell : .: filename argument required\n");
        printf(".: usage: . filename [arguments]\n");
        return (2);
    }
    if (!ft_strncmp(root->content->content, "!", sizeof("!")))
        return (1);
    if (!ft_strncmp(root->content->content, "..", sizeof("..")))
    {
        printf("..: command not found\n");
        return (127);
    }
    if (!ft_strncmp(root->content->content, "//", 1) && is_only_slashes(root))
    {
        printf("minishell: %s: Is a directory\n", root->content->content);
        return (126);
    }
    if (is_only_bs(root))
        return (127);  
    return (0);
}

static int execute_parenthesis(t_tree *root, t_helper *helper, t_tree **rt)
{
  pid_t pid;
  int status;

  if (!root || !root->content)
    return (EXIT_FAILURE);
  if (root->content->type == COMMAND || root->content->type == PATH_COMMAND)
  {
    if (is_builtins(root))
      return run_builtins(root, helper);
  }
  pid = fork();
  if (pid == 0)
  {
    if (find_command(root, helper, rt) != EXIT_SUCCESS)
    {
      cleanup(helper, rt);
      exit(EXIT_FAILURE);
    }
    cleanup(helper, rt);
    exit(EXIT_SUCCESS);
  }
  else if (pid > 0)
  {
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
      return WEXITSTATUS(status);
    return (EXIT_FAILURE);
  }
  return (EXIT_FAILURE);
}

int handle_pipe(t_tree *root, t_helper *helper, t_tree **rt)
{
    
    if (root->content->type == PIPE)
    {
        return (execute_pipe(root, helper, rt));
    }
    return (EXIT_SUCCESS);
}

int find_command(t_tree *root, t_helper *helper, t_tree **rt)
{
   
    if (!root)
        return (EXIT_FAILURE);

    g_helper.exit_status = check_root_content(root);
    if (g_helper.exit_status != 0)
        return (g_helper.exit_status);

    //   if ((root->first_child && 
    //      root->first_child->next_sibling && 
    //      ((root->first_child->next_sibling->content->type != COMMAND &&
    //        root->first_child->next_sibling->content->type != PATH_COMMAND &&
    //        root->first_child->next_sibling->content->type != OPTIONS) || 
    //       (root->content->in == 1))))
    // { 
    if (root->content->in == 1)
    {
        root->content->in = 0;
        return (execute_parenthesis(root, helper, rt));
    }
    //         else
    //             return (execute_parenthesis(root->next_sibling, helper, rt));
    // }
    if (handle_pipe(root,helper, rt) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    if (root->content->type == APPEND || root->content->type == OUTPUT || root->content->type == INPUT)
    {
        if (redirect_all(root, helper,rt) != EXIT_SUCCESS)
            return (EXIT_FAILURE);
    }
     if (root->content->type == AND || root->content->type == OR)
        return (check_and_or(root, helper,rt));
    if (root->content->type == COMMAND || root->content->type == PATH_COMMAND)
    {
        if (is_builtins(root) == true)
            return (run_builtins(root, helper));
        return (execute(root, helper,rt));
    }
    return (EXIT_FAILURE);
}


