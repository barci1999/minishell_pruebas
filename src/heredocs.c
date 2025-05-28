/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 19:50:42 by pablalva          #+#    #+#             */
/*   Updated: 2025/05/28 18:24:46 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pruebas.h"

void	open_the_heredoc(t_list *list, int redir_index, int delim_index)
{
	char	*line;
	int		fd;
	int		fd_index;

	fd_index = redir_index;
	if (!list->fd[fd_index] || !list->redirecc[redir_index])
		return ;
	fd = open(list->fd[fd_index], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open herdoc");
		return ;
	}
	while (1)
	{
		line = readline("heredoc-> ");
		if (!line)
			break ;
		if (ft_strcmp(line, list->delim[delim_index]) == 0)
			break ;
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
}

void	open_all_herdocs(t_list *list)
{
	int	i;
	int	delim_index;

	i = 0;
	delim_index = 0;
	while (list->redirecc[i])
	{
		if (ft_strcmp(list->redirecc[i], "<<") == 0)
		{
			open_the_heredoc(list, i, delim_index);
			delim_index++;
		}
		i++;
	}
}


void	comprove_heredocs(t_list *list)
{
	t_list *current;
	current = list;
	while (current)
	{
		if (have_a_heredoc(current) == 1)
		{
			open_all_herdocs(current);
			current = current->next;
		}
		else
			current = current->next;
	}
}