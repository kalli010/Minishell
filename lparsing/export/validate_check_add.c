/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_check_add.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:50:33 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/19 23:50:35 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>







char **add_new_env(char **env_or_xenv, int s, char *var, char *value, int check)
{
  char **new_env;
  int len;

  len = 0;
  if(check == 0)
  {
    new_env = (char **)malloc(sizeof(char *) * (s + 2));
    if(new_env == NULL)
      return(NULL);
  }
  else
  {
    if(value != NULL)
    {
      new_env = (char **)malloc(sizeof(char *) * (s + 2));
      if(new_env == NULL)
        return(NULL);
    }
    else
    {
      new_env = (char **)malloc(sizeof(char *) * (s + 1));
      if(new_env == NULL)
        return(NULL);
    }
  }
  while (env_or_xenv && env_or_xenv[len])
  {
    new_env[len] = ft_substr(env_or_xenv[len], 0, ft_strlen(env_or_xenv[len]));
    if(new_env[len] == NULL)
    {
      check = -1;
      while(++check < len)
        free(new_env[check]);
      while(env_or_xenv && env_or_xenv[len])
        free(env_or_xenv[len++]);
      free(new_env);
      return(NULL);
    }
    free(env_or_xenv[len]);
    len++;
  }
  new_env[len] = NULL;
  if(check == 1)
  {
    if(value != NULL)
    {
      if(add_var(new_env, var, value, len))
      {
        while(--len >= 0)
          free(new_env[len]);
        free(new_env);
        free(env_or_xenv);
        return(NULL);
      }
      new_env[++len] = NULL;
    }
  }
  else
  {
    if(add_var(new_env, var, value, len))
    {
      while(--len >= 0)
        free(new_env[len]);
      free(new_env);
      free(env_or_xenv);
      return(NULL);
    }
    new_env[++len] = NULL;
  }
  free(env_or_xenv);
  return new_env;
}









//char	**add_new_env(char **env_or_xenv, int s, t_set_var sv, int check)
//{
//	char				**new_env;
//	t_insert_new_var	iv;
//
//	iv.len = 0;
//	if (alloc_env(check, &new_env, s, sv.value))
//		return (NULL);
//	while (env_or_xenv && env_or_xenv[iv.len])
//	{
//		new_env[iv.len] = ft_substr(env_or_xenv[iv.len], 0,
//				ft_strlen(env_or_xenv[iv.len]));
//		if (new_env[iv.len] == NULL)
//		{
//			check = -1;
//			while (++check < iv.len)
//				free(new_env[check]);
//			free(new_env);
//			//while (env_or_xenv && env_or_xenv[iv.len])
//			//	free(env_or_xenv[iv.len++]);
//			return (NULL);
//		}
//    if(env_or_xenv[iv.len] != NULL)
//    {
//      free(env_or_xenv[iv.len]);
//      env_or_xenv[iv.len] = NULL;
//    }
//    iv.len++;
//	}
//	init_iv(new_env, &sv, env_or_xenv, &iv);
//	return (insert_new_var(&iv, iv.len, check));
//}

int	check_content(char *str)
{
	int	i;

	i = 0;
	while (str[++i])
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_')
			return (1);
	}
	return (0);
}

int	validate_var(t_list *list, t_set_var *sv)
{
	int	s;
  int len;

  len = 0;
	while (list->content[len] && list->content[len] != '=')
		len++;
	sv->var = ft_substr(list->content, 0, len);
	if (sv->var == NULL)
		return (1);
	remove_quotes_string(sv->var);
	if ((!ft_isalpha(sv->var[0]) && sv->var[0] != '_')
		|| check_content(sv->var))
	{
		free(sv->var);
		return (1);
	}
	if (list->content[len] != '\0')
	{
		if (list->content[len - 1] == ' ')
			return (1);
		len++;
	}
	s = len;
	while (list->content[len])
		len++;
	sv->value = ft_substr(list->content, s, len - s);
	remove_quotes_string(sv->value);
	return (0);
}
