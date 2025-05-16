/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:39:25 by pablalva          #+#    #+#             */
/*   Updated: 2025/05/16 17:47:46 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pruebas.h"

void	open_and_redir_in(t_list *node, t_general *general, int i)
{
	int	fd;

	fd = -2;
	printf("esto es la entrada %s\n",node->fd[return_fd_in(node)]);
	if (!node->prev && identify_reddir_in(node) == STD_IN)
		return ;
	if (!node->prev && identify_reddir_in(node) != STD_IN)
		fd = open(node->fd[return_fd_in(node)], O_RDONLY);
	else if (node->prev && (identify_reddir_in(node) != STD_IN
			&& identify_reddir_in(node) != PIPE))
		fd = open(node->fd[return_fd_in(node)], O_RDONLY);
	else if (node->prev && identify_reddir_in(node) == PIPE)
	{
		dup2(general->pipes[i - 1][0], STDIN_FILENO);
		close(general->pipes[i - 1][0]);
		return ;
	}
	printf("%i\n",identify_reddir_in(node));
	if (fd == -1)
	{
		perror("Error abriendo archivo para entrada");
		exit(1);
		return ;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}
void	open_and_redir_out(t_list *node, t_general *general, int i)
{
	int	fd;

	fd = -2;
	printf("esto es la salida %s\n",node->fd[return_fd_out(node)]);
	ft_putendl_fd(node->fd[return_fd_out(node)],0);
	if (!node->next && identify_reddir_out(node) == STD_OUT)
		return ;
	else if (!node->next && (identify_reddir_out(node) == FD
			|| identify_reddir_out(node) == FD_APPEND))
	{
		if (identify_reddir_out(node) == FD)
			fd = open(node->fd[return_fd_out(node)],
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (identify_reddir_out(node) == FD_APPEND)
			fd = open(node->fd[return_fd_out(node)],
					O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else if (node->next && identify_reddir_out(node) == PIPE)
	{
		dup2(general->pipes[i + 1][1], STDOUT_FILENO);
		close(general->pipes[i + 1][1]);
		return ;
	}
	if (fd == -1)
	{
		perror("Error abriendo archivo para salida");
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
