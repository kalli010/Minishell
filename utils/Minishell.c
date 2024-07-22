#include <minishell.h>

int basic_check(char *str)
{
  int i;
  char c;

  i = 0;
  while(str[i])
  {
    if(str[i] == '"')
      c++;
    i++;
  }
  return(0);
}

int main()
{
  char *line;

  while(1)
  {
    line = readline("minishell -> ");
    basic_check(line);
  }
  return(0);
}
