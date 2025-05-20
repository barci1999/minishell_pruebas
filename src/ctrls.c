/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:37:14 by ksudyn            #+#    #+#             */
/*   Updated: 2025/05/20 16:38:20 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pruebas.h"

void	ctrl_minishell(int signal, t_shell *shell)
{
	if (signal == SIGINT)
	{
		printf("🔴 Se ha usado Ctrl-C\n");
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		shell->last_exit_status = 1;
	}
	else if (signal == SIGQUIT)
	{
		printf("🔵 Se ha usado Ctrl-\\\n");
		rl_on_new_line();
		rl_redisplay();
	}
}


void	ctrl_child(int signal, t_shell *shell)
{
	if (signal == SIGINT)
	{
		printf("❌ Ctrl-C en hijo\n");
		shell->last_exit_status = 130;
	}
	else if (signal == SIGQUIT)
	{
		printf("❌ Ctrl-\\ en hijo\n");
		write(1, "Quit: 3\n", 8);
		shell->last_exit_status = 131;
	}
}

void	ctrls(int is_child)
{
	struct sigaction	sa;

	memset(&sa, 0, sizeof(sa)); // Limpia toda la estructura
	sigemptyset(&sa.sa_mask);   // Inicializa sa_mask correctamente
	if (is_child)
		sa.sa_handler = (void (*)(int))ctrl_child;
	else
		sa.sa_handler = (void (*)(int))ctrl_minishell;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
}