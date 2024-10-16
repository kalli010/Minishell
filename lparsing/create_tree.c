#include <minishell.h>

t_tree *creat_tree(t_list *lst)
{
  t_tree *root;
  t_tree *n_node;
  t_tree *l_node;

  l_node = NULL;
  n_node = NULL;
  root = NULL;
  while(lst)
  {
    if(lst->content[0] == 41 || lst->content[0] == 40)
      return(root);
    n_node = create_tree_node(lst);
    if(root == NULL)
      root = n_node;
    else if( n_node->content->type == PIPE 
        || n_node->content->type == OR 
        || n_node->content->type == AND 
        || n_node->content->type == OUTPUT 
        || n_node->content->type == HEREDOC 
        || n_node->content->type == INPUT 
        || n_node->content->type == APPEND)
    {
      add_child_to_tree(n_node, root);
      root = n_node;
    }
    else
    {
      if(l_node->content->type != COMMAND && root != l_node)
        add_sibling_to_child(l_node, n_node);
      else
        add_child_to_tree(l_node, n_node);
    }
    if(n_node->content->type == OR || n_node->content->type == AND)
    {
      
      l_node = creat_tree(lst->next);
      if(l_node != NULL && (l_node->content->type == OR || l_node->content->type == AND))
      {
        root = l_node;
        while(l_node->first_child->first_child)
          l_node = l_node->first_child;
        add_child_to_tree(n_node, l_node->first_child);
        add_sibling_to_child(n_node, l_node->first_child->next_sibling);
        l_node->first_child->next_sibling = NULL;
        l_node->first_child = n_node;
      }
      else
        add_child_to_tree(n_node, l_node);
      return(root);
    }
    l_node = n_node;
    lst = lst->next;
  }
  return(root);
}
