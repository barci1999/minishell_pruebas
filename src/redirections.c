/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:39:25 by pablalva          #+#    #+#             */
/*   Updated: 2025/05/29 18:23:57 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pruebas.h"

void	open_and_redir_in(t_list *node, t_general *general, int i)
{
	int	fd;

	fd = -2;
	if (!node->prev && identify_reddir_in(node) == STD_IN)
		return ;
	if (!node->prev && identify_reddir_in(node) != STD_IN)
	{
		printf("popo\n");
		fd = open(node->fd[return_fd_in(node)], O_RDONLY);
	}
	else if (node->prev && (identify_reddir_in(node) != STD_IN
			&& identify_reddir_in(node) != PIPE))
		fd = open(node->fd[return_fd_in(node)], O_RDONLY);
	else if (node->prev && identify_reddir_in(node) == PIPE)
	{
		if (!general->pipes[i])
		{
			printf("coca cola\n");
			printf("%i\n", i);
		}
		dup2(general->pipes[i][0], STDIN_FILENO);
		close(general->pipes[i][1]);
		return ;
	}
	if (fd == -1)
	{
		perror("Error abriendo archivo para entrada");
		exit(1);
		return ;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}
// static void	no_node_next(t_list *node, int *fd)
// {
// 	if (!node->next && identify_reddir_out(node) == STD_OUT)
// 		return ;
// 	else if (!node->next && (identify_reddir_out(node) == FD
// 			|| identify_reddir_out(node) == FD_APPEND))
// 	{
// 		if (identify_reddir_out(node) == FD)
// 			*fd = open(node->fd[return_fd_out(node)],
// 					O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		else if (identify_reddir_out(node) == FD_APPEND)
// 			*fd = open(node->fd[return_fd_out(node)],
// 					O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	}
// }
// static void	node_next(t_list *node, t_general *general, int *i, int *fd)
// {
// 	if (node->next && (identify_reddir_out(node) == FD
// 			|| identify_reddir_out(node) == FD_APPEND))
// 	{
// 		if (identify_reddir_out(node) == FD)
// 			*fd = open(node->fd[return_fd_out(node)],
// 					O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		else if (identify_reddir_out(node) == FD_APPEND)
// 			*fd = open(node->fd[return_fd_out(node)],
// 					O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	}
// 	else if (node->next && identify_reddir_out(node) == PIPE)
// 	{
// 		dup2(general->pipes[*i][1], STDOUT_FILENO);
// 		close(general->pipes[*i][1]);
// 		close(general->pipes[*i][0]);
// 		return ;
// 	}
// }
void	open_and_redir_out(t_list *node, t_general *general, int i,
		int total_cmds)
{
	int		fd;
	int		out_type;
	char	*filename;

	fd = -1;
	out_type = identify_reddir_out(node);
	if (out_type == FD || out_type == FD_APPEND)
	{
		filename = node->fd[return_fd_out(node)];
		if (out_type == FD)
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
	}
	else if (out_type == PIPE)
	{
		// Solo si no es el último comando
		if (i < total_cmds - 1)
		{
			dup2(general->pipes[i][1], STDOUT_FILENO);
			close(general->pipes[i][0]);
			close(general->pipes[i][1]);
		}
	}
	else if (out_type == STD_OUT)
	{
		// No redirección, solo cerrar pipes que no se usan en este hijo
		if (i < total_cmds - 1)
		{
			close(general->pipes[i][0]);
			close(general->pipes[i][1]);
		}
	}
}
