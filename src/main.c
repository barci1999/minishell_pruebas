/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 15:25:26 by pablalva          #+#    #+#             */
/*   Updated: 2025/05/29 10:54:37 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pruebas.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell shell;
	char	*input = NULL;
	t_list *temp = NULL;
	t_mini mini;
	t_general data_gen;
	ft_memset(&temp,0,sizeof(temp));

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
				if(nbr_quotes_ok(input) == false)
					printf("error en numero de comillas\n");
				else 
				{
					if(num_pipes(input,'|') != 0)
						temp = asigg_cont_list(mat_to_list(ft_split_quotes(input,'|')),&data_gen,&mini);
					else
					{
						node_to_end(&temp,new_doble_node(input));
						temp = asigg_cont_list(temp,&data_gen,&mini);
					}
					if(temp)
					{
						comprove_heredocs(temp);
							if(num_pipes(input,'|') == 0 && is_builting(temp->cmd_path))
							{
								execute_builting(temp,&mini);
								close_herdocs(temp,&data_gen);
							}
							else
							{
								execute_list(temp,data_gen,&mini);
								close_herdocs(temp,&data_gen);
							}
						print_cmd_list(temp);
						free_list(&temp);
						free_env_array(data_gen.my_env);//free añadido para liberar el array
						data_gen.my_env = NULL;//esto es una recomendacion
					}
					else
						ft_putendl_fd("Error",0);
				}
				free(input);	
			}
	}
	free_env_list(&mini);
	return (0);
}

//he usado esto valgrind --leak-check=full --trace-children=yes --track-fd=yes ./mini