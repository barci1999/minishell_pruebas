/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:38:39 by pablalva          #+#    #+#             */
/*   Updated: 2025/05/19 19:52:03 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pruebas.h"

void execute_builting(t_list *node,t_mini *mini)
{
	if(ft_strcmp(node->cmd_path,"echo") == 0)
		ft_echo(node->cmd_arg);
	else if(ft_strcmp(node->cmd_path,"export") == 0)
		ft_export(node->cmd_arg,mini);
	else if(ft_strcmp(node->cmd_path,"env") == 0)
		ft_env(node->cmd_arg,mini);
	else if(ft_strcmp(node->cmd_path,"pwd") == 0)
		ft_pwd();
	else if(ft_strcmp(node->cmd_path,"cd") == 0)
		ft_cd(node->cmd_arg);
	else if(ft_strcmp(node->cmd_path,"exit") == 0)
		ft_exit(node->cmd_arg);
	else if(ft_strcmp(node->cmd_path,"unset")  == 0)
		ft_unset(node->cmd_arg,mini);
}

void 	execute_node(t_list *node,t_general *general,t_mini *mini)
{
	if (!is_builting(node->cmd_path))
	{
		execve(node->cmd_path,node->cmd_arg,general->my_env);
	}
	else if (is_builting(node->cmd_path))
	{
		execute_builting(node,mini);
		exit(1);
	}
}
void	execute_list(t_list *list, t_general general,t_mini *mini)
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
			execute_node(current,&general,mini);
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
