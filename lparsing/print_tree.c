#include <minishell.h>

void print_tree(t_tree *root, int spaces)
{
  int i;
  t_tree *child;

  i = -1;
  if(root == NULL)
    return;
  while(++i < spaces)
    printf(" ");
  printf("%s  (%d)\n",root->content->content,root->content->type);
  child = root->first_child;
  while(child)
  {
    print_tree(child, spaces + 2);
    child = child->next_sibling;
  }
}
