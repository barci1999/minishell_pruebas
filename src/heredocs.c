/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 19:50:42 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/13 20:40:36 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_heredoc_fd(t_list *list, int fd_index)
{
	int	fd;

	if (!list->fd[fd_index] || !list->redirecc[fd_index])
		return (-1);
	fd = open(list->fd[fd_index], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		perror("open heredoc");
	return (fd);
}

static int	is_delimiter(char *line, char *delimiter)
{
	return (ft_strcmp(line, delimiter) == 0);
}

static void	handle_heredoc_loop(int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc-> ");
		if (g_exit_status == 130)
			break ;
		if (!line)
			break ;
		if (is_delimiter(line, delimiter))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
}

void	open_the_heredoc(t_list *list, int redir_index, int delim_index)
{
	int	fd;

	fd = open_heredoc_fd(list, redir_index);
	if (fd == -1)
		return ;
	handle_heredoc_loop(fd, list->delim[delim_index]);
	close(fd);
}
