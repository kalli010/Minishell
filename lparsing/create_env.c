/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:50:09 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/19 20:50:10 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	clean_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		free(env[i]);
	free(env);
}

int	env_size(char **str)
{
	int	s;

	s = 0;
	while (str[s])
		s++;
	return (s);
}

char	**create_env(char **envp)
{
	char	**env;
	int		s;
	int		i;

	i = -1;
	s = env_size(envp);
	env = (char **)malloc(sizeof(char *) * (s + 1));
	if (env == NULL)
		return (NULL);
	while (envp[++i])
	{
		env[i] = ft_substr(envp[i], 0, ft_strlen(envp[i]));
		if (env[i] == NULL)
		{
			while (--i >= 0)
				free(env[i]);
			free(env);
		}
	}
	env[i] = NULL;
	return (env);
}
