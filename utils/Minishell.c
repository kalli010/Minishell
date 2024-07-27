#include <minishell.h>

int quotes_check(char *str)
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
        printf("Error, check %c.\n",c);
        return(1);
      }
    }
  }
  return(0);
}

//int symbols_check(char *str)
//{
//  while(*str)
//  {
//    if(*str == '|' && *(str + 1) == '|' && *(str + 2) == '|')
//    {
//      printf("Error, there is more than two pipes\n");
//      return(1);
//    }
//    else if(*str == '<' && *(str + 1) == '<' && *(str + 2) == '<')
//    {
//      printf("Error, there is more than two redirections\n");
//      return(1);
//    }
//    else if(*str == '>' && *(str + 1) == '>' && *(str + 2) == '>')
//    {
//      printf("Error, there is more than two redirections\n");
//      return(1);
//    }
//   // else if(*str == '>' && *(str + 1) == '<')
//   // {
//   //   printf("Error\n");
//   //   return(1);
//   // }
//   // else if(*str == '<' && *(str + 1) == '>')
//   // {
//   //   printf("Error\n");
//   //   return(1);
//   // }
//    str++;
//  }
//  return(0);
//}

void check_p_r(char *str, int *i, int *s)
{
  if(str[0] == '|')
  {
    if(str[0 + 1] != '|')
      *s = *s + 2;
    else
    {
      *s = *s + 2;
      *i = *i + 1;
    }
  }
  else if(str[0] == '>')
  {
    if(str[0 + 1] != '>')
      *s = *s + 2;
    else
    {
      *s = *s + 2;
      *i = *i + 1;
    }
  }
  else if(str[0] == '<')
  {
    if(str[0 + 1] != '<')
      *s = *s + 2;
    else
    {
      *s = *s + 2;
      *i = *i + 1;
    }
  }
}

int check_p_r2(char *str,int *i)
{
  if(str[0] == '|')
  {
    if(str[0 + 1] != '|')
      return(1);
    else
    {
      *i = *i + 1;
      return(0);
    }
  }
  else if(str[0] == '>')
  {
    if(str[0 + 1] != '>')
      return(1);
    else
    {
      *i = *i + 1;
      return(0);
    }
  }
  else if(str[0] == '<')
  {
    if(str[0 + 1] != '<')
      return(1);
    else
    {
      *i = *i + 1;
      return(0);
    }
  }
  return(-1);
}

char *split_symbols(char *str)
{
  int i;
  int s;
  char *tmp;
  char q;
  int check;

  s = 0;
  i = -1;
  while(str[++i])
  {
    if(str[i] == 34 || str[i] == 39)
    {
      q = str[i];
      while(str[++i] != q);
    }
    check_p_r(&str[i], &i, &s);
  }
  tmp = (char *)malloc(sizeof(char) * (i + s + 1));
  i = -1;
  s = 0;
  while(str[++i])
  {
    if(str[i] == 34 || str[i] == 39)
    {
      q = str[i];
      tmp[s++] = str[i];
      while(str[++i] != q)
        tmp[s++] = str[i];
      tmp[s++] = str[i];
    }
    else
    {
      check = check_p_r2(&str[i], &i);
      if(check == 1)
      {
        tmp[s++] = ' ';
        tmp[s++] = str[i];
        tmp[s++] = ' ';
      }
      else if(check == 0)
      {
        tmp[s++] = ' ';
        tmp[s++] = str[i];
        tmp[s++] = str[i];
        tmp[s++] = ' ';
      }
      else
        tmp[s++] = str[i];
    }
  }
  tmp[s] = '\0';
  return(tmp);
}

int echo_check(char *str)
{
  int i;
  int j;

  i = -1;
  j = 0;
  while(str[++i])
  {
    if(str[i] != ' ')
    {
      j = i;
      while(str[i] != ' ' && str[i++] != '\0');
      if(!ft_strncmp(&str[j], "echo", i - j))
        return(1);
      else 
        return(0);
    }
  }
  return(0);
}

int echo_token_count(char *str)
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
      if(c == 1)
      {
        while(str[i] != '\0' && str[i] != ' ')
          i++;
      }
      while(str[i] != '\0' && (str[i] != '|' || str[i] != '<' || str[i] != '>' ))
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

void echo_create_tokens(char *str, char **tokens)
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
      if(j == 0)
        while(str[i] != '\0' && str[i] != ' ')
          i++;
      else
      {
        if(str[i] == '|' || str[i] == '<' || str[i] == '>')
        {
          while(str[i] != '\0' && str[i] != ' ')
            i++;
        }
        else
        {
          while(str[i] != '\0' && str[i] != '|' && str[i] != '<' && str[i] != '>' )
          {
            if(str[i] == 34 || str[i] == 39)
            {
              q = str[i];
              while(str[++i] != q);
            }
            i++;
          }
          if(str[i] != '\0')
            i--;
        }
      }
      tokens[j] = ft_substr(str, s, i - s);
      j++;
      if(str[i] == '\0')
        i--;
    }
  }
  tokens[j] = NULL;
}

void create_tokens(char *str, char **tokens)
{
  int i;
  int s;
  int j;
  char q;

  j = 0;
  i = -1;
  if(echo_check(str))
    echo_create_tokens(str, tokens);
  else 
  {
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
}

void remove_quotes(char **tokens)
{
  //int i;
  int j;
  char q;

  //i = -1;
  //while(tokens[++i])
  //{
    j = -1;
    while(tokens[0][++j])
    {
      if(tokens[0][j] == '"' /*|| tokens[0][j] == 39*/)
      {
        q = tokens[0][j];
        tokens[0][j] = tokens[0][j + 1];
        while(tokens[0][++j + 1] != q)
          tokens[0][j] = tokens[0][j + 1];
        j++;
        while(tokens[0][++j])
          tokens[0][j - 2] = tokens[0][j];
        tokens[0][j - 2] = '\0';
        j = -1;;
      }
    }
  //}
}

int check_commend(char *str)
{
  int i;

  i = 0;
  if(!str)
    return(0);
  if(str[0] == '"')
  {
    if(str[1] == '$')
      return(0);
    while(str[++i] != '"');
  }
  i--;
  if(!ft_strncmp(&str[1],"ls",i - 1))
    return(1);
  return(0);
}

char **tokenizer(char *str)
{
  char **tokens;
  int tc;

  if(echo_check(str))
    tc = echo_token_count(str);
  else
    tc = token_count(str);
  tokens = (char **)malloc(sizeof(char *) * (tc + 1));
  create_tokens(str, tokens);
  if(check_commend(tokens[0]))
    remove_quotes(tokens);
  int i = -1;
  while(tokens[++i])
    printf("token %d: %s\n",i,tokens[i]);
  return(tokens);
}

//int basic_symbols_check(char **tokens)
//{
//  int i;
//
//  i = 0;
//  if(tokens[i][0] == '|')
//  {
//    printf("syntax error\n");
//    return(1);
//  }
//  else
//  {
//    while(tokens[i++]);
//    if(tokens[i - 2][0] == '>' || tokens[i - 2][0] == '<')
//    {
//      printf("syntax error\n");
//      return(1);
//    }
//  }
//  return(0);
//}



void ft_minishell(char *line)
{
   char **tokens;
   char *cmd;
  
  if(quotes_check(line))
      return;
  cmd = split_symbols(line);
  free(line);
  tokens = tokenizer(cmd);
  creat_linked_list(tokens);
  return;
}

int main()
{
  char *line;

  while(1)
  {
    line = readline("minishell -> ");
    if(line)
      ft_minishell(line); 
  }
  return(0);
}
