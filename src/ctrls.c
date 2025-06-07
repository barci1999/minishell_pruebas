/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:37:14 by ksudyn            #+#    #+#             */
/*   Updated: 2025/06/07 17:59:34 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_minishell(int signal)
{
	if (signal == SIGINT)
	{
		printf("🔴 Se ha usado Ctrl-C\n");
		ioctl(STDIN_FILENO, TIOCSTI,"\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		
		g_exit_status = 1;
	}
	else if (signal == SIGQUIT)
	{
		printf("🔵 Se ha usado Ctrl-\\\n");
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ctrl_child(int signal)
{
	if (signal == SIGINT)
	{
		printf("❌ Ctrl-C en hijo\n");
		g_exit_status = 130;
	}
	else if (signal == SIGQUIT)
	{
		printf("❌ Ctrl-\\ en hijo\n");
		write(1, "Quit: 3\n", 8);
		g_exit_status = 131;
	}
}

void	ctrls(int is_child)
{
	struct sigaction	sa;

	memset(&sa, 0, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	if (is_child)
		sa.sa_handler = (void (*)(int))ctrl_child;
	else
		sa.sa_handler = (void (*)(int))ctrl_minishell;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
}
