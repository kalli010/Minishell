/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:18:09 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/25 14:18:10 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	find_env_variable(char **env, char *str, int *s)
{
	while (env != NULL && env[++(*s)])
	{
		if (!ft_strncmp(env[*s], str, ft_strlen(str))
			&& env[*s][ft_strlen(str)] == '=')
			return (*s);
	}
	return (-1);
}

char	*extract_env_value(char **env, int index, char *str)
{
	char	*new_var;
	int		st;
	int		i;

	new_var = NULL;
	st = ft_strlen(str);
	st++;
	i = 0;
	while (env[index][i])
		i++;
	new_var = (char *)malloc(sizeof(char) * (i - st + 1));
	if (new_var == NULL)
		return (NULL);
	new_var[0] = '\0';
	ft_cpy(new_var, &env[index][st]);
	new_var[i - st] = '\0';
	return (new_var);
}

char	*ft_getenv(char **env, char *str, int s)
{
	int	index;

	if (str == NULL)
		return (NULL);
	index = find_env_variable(env, str, &s);
	if (index == -1)
		return (NULL);
	return (extract_env_value(env, index, str));
}
