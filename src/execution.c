/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:38:39 by pablalva          #+#    #+#             */
/*   Updated: 2025/05/16 17:23:32 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pruebas.h"

static void	precreate_output_files(t_list *list)
{
	t_list *node = list;
	int fd;

	while (node)
	{
		if (identify_reddir_out(node) == FD)
			fd = open(node->fd[return_fd_out(node)], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (identify_reddir_out(node) == FD_APPEND)
			fd = open(node->fd[return_fd_out(node)], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd != -1)
			close(fd);
		node = node->next;
	}
}


void 	execute_node(t_list *node,t_general *general)
{
	if (!is_builting(node->cmd_path))
		execve(node->cmd_path,node->cmd_arg,general->my_env);
	
	
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
	precreate_output_files(list);
	while (current)
	{
		pid = fork();
		if(pid == -1)
			exit (1);
		else if(pid == 0)
		{
			open_and_redir_in(current, &general, i);
			open_and_redir_out(current, &general, i);
			execute_node(current,&general);
		}
		else
		{
			general.pids[i] = pid;
			current = current->next;
			i++;
		}
	}
	while (j <= i)
	{
		waitpid(general.pids[j],&status,0);
		if(j == i - 1)
			general.last_exit_code = WEXITSTATUS(status);
		j++;
	}
	
}
