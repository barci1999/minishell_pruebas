/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detectors_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:37:19 by pablalva          #+#    #+#             */
/*   Updated: 2025/05/14 18:43:57 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pruebas.h"

int	return_fd_in(t_list *node)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (node->redirecc[i])
	{
		if (ft_strcmp(node->redirecc[i], "<<") == 0
			|| ft_strcmp(node->redirecc[i], "<") == 0)
			result++;
		i++;
	}
	if (result != 0)
		return (result - 1);
	return (result);
}
int	return_fd_out(t_list *node)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (node->redirecc[i])
	{
		if (ft_strcmp(node->redirecc[i], ">>") == 0
			|| ft_strcmp(node->redirecc[i], ">") == 0)
			result++;
		i++;
	}
	if (result != 0)
		return (result - 1);
	return (result);
}
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
	int i;
	t_token_type result;

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