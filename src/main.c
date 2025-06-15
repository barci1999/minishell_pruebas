/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 15:25:26 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/15 22:11:50 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;
	char		*input;
	t_list		*temp;
	t_mini		mini;
	t_general	data_gen;
	int flag;

	flag = 0;
	input = NULL;
	temp = NULL;
	ft_memset(&temp, 0, sizeof(temp));
	ft_memset(&mini, 0, sizeof(t_mini));
	ft_memset(&data_gen, 0, sizeof(t_general));
	(void)argv;
	(void)envp;
	if (argc < 1)
		return (1);
	shell.last_exit_status = 0;
	mini.first_node = NULL;
	mini.total_nodes = 0;
	init_env_list(&mini, envp);
	ctrls(0);
	while (1)
	{
		input = readline("minishell -> ");
		if (input == NULL)
		{
			printf("🟡 Se ha usado Ctrl-D\n");
			break ;
		}
		if (*input != '\0')
		{
			add_history(input);
			if (nbr_quotes_ok(input) == false)
				printf("error en numero de comillas\n");
			else
			{
				if (num_pipes(input, '|') != 0)
				{
					temp = asigg_cont_list(mat_to_list(ft_split_quotes(input,
									'|')), &data_gen, &mini);
				}
				else
				{
					node_to_end(&temp, new_doble_node(input));
					temp = asigg_cont_list(temp, &data_gen, &mini);
				}
				//print_cmd_list(temp);
				if (temp)
				{
					if(comprove_heredocs(temp) == -1)
						close_herdocs(temp,&data_gen);
					else {
						if (num_pipes(input, '|') == 0
							&& is_builting(temp->cmd_path))
						{
							if(try_to_open_all_fds(temp) == 0)
							{
								execute_builtin_with_redir(temp, &data_gen, &mini);
							}
							close_herdocs(temp, &data_gen);
						}
						else
						{
							execute_list(temp, data_gen, &mini);
							close_herdocs(temp, &data_gen);
						}
						
					}
					free_list(&temp);
					free_env_array(data_gen.my_env);
						// free añadido para liberar el array
					data_gen.my_env = NULL;         
						// esto es una recomendacion
				}
			free(input);
			}
		}
	}
	free_env_list(&mini);
	return (0);
}

// he usado esto valgrind --show-leak-kinds=indirect --leak-check=full --trace-children=yes --track-fds=yes ./minishell	