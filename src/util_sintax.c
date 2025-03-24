/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_sintax.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-19 20:15:19 by pablalva          #+#    #+#             */
/*   Updated: 2025-03-19 20:15:19 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pruebas.h"

int	sintax_cmd(t_token_type type, t_list *comprove)
{
	if (type == CMD)
	{
		if (comprove->prev == NULL || comprove->prev->token == PIPE)
		{
			if (comprove->next == NULL || comprove->next->token == ARG
				|| comprove->next->token == REDIR_OUT
				|| comprove->next->token == HEREDOC
				|| comprove->next->token == PIPE)
				{
					return (1);
				}
		}
	}
	return (-1);
}

int	sintax_arg(t_token_type type, t_list *comprove)
{
	if (type == ARG)
	{
		if (comprove->prev == NULL)
			return (-1);
		else if (comprove->prev->token == CMD)
		{
			if (comprove->next == NULL || comprove->next->token == REDIR_OUT
				|| comprove->next->token == REDIR_APPEND
				|| comprove->next->token == PIPE)
				{

					return (1);
				}
		}
	}
	return (-1);
}

int	sintax_pipe(t_token_type type, t_list *comprove)
{
	if (type == PIPE)
	{
		if (comprove->prev == NULL || comprove->next == NULL)
			return (-1);
		else if (comprove->prev->token == CMD || comprove->prev->token == ARG
			|| comprove->prev->token == BUILTIN)
		{
			if (comprove->next->token == CMD
				|| comprove->next->token == BUILTIN)
				return (1);
		}
	}
	return (-1);
}

int	sintax_redirs_out(t_token_type type, t_list *comprove)
{
	if (type == REDIR_OUT || type == REDIR_APPEND)
	{
		if (comprove->prev == NULL || comprove->next == NULL)
			return (-1);
		else if (comprove->prev->token == CMD || comprove->prev->token == ARG
			|| comprove->prev->token == BUILTIN)
		{
			if (comprove->next->token == FD)
				return (1);
		}
	}
	return (-1);
}

int	sintax_redir_in(t_token_type type, t_list *comprove)
{
	if (type == REDIR_IN)
	{
		if (comprove->prev == NULL || comprove->next == NULL)
			return (-1);
		else if (comprove->prev->token == CMD || comprove->prev->token == ARG
			|| comprove->prev->token == BUILTIN)
		{
			if (comprove->next->token == FD)
				return (1);
		}
	}
	return (-1);
}
