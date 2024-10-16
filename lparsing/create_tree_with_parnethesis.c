#include <minishell.h>

t_tree *creat_subtree(t_list **list)
{
  t_tree *s_tree;
  t_tree *r_tree;
  t_tree *l_tree;

  l_tree = NULL;
  s_tree = NULL;
  r_tree = NULL;
  while(*list && (*list)->content[0] != 41)
  {
    if((*list)->content[0] == 40)
    {
      *list = (*list)->next;
      l_tree = creat_subtree(&(*list));
      *list = (*list)->next;
    }
    s_tree = creat_tree(*list);
    
    while((*list)->content[0] != 41)
    {
      (*list)->in = 1;
      if((*list)->content[0] == 40)
        break;
      *list = (*list)->next;
    }
    if(l_tree != NULL)
    {
      if(r_tree != NULL)
        add_child_to_tree(r_tree, l_tree);
      else
      {
        add_sibling_to_child(l_tree, s_tree->first_child);
        s_tree->first_child = l_tree;
      }
    }
    if(r_tree == NULL)
      r_tree = s_tree;
    else if(s_tree != NULL && s_tree->first_child != NULL)
    {
      add_sibling_to_child(r_tree, s_tree->first_child);
      s_tree->first_child = r_tree;
      r_tree = s_tree;
    }
    else if(s_tree != NULL && s_tree->first_child == NULL)
    {
      add_child_to_tree(s_tree, r_tree);
      r_tree = s_tree;
    }
  }
  return(r_tree);
}

t_tree *creat_tree_with_parenthesis(t_list *list)
{
  t_tree *root;
  t_tree *l_node;
  t_tree *r_tree;
  t_tree *tmp;
  t_tree *tmp2;

  r_tree = NULL;
  l_node = NULL;
  root = NULL;
  while(list)
  {
    if(list->content[0] == 41)
      list = list->next;
    if(list->content[0] == 40)
    {
      list = list->next;
      r_tree = creat_subtree(&list);
      list = list->next;
    }
    if(root != NULL && r_tree != NULL)
    {
      if(root->first_child->next_sibling != NULL)
        add_child_to_tree(root->first_child->next_sibling, r_tree);
      else
        add_child_to_tree(root, r_tree);
    }
    l_node = creat_tree(list);
    
    if(root == NULL)
    {
      if(r_tree != NULL)
      {
        if(l_node != NULL && l_node->first_child != NULL)
        {
          if(l_node->first_child->content->type == COMMAND \
            || l_node->content == list)
          {
            add_sibling_to_child(r_tree, l_node->first_child);
            l_node->first_child = r_tree;
          }
          else
          {
            tmp = l_node->first_child;
            while(check_tmp(tmp->first_child->content))
              tmp = tmp->first_child;
            tmp2 = tmp->first_child;
            tmp->first_child = r_tree;
            r_tree->next_sibling = tmp2;
          }
        }
        else if(l_node != NULL)
          add_child_to_tree(l_node, r_tree);
      }
      if(l_node != NULL)
        root = l_node;
      else {
        root = r_tree;
      }
    }
    else if(l_node != NULL && l_node->first_child != NULL)
    {
      add_sibling_to_child(root, l_node->first_child);
      l_node->first_child = root;
      root = l_node;
    }
    else if(l_node != NULL && l_node->first_child == NULL)
    {
      add_child_to_tree(l_node, root);
      root = l_node;
    }
    while(list != NULL && list->content[0] != 40)
      list = list->next;
    r_tree = NULL;
  }
  if(root == NULL)
    root = r_tree;
  return(root);
}
