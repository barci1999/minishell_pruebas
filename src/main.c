/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 15:25:26 by pablalva          #+#    #+#             */
/*   Updated: 2025/05/12 12:24:59 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pruebas.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input = NULL;
	t_list *temp = NULL;
	t_general data_gen;
	ft_memset(&temp,0,sizeof(temp));

	(void)argv;
	(void)envp;
	if (argc < 1)
		return (1);
	if(envp)
		data_gen.my_env = ft_dup_mat(envp);
	//else
		//data_gen.my_env = gen_env();		
	while (1)
	{
		input = readline("minishell -> ");
		if (input == NULL)
			break ;
		if (*input != '\0')
			{
				if(nbr_quotes_ok(input) == false)
				{	
					printf("error en numero de comillas\n");
					exit(1);
				}
				add_history(input);
				if(num_pipes(input,'|') != 0)
					temp = asigg_cont_list(mat_to_list(ft_split_quotes(input,'|')),&data_gen);
				else
				{
					node_to_end(&temp,new_doble_node(input));
					temp = asigg_cont_list(temp,&data_gen);
				}
				comprove_heredocs(temp);
				execute_list(temp);
				print_cmd_list(temp);
				free_list(&temp);
				free(input);	
			}
	}
	ft_free_mat(data_gen.my_env);
	return (0);
}
