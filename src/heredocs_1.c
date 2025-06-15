/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 20:40:13 by ksudyn            #+#    #+#             */
/*   Updated: 2025/06/15 21:19:28 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	t_list	*current;

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

void	close_herdocs(t_list *list, t_general *gen)
{
	t_list	*current;
	int		i;
	char	*temp;
	char *temp_2;

	current = list;
	temp = NULL;
	temp_2 = NULL;
	i = 0;
	while (i <= gen->tem_heredoc)
	{
		temp_2 = ft_itoa(i);
		temp = ft_strjoin("temp_here_", temp_2);
		if (access(temp, F_OK) != -1)
			unlink(temp);
		free(temp);
		free(temp_2);
		i++;
	}
}
