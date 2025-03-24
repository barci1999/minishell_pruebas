/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sintax2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-19 20:15:12 by pablalva          #+#    #+#             */
/*   Updated: 2025-03-19 20:15:12 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pruebas.h"

int	sintax_heredoc(t_token_type type, t_list *comprove)
{
	if (type == HEREDOC)
	{
		if (comprove->prev == NULL || comprove->next == NULL)
			return (-1);
		else if (comprove->prev->token == CMD || comprove->prev->token == ARG
			|| comprove->prev->token == BUILTIN)
		{
			if (comprove->next->token == DELIM)
				return (1);
		}
	}
	return (-1);
}
int	sintax_env_var(t_token_type type, t_list *comprove)
{
	if (type == ENV_VAR)
	{
		if (comprove->prev == NULL)
			return (-1);
		else if (comprove->prev->token == CMD || comprove->prev->token == ARG
			|| comprove->prev->token == BUILTIN)
		{
			if (comprove->next == NULL || comprove->next->token == PIPE
				|| comprove->next->token == REDIR_OUT
				|| comprove->next->token == REDIR_APPEND)
				return (1);
		}
	}
	return (-1);
}
int	sintax_fd(t_token_type type, t_list *comprove)
{
	if (type == FD)
	{
		if (comprove->prev == NULL)
			return (-1);
		else if (comprove->prev->token == REDIR_IN
			|| comprove->prev->token == REDIR_APPEND
			|| comprove->prev->token == REDIR_OUT
			|| comprove->prev->token == DELIM)
		{
			if (comprove->next == NULL || comprove->next->token == PIPE
				|| comprove->next->token == REDIR_OUT
				|| comprove->next->token == REDIR_APPEND)
				return (1);
		}
	}
	return (-1);
}
int	sintax_dollar_exit(t_token_type type, t_list *comprove)
{
	if (type == DOLLAR_EXIT)
	{
		if (comprove->prev == NULL)
			return (-1);
		else if (comprove->prev->token == CMD || comprove->prev->token == ARG
			|| comprove->prev->token == BUILTIN)
		{
			if (comprove->next == NULL || comprove->next->token == REDIR_OUT
				|| comprove->next->token == REDIR_APPEND
				|| comprove->next->token == PIPE)
				return (1);
		}
	}
	return (-1);
}
