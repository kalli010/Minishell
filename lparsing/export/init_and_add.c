/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:38:44 by zelkalai          #+#    #+#             */
/*   Updated: 2024/11/05 00:54:30 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_params(t_add_env_params *p_env, char **env, char *var, char *value)
{
	p_env->env_or_xenv = env;
	p_env->var = var;
	p_env->value = value;
}

int	add_new_var_to_env(char ***env, char ***xenv, t_set_var *sv, int s)
{
	t_add_env_params	p_env;
	t_add_env_params	p_xenv;

	init_params(&p_env, *env, sv->var, sv->value);
	p_env.s = s;
	p_env.check = 0;
	init_params(&p_xenv, *xenv, sv->var, sv->value);
	p_xenv.s = s;
	p_xenv.check = 1;
	if ((*env)[s] == NULL)
		*env = add_new_env(&p_env);
	*xenv = add_new_env(&p_xenv);
	if (*env == NULL || *xenv == NULL)
	{
		free(sv->var);
		free(sv->value);
		return (1);
	}
	return (0);
}

void	init_sv(t_set_var *sv, char *var, char *value)
{
	sv->var = var;
	sv->value = value;
}
