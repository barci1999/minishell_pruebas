/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 15:25:26 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/18 22:48:37 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_list		*temp;
	t_mini		mini;
	t_general	data_gen;

	if (argc < 1)
		return (1);
	(void)argv;
	temp = NULL;
	init_structs(&mini, &data_gen, envp);
	while (1)
	{
		input = readline("minishell -> ");
		if (!input)
			break ;
		if (*input == '\0')
		{
			free(input);
			continue ;
		}
		if (handle_input(input, &temp, &mini, &data_gen) == -1)
			break ;
		free(input);
	}
	return (free_all(&mini), 0);
}
