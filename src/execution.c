/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:38:39 by pablalva          #+#    #+#             */
/*   Updated: 2025/05/14 18:44:06 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pruebas.h"

void	execute_list(t_list *list, t_general general)
{
	t_list	*current;
	int		i;

	current = list;
	i = 0;
	general.pids = gen_pid_array(list_size(&list));
	general.pipes = gen_pipes_array(list_size(&list));
	if (!general.pids || !general.pipes)
	{
		free_list(&list);
		exit(1);
	}
	while (current)
	{
		open_and_redir_in(current, &general, i);
		open_and_redir_out(current, &general, i);
		current = current->next;
		i++;
	}
}
