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
	if (env_or_xenv[index] != NULL)
	{
		free(env_or_xenv[index]);
		env_or_xenv[index] = NULL;
	}
	env_or_xenv[index] = new_var;
	return (0);
}
