#include <minishell.h>

void quotes_check(char *str)
{
  int i;
  char c;
  int e;

  e = 0;
  i = -1;
  while(str[++i])
  {
    if(str[i] == 34 || str[i] == 39)
    {
      c = str[i];
      while(str[++i])
      {
        if(str[i] == c)
        {
          e++;
          break;
        }
      }
      if(e == 1)
        e = 0;
      else
      {
        printf("error, check %c.\n",c);
        break;
      }
    }
  }
}

int token_count(char *str)
{
  int i;
  int c;
  char q;

  c = 0;
  i = -1;
  while(str[++i])
  {
    if(str[i] != ' ')
    {
      c++;
      while(str[i] != '\0' && str[i] != ' ')
      {
        if(str[i] == 34 || str[i] == 39)
        {
          q = str[i];
          while(str[++i] != q);
        }
        i++;
      }
      if(str[i] == '\0')
        i--;
    }
  }
  return(c);
}

void create_tokens(char *str, char **tokens)
{
  int i;
  int s;
  int j;
  char q;

  j = 0;
  i = -1;
  while(str[++i])
  {
    if(str[i] != ' ')
    {
      s = i;
      while(str[i] != '\0' && str[i] != ' ')
      {
        if(str[i] == 34 || str[i] == 39)
        {
          q = str[i];
          while(str[++i] != q);
        }
        i++;
      }
      tokens[j] = ft_substr(str, s, i - s);
      j++;
      if(str[i] == '\0')
        i--;
    }
  }
  tokens[j] = NULL;
}

remove_quotes(char **tokens)
{
  int i;
  int j;
  char q;

  i = -1;
  while(tokens[++i])
  {
    j = -1;
    while(tokens[i][++j])
    {
      if(tokens[i][j] == 34 || tokens[i][j] == 39)
      {
        q = tokens[i][j];
        while(tokens[i][j])
      }
    }
  }
}

char **tokenizer(char *str)
{
  char **tokens;
  int tc;

  tc = token_count(str);
  tokens = (char **)malloc(sizeof(char *) * (tc + 1));
  create_tokens(str, tokens);
  remove_quotes(tokens);
  return(tokens);
}

int main()
{
  char *line;
  char **tokens;

  while(1)
  {
    line = readline("minishell -> ");
    if(!line)
      break;
    quotes_check(line);
    tokens = tokenizer(line);
    (void)tokens;
  }
  return(0);
}
