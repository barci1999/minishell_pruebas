/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:38:39 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/18 16:20:29 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_node(t_list *node, t_general *general, t_mini *mini,
		t_list **lista)
{
	if (!node->cmd_path)
	{
		ft_free_mat_void((void **)general->my_env, ft_matlen(general->my_env));
		ft_free_mat_void((void **)general->pipes, (list_size(lista)) - 1);
		ft_free_array_void(general->pids);
		free_list(lista);
		free_all(mini);
		exit(0);
	}
	if (!is_builting(node->cmd_path))
	{
		handle_external_command(node, general);
	}
	else
	{
		execute_builting(node, mini);
		ft_free_mat_void((void **)general->my_env, ft_matlen(general->my_env));
		ft_free_mat_void((void **)general->pipes, (list_size(lista)) - 1);
		ft_free_array_void(general->pids);
		free_list(lista);
		free_all(mini);
		exit(g_exit_status);
	}
}

void	execute_builtin_with_redir(t_list *node, t_general *data_gen,
		t_mini *mini)
{
	int	saved_stdout;
	int	saved_stdin;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	if (node->redirecc)
	{
		open_and_redir_out(node, data_gen, 0, 0);
		open_and_redir_in(node, data_gen, 0);
	}
	execute_builting(node, mini);
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdout);
	close(saved_stdin);
}

void	execute_builting(t_list *node, t_mini *mini)
{
	if (ft_strcmp(node->cmd_path, "echo") == 0)
		g_exit_status = ft_echo(node->cmd_arg);
	else if (ft_strcmp(node->cmd_path, "export") == 0)
		g_exit_status = ft_export(node->cmd_arg, mini);
	else if (ft_strcmp(node->cmd_path, "env") == 0)
		g_exit_status = ft_env(node->cmd_arg, mini);
	else if (ft_strcmp(node->cmd_path, "pwd") == 0)
		g_exit_status = ft_pwd();
	else if (ft_strcmp(node->cmd_path, "cd") == 0)
		g_exit_status = ft_cd(node->cmd_arg);
	else if (ft_strcmp(node->cmd_path, "exit") == 0)
		g_exit_status = ft_exit(node->cmd_arg);
	else if (ft_strcmp(node->cmd_path, "unset") == 0)
		g_exit_status = ft_unset(node->cmd_arg, mini);
}

void	execute_list(t_list *list, t_general general, t_mini *mini)
{
	t_list	*cur;
	int		i;
	pid_t	pid;

	cur = list;
	i = 0;
	general.pipe_index = 0;
	general.total_cmd = (int)list_size(&list);
	init_exec_data(&list, &general);
	while (cur)
	{
		pid = fork();
		if (pid == -1)
			exit(1);
		if (pid == 0)
			handle_child(cur, &general, mini, list);
		handle_parent(pid, &general, &i);
		cur = cur->next;
		if (cur)
			general.pipe_index++;
	}
	end_exec(list, &general, i);
}
