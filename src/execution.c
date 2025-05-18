/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:38:39 by pablalva          #+#    #+#             */
/*   Updated: 2025/05/18 21:29:59 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pruebas.h"

void execute_builting(t_list *node)
{
	if(ft_strcmp(node->cmd_path,"echo") == 0)
		ft_echo(node->cmd_arg);
}

void 	execute_node(t_list *node,t_general *general)
{
	if (!is_builting(node->cmd_path))
	{
		execve(node->cmd_path,node->cmd_arg,general->my_env);
	}
	else if (is_builting(node->cmd_path))
	{
		execute_builting(node);
		exit(1);
	}
}
void	execute_list(t_list *list, t_general general)
{
	t_list	*current;
	int		i;
	pid_t pid;
	int status;
	int j = 0;

	current = list;
	i = 0;
	general.pids = gen_pid_array(list_size(&list));
	general.pipes = gen_pipes_array(list_size(&list));
	if (!general.pids || !general.pipes)
	{
		free_list(&list);
		exit(1);
	}
	while (current)
	{
		pid = fork();
		if(pid == -1)
			exit (1);
		if(pid == 0)
		{
			open_and_redir_in(current, &general, i);
			open_and_redir_out(current, &general, i);
			execute_node(current,&general);
		}
		else
		{
			if (i < (int)list_size(&list) - 1)
			{
				close(general.pipes[i][0]);
				close(general.pipes[i][1]);
			}
			general.pids[i] = pid;
			current = current->next;
			i++;
		}
	}
	while (j < i)
	{
		
		waitpid(general.pids[j],&status,0);
		if(j == i - 1)
			general.last_exit_code = WEXITSTATUS(status);
		j++;
	}
	
}
