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

char	**add_new_env(char **env_or_xenv, int s, char *var, char *value,
		int check)
{
	char	**new_env;
	int		len;

	len = 0;
	if (check == 0)
	{
		new_env = (char **)malloc(sizeof(char *) * (s + 2));
		if (new_env == NULL)
			return (NULL);
	}
	else
	{
		if (value != NULL)
		{
			new_env = (char **)malloc(sizeof(char *) * (s + 2));
			if (new_env == NULL)
				return (NULL);
		}
		else
		{
			new_env = (char **)malloc(sizeof(char *) * (s + 1));
			if (new_env == NULL)
				return (NULL);
		}
	}
	while (env_or_xenv && env_or_xenv[len])
	{
		new_env[len] = ft_substr(env_or_xenv[len], 0,
				ft_strlen(env_or_xenv[len]));
		if (new_env[len] == NULL)
		{
			check = -1;
			while (++check < len)
				free(new_env[check]);
			while (env_or_xenv && env_or_xenv[len])
				free(env_or_xenv[len++]);
			free(new_env);
			return (NULL);
		}
		free(env_or_xenv[len]);
		len++;
	}
	new_env[len] = NULL;
	if (check == 1)
	{
		if (value != NULL)
		{
			if (add_var(new_env, var, value, len))
			{
				while (--len >= 0)
					free(new_env[len]);
				free(new_env);
				free(env_or_xenv);
				return (NULL);
			}
			new_env[++len] = NULL;
		}
	}
	else
	{
		if (add_var(new_env, var, value, len))
		{
			while (--len >= 0)
				free(new_env[len]);
			free(new_env);
			free(env_or_xenv);
			return (NULL);
		}
		new_env[++len] = NULL;
	}
	free(env_or_xenv);
	return (new_env);
}

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
