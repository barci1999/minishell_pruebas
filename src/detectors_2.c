/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detectors_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:37:19 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/16 18:38:28 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	return_fd_in(t_list *node)
{
	int	i;
	int	last_index;

	i = 0;
	last_index = -1;
	while (node->redirecc[i])
	{
		if (ft_strcmp(node->redirecc[i], "<") == 0
			|| ft_strcmp(node->redirecc[i], "<<") == 0)
			last_index = i;
		i++;
	}
	return (last_index);
}

int	return_fd_out(t_list *node)
{
	int	i;
	int	last_index;

	i = 0;
	last_index = -1;
	while (node->redirecc[i])
	{
		if (ft_strcmp(node->redirecc[i], ">") == 0
			|| ft_strcmp(node->redirecc[i], ">>") == 0)
			last_index = i;
		i++;
	}
	return (last_index);
}

t_token_type	identify_reddir_in(t_list *node)
{
	int				i;
	t_token_type	result;

	i = 0;
	result = STD_IN;
	if (!node->redirecc)
	{
		if (node->prev)
			return (PIPE);
		else
			return (STD_IN);
	}
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
	if (!node->redirecc)
	{
		if (node->next)
			return (PIPE);
		else
			return (STD_OUT);
	}
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

t_status_type	update_status(char **math_content, int *i, t_general *data_gen)
{
	if (is_redirec(math_content[*i]))
		return (REDIREC);
	else if (is_cmd(math_content[*i], data_gen) == 1)
		return (CMD);
	else
	{
		return (WORD);
	}
}
