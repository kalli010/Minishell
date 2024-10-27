/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:51:28 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/26 19:13:22 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int ac, char **av, char **envp)
{
	char	*line;

	(void)ac, (void)av;
	init_helper();
	g_helper.envp = create_env(envp);
	g_helper.xenv = create_env(envp);
	while (1)
	{
		signal_handeler(BEFORE);
		line = readline("(minishell)-> ");
		init_helper_2();
		signal_handeler(PARENT);
		if (line == NULL)
		{
			printf("exit \n");
			free(line);
			(clean_env(g_helper.envp), clean_env(g_helper.xenv));
			exit(g_helper.exit_status);
		}
		if (ft_strlen(line) > 0)
			add_history(line);
		if (line)
			ft_minishell(line);
		printf("exit status: %d\n", g_helper.exit_status);
	}
	return (EXIT_SUCCESS);
}
