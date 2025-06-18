/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:50:31 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/18 16:19:26 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_exec_data(t_list **list, t_general *general)
{
	general->pids = gen_pid_array((size_t)general->total_cmd);
	general->pipes = gen_pipes_array((size_t)general->total_cmd);
	if (!general->pids)
	{
		free_list(list);
		exit(1);
	}
}

void	redir_and_exec(t_list *node, t_general *gen, t_mini *mini, t_list *list)
{
	open_and_redir_in(node, gen, gen->pipe_index);
	open_and_redir_out(node, gen, gen->pipe_index, gen->total_cmd);
	execute_node(node, gen, mini, &list);
}

void	handle_child(t_list *node, t_general *gen, t_mini *mini, t_list *list)
{
	int	ret;

	close_unused_pipes(gen->pipe_index, gen->total_cmd, gen->pipes);
	ret = try_to_open_all_fds(node);
	if (ret == 0)
		redir_and_exec(node, gen, mini, list);
	exit(1);
}

void	handle_parent(pid_t pid, t_general *gen, int *i)
{
	gen->pids[*i] = pid;
	(*i)++;
}

void	end_exec(t_list *list, t_general *general, int i)
{
	close_all_pipes(general->total_cmd, general);
	wait_all_procces(general, i);
	close_herdocs(list, general);
}
