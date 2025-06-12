/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:38:39 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/12 19:33:40 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	handle_external_command(t_list *node, t_general *general)
{
	struct stat	sb;

	// Verificar si el archivo existe
	//printf("%s\n",node->cmd_path);
	if(*node->cmd_path == '\0')
		exit(0);
	if (access(node->cmd_path, F_OK) != 0)
	{
		print_cmd_error(node->cmd_path, "No such file or directory", 127);
		exit(127);
	}
	// Verificar si es un directorio
	if (stat(node->cmd_path, &sb) == 0 && S_ISDIR(sb.st_mode))
	{
		print_cmd_error(node->cmd_path, "Is a directory", 126);
		exit(126);
	}
	// Verificar si tiene permisos de ejecución
	if (access(node->cmd_path, X_OK) != 0)
	{
		print_cmd_error(node->cmd_path, "Permission denied", 126);
		exit(126);
	}
	// Ejecutar si todo está bien
	if (execve(node->cmd_path, node->cmd_arg, general->my_env) == -1)
		exit(1);
}

void	execute_node(t_list *node, t_general *general, t_mini *mini)
{
	if (!is_builting(node->cmd_path))
	{
		handle_external_command(node, general);
	}
	else
	{
		execute_builting(node, mini);
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
		open_and_redir_in(node, data_gen, 0);
		open_and_redir_out(node, data_gen, 0, 0);
	}
	execute_builting(node, mini);
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdout);
	close(saved_stdin);
}

void	close_unused_pipes(int pipe_index, int total_cmds, int **pipes)
{
	int	j;

	j = 0;
	while (j < total_cmds - 1)
	{
		if (j != pipe_index)
			close(pipes[j][1]); // escritura
		if (j != pipe_index - 1)
			close(pipes[j][0]); // lectura
		j++;
	}
}

void	execute_list(t_list *list, t_general general, t_mini *mini)
{
	t_list	*current;
	int		i;
	pid_t	pid;
	int		total_cmds;
	int		pipe_index;

	total_cmds = (int)list_size(&list);
	pipe_index = 0;
	current = list;
	i = 0;
	general.pids = gen_pid_array((size_t)total_cmds);
	general.pipes = gen_pipes_array((size_t)total_cmds);
	if (!general.pids)
	{
		free_list(&list);
		exit(1);
	}
	while (current)
	{
		pid = fork();
		if (pid == -1)
			exit(1);
		if (pid == 0)
		{
			close_unused_pipes(pipe_index, total_cmds, general.pipes);
			open_and_redir_in(current, &general, pipe_index);
			open_and_redir_out(current, &general, pipe_index, total_cmds);
			execute_node(current, &general, mini);
		}
		else
		{
			general.pids[i] = pid;
			current = current->next;
			i++;
			if (current)
				pipe_index++;
		}
	}
	close_all_pipes(total_cmds, &general);
	wait_all_procces(&general, i);
	close_herdocs(list, &general);
}
