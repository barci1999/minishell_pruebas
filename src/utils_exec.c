/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:17:23 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/18 18:41:33 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_unused_pipes(int pipe_index, int total_cmds, int **pipes)
{
	int	j;

	j = 0;
	while (j < total_cmds - 1)
	{
		if (j != pipe_index)
			close(pipes[j][1]);
		if (j != pipe_index - 1)
			close(pipes[j][0]);
		j++;
	}
}

void	handle_external_command(t_list *node, t_general *general)
{
	struct stat	sb;

	if (*node->cmd_path == '\0')
	{
		ft_free_mat_void((void **)general->my_env, ft_matlen(general->my_env));
		exit(0);
	}
	if (stat(node->cmd_path, &sb) == 0 && S_ISDIR(sb.st_mode))
		print_error_exit(node->cmd_path, "Is a directory", 126);
	if (access(node->cmd_path, F_OK) != 0)
		print_error_exit(node->cmd_path, "No such file or directory", 127);
	if (access(node->cmd_path, X_OK) != 0)
		print_error_exit(node->cmd_path, "Permission denied", 126);
	if (execve(node->cmd_path, node->cmd_arg, general->my_env) == -1)
	{
		ft_free_mat_void((void **)general->my_env, ft_matlen(general->my_env));
		exit(1);
	}
}
