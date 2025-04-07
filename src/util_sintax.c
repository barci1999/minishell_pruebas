/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_sintax.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:15:19 by pablalva          #+#    #+#             */
/*   Updated: 2025/04/07 16:34:50 by pablalva         ###   ########.fr       */
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
				|| comprove->next->token == PIPE
				|| comprove->next->token == REDIR_IN)
				{
					return (1);
				}
		}
	}
	return (-1);
}

int sintax_arg(t_token_type type, t_list *comprove)
{
    if (type == ARG)
    {
        if (comprove->prev == NULL)
            return (-1);
        else if (comprove->prev->token == CMD || comprove->prev->token == BUILTIN || comprove->prev->token == ARG)
        {
            if (comprove->next == NULL || comprove->next->token == REDIR_OUT
                || comprove->next->token == REDIR_APPEND
                || comprove->next->token == PIPE
                || comprove->next->token == ARG)
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
		printf("%i\n",type);
		if (comprove->prev == NULL || comprove->next == NULL)
			return (-1);
		else if (comprove->prev->token == CMD || comprove->prev->token == ARG
			|| comprove->prev->token == BUILTIN || comprove->prev->token == ENV_VAR)
		{
			if (comprove->next->token == FD || comprove->next->token == DELIM)
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
			{
				printf("hola\n");
				return (1);
			}
		}
	}
	return (-1);
}
