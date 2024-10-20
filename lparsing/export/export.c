/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:50:43 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/19 21:38:22 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_var_value(char *var, char *value)
{
	free(var);
	free(value);
}

int	update_existing_var(char ***env, t_set_var *sv, char ***xenv, t_list *list)
{
	if (!ft_strncmp((*env)[sv->s], sv->var, ft_strlen(sv->var))
		&& ((*env)[sv->s][ft_strlen(sv->var)] == '='
			|| (*env)[sv->s][ft_strlen(sv->var)] == '\0'))
	{
		if (list->content[ft_strlen(sv->var)] == '\0')
		{
			free_var_value(sv->var, sv->value);
			return (0);
		}
		if (add_var(*env, sv->var, sv->value, sv->s))
		{
			free_var_value(sv->var, sv->value);
			return (1);
		}
		if (add_var(*xenv, sv->var, sv->value, sv->s))
		{
			free_var_value(sv->var, sv->value);
			return (1);
		}
		free_var_value(sv->var, sv->value);
		return (0);
	}
	return (0);
}








int set_var(t_list *list, char ***env, char ***xenv)
{
  char *var;
  char *value;
  int len;
  int s;

  len = 0;
  s = 0;
  while (list->content[len] && list->content[len] != '=')
    len++;
  var = ft_substr(list->content, 0, len);
  if(var == NULL)
    return(1);
  remove_quotes_string(var);
  if((!ft_isalpha(var[0]) && var[0] != '_' ) || check_content(var))
  {
    free(var);
    return(1);
  }
  if (list->content[len] != '\0')
  {
    if(list->content[len - 1] == ' ')
      return(1);
    len++;
  }
  s = len;
  while (list->content[len])
    len++;
  value = ft_substr(list->content, s, len - s);
  remove_quotes_string(value);
  s = 0;
  while (*env != NULL && (*env)[s] != NULL)
  {
    if (!ft_strncmp((*env)[s], var, ft_strlen(var)) && ((*env)[s][ft_strlen(var)] == '=' || (*env)[s][ft_strlen(var)] == '\0'))
    {
      if(list->content[ft_strlen(var)] == '\0')
      {
        free(var);
        free(value);
        return(0);
      }
      if(add_var(*env, var, value, s))
      {
        free(var);
        free(value);
        return(1);
      }
      if(add_var(*xenv, var, value, s))
      {
        free(var);
        free(value);
        return(1);
      }
      free(var);
      free(value);
      return(0);
    }
    s++;
  }
  *env = add_new_env(*env, s, var, value, 0);
  *xenv = add_new_env(*xenv, s, var, value, 1);
  if(*env == NULL || *xenv == NULL)
  {
    free(var);
    free(value);
    return(1);
  }
  free(var);
  free(value);
  return(0);
}










//int	set_var(t_list *list, char ***env, char ***xenv)
//{
//	t_set_var	sv;
//
//	if (validate_var(list, &sv))
//		return (1);
//	sv.s = 0;
//	while (*env != NULL && (*env)[sv.s] != NULL)
//	{
//		if (update_existing_var(env, &sv, xenv, list))
//			return (1);
//		sv.s++;
//	}
//	*env = add_new_env(*env, sv.s, sv, 0);
//	*xenv = add_new_env(*xenv, sv.s, sv, 1);
//	if (*env == NULL || *xenv == NULL)
//	{
//		free_var_value(sv.var, sv.value);
//		return (1);
//	}
//	free_var_value(sv.var, sv.value);
//	return (0);
//}

int	check_cmd_export(t_list *list)
{
	while (list)
	{
		if (list->type != OPTIONS)
			return (1);
		list = list->next;
	}
	return (0);
}

int	check_var(t_list *list, char ***env, char ***xenv)
{
	g_helper.exit_status = 0;
	if (list->back && (list->back->back != NULL || check_cmd_export(list)))
		return (g_helper.exit_status);
	while (list)
	{
		if (set_var(list, env, xenv))
		{
			printf("not a valid identifier\n");
			g_helper.exit_status = 1;
		}
		list = list->next;
	}
	return (g_helper.exit_status);
}
