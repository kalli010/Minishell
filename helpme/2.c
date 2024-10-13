#include <minishell.h>
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
      else
      {
        if(str[i] == '|' || str[i] == '<' || str[i] == '>' || str[i] == '&' || str[i] == 40 || str[i] == 41)
        {
          while(str[i] != '\0' && str[i] != ' ')
            i++;
        }
        else
        {
          while(str[i] != '\0' && str[i] != '|' && str[i] != '<' && str[i] != '>' && str[i] != '&' && str[i] != ' ' && str[i] != 40 && str[i] != 41)
          {
            if(str[i] == 34 || str[i] == 39)
            {
              q = str[i];
              while(str[++i] != q);
            }
            i++;
          }
        }
      }
      if(str[i] == '|' || str[i] == '<' || str[i] == '>' || str[i] == '&' || str[i] == 40 || str[i] == 41)
        i--;
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
  int s;

  c = 0;
  i = -1;
  while(str[++i])
  {
    if(str[i] != ' ' && (str[i] < 9 || str[i] > 13))
    {
      s = i;
      while(str[i] != '\0' && (str[i] != ' ' && (str[i] < 9 || str[i] > 13)))
      {
        if(str[i] == 34 || str[i] == 39)
        {
          q = str[i];
          while(str[++i] != q);
        }
        i++;
      }
      if(!ft_strncmp(&str[s], "echo", 4))
      {
        c += echo_token_count(&str[s]);
        return(c);
      }
      if(str[i] == '\0')
        i--;
      c++;
    }
  }
  return(c);
}

int count_words(char *str)
{
  int i;
  int c;
  int in_word;
  char q;

  i = -1;
  c = 0;
  in_word = 0;
  if(str == NULL)
    return(0);
  while(str[++i])
  {
    if(str[i] == '"' || str[i] == '\'')
    {
      q = str[i];
      while(str[++i] != q);
    }
    if(str[i] == ' ')
      in_word = 0;
    else if(str[i] != ' ' && in_word == 0)
    {
      c++;
      in_word = 1;
    }
  }
  return(c);
}

int split_tokens(char *tokens, char **tkn)
{
  char *str;
  int len;
  int i;
  int wd;
  char q;

  wd = count_words(tokens);
  i = -1;
  len = 0;
  while(tokens[++i])
  {
    if(tokens[i] == '"' || tokens[i] == '\'')
    {
      q = tokens[i];
      len++;
      while(tokens[++i] != q)
        len++;
    }
    if(tokens[i] != ' ')
      len++;
  }
  str = (char *)malloc(sizeof(char) * (len + (wd - 1) + 1));
  if(str == NULL)
    return(1);
  i = -1;
  len = -1;
  wd = 0;
  while(tokens[++i])
  {
    if(tokens[i] == '"' || tokens[i] == '\'')
    {
      q = tokens[i];
      str[++len] = tokens[i];
      while(tokens[++i] != q)
        str[++len] = tokens[i];
      str[++len] = tokens[i++];
    }
    if(tokens[i] == ' ')
    {
      wd = 0;
      str[++len] = ' ';
      while(tokens[++i] == ' ');
    }
    if(tokens[i] != ' ' && wd == 0)
    {
      wd = 1;
      while(tokens[i] != '\0' && tokens[i] != ' ')
      {
        if(tokens[i] == '"' || tokens[i] == '\'')
        {
          q = tokens[i];
          str[++len] = tokens[i];
          while(tokens[++i] != q)
            str[++len] = tokens[i];
        }
        str[++len] = tokens[i++];
      }
      i--;
    }
  }
  str[++len] = '\0';
  free(tokens);
  *tkn = str;
  return(0);
}

int echo_create_tokens(char *str, int j, char ***tokens)
{
  int i;
  int s;
  int x;
  char q;

  x = 0;
  i = -1;
  while(str[++i])
  {
    if(str[i] != ' ')
    {
      s = i;
      if(x == 0)
        while(str[i] != '\0' && str[i] != ' ' && (str[i] < 9 || str[i] > 13))
        {
          if(str[i] == 34 || str[i] == 39)
            {
              q = str[i];
              while(str[++i] != q);
            }
          i++;
        }
      else
      {
        if(str[i] == '|' || str[i] == '<' || str[i] == '>' || str[i] == '&' || str[i] == '&' || str[i] == 40 || str[i] == 41)
        {
          x = -1;
          while(str[i] != '\0' && str[i] != ' ' && (str[i] < 9 || str[i] > 13))
            i++;
        }
        else if(str[i] == '-')
        {
          while(str[++i] == 'n' || str[i] == '"' || str[i] == '\'');
          if(str[i] != ' ')
          {
            while(str[i] != '\0' && str[i] != '|' && str[i] != '<' && str[i] != '>' && str[i] != '&' && str[i] != 40 && str[i] != 41)
            {
              if(str[i] == 34 || str[i] == 39)
              {
                q = str[i];
                while(str[++i] != q);
              }
              i++;
            }
            while(str[--i] == ' ' && (str[i] < 9 || str[i] > 13));
            i++;
          }
        }
        else
        {
          while(str[i] != '\0' && str[i] != '|' && str[i] != '<' && str[i] != '>' && str[i] != '&' && str[i] != 40 && str[i] != 41)
          {
            if(str[i] == 34 || str[i] == 39)
            {
              q = str[i];
              while(str[++i] != q);
            }
            i++;
          }
          while(str[--i] == ' ' && (str[i] < 9 || str[i] > 13));
          i++;
        }
        
      }
      (*tokens)[j] = ft_substr(str, s, i - s);
      if((*tokens)[j] == NULL)
      {
        i = -1;
        while(++i < j)
          free((*tokens)[i]);
        return (1);
      }
      if(split_tokens((*tokens)[j], &(*tokens)[j]))
      {
        i = -1;
        while(++i < j)
          free((*tokens)[i]);
        return (1);
      }
      j++;
      x++;
      if(str[i] == '|' || str[i] == '<' || str[i] == '>' || str[i] == '&' || str[i] == 40 || str[i] == 41)
        i--;
      if(str[i] == '\0')
        i--;
    }
  }
  (*tokens)[j] = NULL;
  return(0);
}