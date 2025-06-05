/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:39:25 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/05 14:59:21 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pruebas.h"

void	open_and_redir_in(t_list *node, t_general *general, int i)
{
	int	fd;
	int	redir_type;

	fd = -2;
	redir_type = identify_reddir_in(node);
	if (redir_type == STD_IN)
		return ;
	if (redir_type == FD || redir_type == HEREDOC)
	{
		fd = open(node->fd[return_fd_in(node)], O_RDONLY);
		if (fd == -1)
		{
			perror("Error abriendo archivo para entrada");
			exit(1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
		return ;
	}
	if (redir_type == PIPE && i > 0)
	{
		dup2(general->pipes[i - 1][0], STDIN_FILENO);
		close(general->pipes[i - 1][1]);
		close(general->pipes[i - 1][0]);
		return ;
	}
}

void	open_and_redir_out(t_list *node, t_general *general, int i,
		int total_cmds)
{
	int		fd;
	int		redir_type;
	char	*filename;

	fd = -1;
	redir_type = identify_reddir_out(node);
	if (redir_type == FD || redir_type == FD_APPEND)
	{
		filename = node->fd[return_fd_out(node)];
		if (redir_type == FD)
			fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			perror("Error abriendo archivo para salida");
			exit(1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
		return ;
	}
	if (redir_type == PIPE && i < total_cmds - 1)
	{
		dup2(general->pipes[i][1], STDOUT_FILENO);
		close(general->pipes[i][0]);
		close(general->pipes[i][1]);
		return ;
	}
	if (redir_type == STD_OUT && i < total_cmds - 1)
	{
		close(general->pipes[i][0]);
		close(general->pipes[i][1]);
	}
}
