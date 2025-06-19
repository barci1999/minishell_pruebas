/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:39:25 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/19 17:54:44 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	aux_try_open_all_fds(t_list *node, int i, int fd)
{
	if (ft_strcmp(node->redirecc[i], ">>") == 0)
	{
		if (!dir_exists(node->fd[i]))
			return (perror(node->fd[i]), -1);
		fd = open(node->fd[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return (perror(node->fd[i]), -1);
		close(fd);
	}
	if (ft_strcmp(node->redirecc[i], ">") == 0)
	{
		if (!dir_exists(node->fd[i]))
			return (perror(node->fd[i]), -1);
		fd = open(node->fd[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (perror(node->fd[i]), -1);
		close(fd);
	}
	return (0);
}

int	try_to_open_all_fds(t_list *node)
{
	int	i;
	int	fd;

	i = 0;
	if (!node->redirecc)
		return (0);
	while (node->redirecc[i])
	{
		if (ft_strcmp(node->redirecc[i], "<<") == 0
			|| ft_strcmp(node->redirecc[i], "<") == 0)
		{
			if (!dir_exists(node->fd[i]))
				return (perror(node->fd[i]), -1);
			fd = open(node->fd[i], O_RDONLY);
			if (fd == -1)
				return (perror(node->fd[i]), g_exit_status = 1, -1);
			close(fd);
		}
		if (aux_try_open_all_fds(node, i, fd))
			return (-1);
		i++;
	}
	return (0);
}

void	open_and_redir_in(t_list *node, t_general *general, int i)
{
	int	fd;
	int	redir_type;

	redir_type = identify_reddir_in(node);
	if (redir_type == STD_IN)
		return ;
	if (redir_type == FD || redir_type == HEREDOC)
	{
		fd = open(node->fd[return_fd_in(node)], O_RDONLY);
		if (fd == -1)
		{
			perror(node->fd[return_fd_in(node)]);
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

void	aux_open_and_redir_out(t_list *node, char *filename, int *fd)
{
	if (!dir_exists(filename))
		print_perror_exit(filename, 1);
	if (iden_red_out(node) == FD)
		*fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		*fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fd == -1)
		print_perror_exit(filename, 1);
	dup2(*fd, STDOUT_FILENO);
}

void	open_and_redir_out(t_list *node, t_general *general, int i,
		int total_cmds)
{
	int		fd;
	char	*filename;

	fd = -1;
	if (iden_red_out(node) == FD || iden_red_out(node) == FD_APPEND)
	{
		filename = node->fd[return_fd_out(node)];
		aux_open_and_redir_out(node, filename, &fd);
		if (i < (int)list_size(&node) - 1 && general->pipes[i])
			close(general->pipes[i][1]);
		close(fd);
		return ;
	}
	if (iden_red_out(node) == PIPE && i < total_cmds - 1)
	{
		dup2(general->pipes[i][1], STDOUT_FILENO);
		close(general->pipes[i][0]);
		close(general->pipes[i][1]);
		return ;
	}
	if (iden_red_out(node) == STD_OUT && i < total_cmds - 1)
	{
		close(general->pipes[i][0]);
		close(general->pipes[i][1]);
	}
}
