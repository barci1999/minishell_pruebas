/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 22:38:33 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/19 19:24:42 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_exec(t_general *data_gen, t_list **temp)
{
	free_list(temp);
	free_env_array(data_gen->my_env);
	data_gen->my_env = NULL;
}

void	init_structs(t_mini *mini, t_general *data_gen, char **envp)
{
	ft_memset(mini, 0, sizeof(t_mini));
	ft_memset(data_gen, 0, sizeof(t_general));
	mini->first_node = NULL;
	mini->total_nodes = 0;
	init_env_list(mini, envp);
	ctrls(0);
	g_exit_status = 0;
}

void	execute_pipeline(char *input, t_list *temp, t_general *data_gen,
		t_mini *mini)
{
	if (num_pipes(input, '|') == 0 && is_builting(temp->cmd_path))
	{
		if (try_to_open_all_fds(temp) == 0)
			execute_builtin_with_redir(temp, data_gen, mini);
	}
	else
		execute_list(temp, *data_gen, mini);
	close_herdocs(temp, data_gen);
}

void	free_error_case(t_general *data_gen, t_list **temp)
{
	ft_free_mat_void((void **)data_gen->my_env, ft_matlen(data_gen->my_env));
	ft_free_mat_void((void **)data_gen->pipes, list_size(temp) - 1);
	ft_free_array_void(data_gen->pids);
	free_list(temp);
}

int	handle_input(char *input, t_list **temp, t_mini *mini, t_general *data_gen)
{
	add_history(input);
	if (comprove_input(input) == 1)
	{
		printf("invalid input\n");
		g_exit_status = 2;
		return (0);
	}
	if (num_pipes(input, '|') != 0)
		*temp = asigg_cont_list(mat_to_list(ft_split_quotes(input, '|')),
				data_gen, mini);
	else
	{
		node_to_end(temp, new_doble_node(input));
		*temp = asigg_cont_list(*temp, data_gen, mini);
	}
	if (!*temp)
		return (free_error_case(data_gen, temp), 0);
	if (comprove_heredocs(*temp) == -1)
		close_herdocs(*temp, data_gen);
	else
		execute_pipeline(input, *temp, data_gen, mini);
	cleanup_exec(data_gen, temp);
	return (0);
}
