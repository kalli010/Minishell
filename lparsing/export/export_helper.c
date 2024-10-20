/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:47:26 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/19 23:47:27 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	add_var(char **env_or_xenv, char *var, char *value, int index)
{
	char	*new_var;

	new_var = (char *)malloc(sizeof(char) * (ft_strlen(var) + ft_strlen(value)
				+ 2));
	if (new_var == NULL)
		return (1);
	new_var[0] = '\0';
	ft_cpy(new_var, var);
	if (value != NULL)
	{
		ft_cpy(new_var, "=");
		ft_cpy(new_var, value);
	}
  if(env_or_xenv[index] != NULL)
  {
	  free(env_or_xenv[index]);
    env_or_xenv[index] = NULL;
  }
  env_or_xenv[index] = new_var;
	return (0);
}

int	alloc_env(int check, char ***new_env, int s, char *value)
{
	if (check == 0)
	{
		*new_env = (char **)malloc(sizeof(char *) * (s + 2));
		if (*new_env == NULL)
			return (1);
	}
	else
	{
		if (value != NULL)
		{
			*new_env = (char **)malloc(sizeof(char *) * (s + 2));
			if (*new_env == NULL)
				return (1);
		}
		else
		{
			*new_env = (char **)malloc(sizeof(char *) * (s + 1));
			if (*new_env == NULL)
				return (1);
		}
	}
	return (0);
}

void	free_new_env(t_insert_new_var *iv, int len)
{
	while (--len >= 0)
		free(iv->new_env[len]);
	free(iv->new_env);
	free(iv->env_or_xenv);
}

char	**insert_new_var(t_insert_new_var *iv, int len, int check)
{
	if (check == 1)
	{
		if (*iv->value != NULL)
		{
			if (add_var(iv->new_env, *iv->var, *iv->value, len))
			{
				free_new_env(iv, len);
				return (NULL);
			}
			(iv->new_env)[++len] = NULL;
		}
	}
	else
	{
		if (add_var(iv->new_env, *iv->var, *iv->value, len))
		{
			free_new_env(iv, len);
			return (NULL);
		}
		iv->new_env[++len] = NULL;
	}
  if(iv->env_or_xenv != NULL)
  {
    free(iv->env_or_xenv);
    iv->env_or_xenv = NULL;
  }
  return (iv->new_env);
}

void	init_iv(char **new_env, t_set_var *sv, char **env_or_xenv,
		t_insert_new_var *iv)
{
	new_env[iv->len] = NULL;
	iv->value = &sv->value;
	iv->new_env = new_env;
	iv->var = &sv->var;
	iv->env_or_xenv = env_or_xenv;
}
