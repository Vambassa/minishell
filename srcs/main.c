/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calecia <calecia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 01:14:27 by vambassa          #+#    #+#             */
/*   Updated: 2022/03/28 20:34:28 by calecia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_mini	shell;

	(void)argc;
	(void)argv;
	g_exit_code = 0;
	init_shell(&shell);
	init_env(&shell, env);
	init_export_env(&shell, env);
	define_shell_level(&shell);
	while (1)
	{
		handle_signals();
		shell.input = readline("minishell$ ");
		if (!shell.input)
			exit(g_exit_code);
		if (shell.input[0] != '\0')
			add_history(shell.input);
		parser(&shell);
		if (shell.cmds)
			execute_commands(&shell, shell.cmds);
		free_shell(&shell);
	}
	return (0);
}
