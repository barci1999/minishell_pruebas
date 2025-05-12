/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:38:39 by pablalva          #+#    #+#             */
/*   Updated: 2025/05/12 21:25:59 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pruebas.h"

t_token_type	identify_reddir_in(t_list *node)
{
	int				i;
	t_token_type	result;

	i = 0;
	result = STD_IN;
	while (node->redirecc[i])
	{
		if (ft_strcmp(node->redirecc[i], "<<") == 0)
			result = HEREDOC;
		else if (ft_strcmp(node->redirecc[i], "<") == 0)
			result = FD;
		i++;
	}
	if (result == STD_IN && node->prev)
		result = PIPE;
	return (result);
}
t_token_type	identify_reddir_out(t_list *node)
{
	int				i;
	t_token_type	result;

	i = 0;
	result = STD_OUT;
	while (node->redirecc[i])
	{
		if (ft_strcmp(node->redirecc[i], ">") == 0)
			result = FD;
		else if (ft_strcmp(node->redirecc[i], ">>") == 0)
			result = FD_APPEND;
		i++;
	}
	if (result == STD_OUT && node->next)
		result = PIPE;
	return (result);
}
void	execute_list(t_list *list)
{
	t_list *current;
	current = list;
	pid_t *pids;
	pids = gen_pid_array(list_size(&*list));
	if(!pids)
	{
		free_list(&*list);
		exit(1);
	}
	while (current)
	{
		
		current = current->next;
	}
}
