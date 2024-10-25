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
#include <stdlib.h>
#include <string.h>

char	**allocate_new_env(t_add_env_params *params)
{
	char	**new_env;

	if (params->check == 0)
		new_env = (char **)malloc(sizeof(char *) * (params->s + 2));
	else
	{
		if (params->value != NULL)
			new_env = (char **)malloc(sizeof(char *) * (params->s + 2));
		else
			new_env = (char **)malloc(sizeof(char *) * (params->s + 1));
	}
	return (new_env);
}

int	copy_old_env(t_add_env_params *params, char **new_env)
{
	int	len;
	int	i;

	len = 0;
	while (params->env_or_xenv && params->env_or_xenv[len])
	{
		new_env[len] = ft_substr(params->env_or_xenv[len], 0,
				ft_strlen(params->env_or_xenv[len]));
		if (new_env[len] == NULL)
		{
			i = -1;
			while (++i < len)
				free(new_env[i]);
			free(new_env);
			while (params->env_or_xenv && params->env_or_xenv[len])
				free(params->env_or_xenv[len++]);
			free(params->env_or_xenv);
			return (-1);
		}
		free(params->env_or_xenv[len]);
		len++;
	}
	new_env[len] = NULL;
	return (len);
}

int	handle_add_variable(t_add_env_params *params, char **new_env, int len)
{
	if (params->check == 1)
	{
		if (params->value != NULL)
		{
			if (add_var(new_env, params->var, params->value, len))
			{
				while (--len >= 0)
					free(new_env[len]);
				return (free(new_env), free(params->env_or_xenv), -1);
			}
			new_env[++len] = NULL;
		}
	}
	else
	{
		if (add_var(new_env, params->var, params->value, len))
		{
			while (--len >= 0)
				free(new_env[len]);
			return (free(new_env), free(params->env_or_xenv), -1);
		}
		new_env[++len] = NULL;
	}
	return (0);
}

char	**add_new_env(t_add_env_params *params)
{
	char	**new_env;
	int		len;

	new_env = allocate_new_env(params);
	if (new_env == NULL)
		return (NULL);
	len = copy_old_env(params, new_env);
	if (len == -1)
		return (NULL);
	if (handle_add_variable(params, new_env, len) == -1)
		return (NULL);
	free(params->env_or_xenv);
	return (new_env);
}

// char	**add_new_env(char **env_or_xenv, int s, char *var, char *value,
// 		int check)
// {
// 	char	**new_env;
// 	int		len;
//
// 	len = 0;
// 	if (check == 0)
// 	{
// 		new_env = (char **)malloc(sizeof(char *) * (s + 2));
// 		if (new_env == NULL)
// 			return (NULL);
// 	}
// 	else
// 	{
// 		if (value != NULL)
// 		{
// 			new_env = (char **)malloc(sizeof(char *) * (s + 2));
// 			if (new_env == NULL)
// 				return (NULL);
// 		}
// 		else
// 		{
// 			new_env = (char **)malloc(sizeof(char *) * (s + 1));
// 			if (new_env == NULL)
// 				return (NULL);
// 		}
// 	}
// 	while (env_or_xenv && env_or_xenv[len])
// 	{
// 		new_env[len] = ft_substr(env_or_xenv[len], 0,
// 				ft_strlen(env_or_xenv[len]));
// 		if (new_env[len] == NULL)
// 		{
// 			check = -1;
// 			while (++check < len)
// 				free(new_env[check]);
// 			while (env_or_xenv && env_or_xenv[len])
// 				free(env_or_xenv[len++]);
// 			free(new_env);
// 			return (NULL);
// 		}
// 		free(env_or_xenv[len]);
// 		len++;
// 	}
// 	new_env[len] = NULL;
// 	if (check == 1)
// 	{
// 		if (value != NULL)
// 		{
// 			if (add_var(new_env, var, value, len))
// 			{
// 				while (--len >= 0)
// 					free(new_env[len]);
// 				free(new_env);
// 				free(env_or_xenv);
// 				return (NULL);
// 			}
// 			new_env[++len] = NULL;
// 		}
// 	}
// 	else
// 	{
// 		if (add_var(new_env, var, value, len))
// 		{
// 			while (--len >= 0)
// 				free(new_env[len]);
// 			free(new_env);
// 			free(env_or_xenv);
// 			return (NULL);
// 		}
// 		new_env[++len] = NULL;
// 	}
// 	free(env_or_xenv);
// 	return (new_env);
// }

int	check_content(char *str)
{
	int	i;

	i = 0;
	while (str[++i])
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_')
		{
			if (str[i] == '=' && str[i + 1] == '\0')
				return (0);
			return (1);
		}
	}
	return (0);
}
