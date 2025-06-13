/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:39:25 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/13 15:46:44 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void try_to_open_all_fds_in(t_list *node)
{
	int i;
	int fd;
	i = 0;
	if(!node->redirecc)
		return;
	while (node->redirecc[i])
	{
		if(ft_strcmp(node->redirecc[i],"<<") == 0 || ft_strcmp(node->redirecc[i],"<") == 0)
		{
			fd = open(node->fd[i],O_RDONLY);
			if(fd == -1)
			{
				perror(node->fd[i]);
				exit(1);
			}
			close(fd);	
		}
		i++;
	}
}
void try_open_all_fds_out(t_list *node)
{
	int i;
	int fd;
	fd = 0;
	i = 0;
	if(!node->redirecc)
		return;
	while (node->redirecc[i])
	{
		if(ft_strcmp(node->redirecc[i],">") == 0)
		{
			fd = open(node->fd[i],O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if(fd == -1)
			{
				perror(node->fd[i]);
				exit(1);
			}
			close(fd);
		}
		else if (ft_strcmp(node->redirecc[i],">>") == 0)
		{
			fd = open(node->fd[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if(fd == -1)
			{
				perror(node->fd[i]);
				exit(1);
			}
			close(fd);
		}
		i++;
	}
	
}
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
		try_to_open_all_fds_in(node);
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
		try_open_all_fds_out(node);
		filename = node->fd[return_fd_out(node)];
		// ⚠️ Verifica que el directorio existe
		if (!dir_exists(filename))
		{
			perror(filename);
			exit(1);
		}
		// Abre el archivo según tipo de redirección
		if (redir_type == FD)
			fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			perror(filename);
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
