/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_enums.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:47:09 by pablalva          #+#    #+#             */
/*   Updated: 2025/04/07 17:34:14 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pruebas.h"

void	change_word(t_list **list)
{
	t_list	*current;

	current = *list;
	while (current)
	{
		if (current->prev != NULL)
		{
			if (current->token == WORD && current->prev->token == REDIR_OUT)
				current->token = FD;
			else if (current->token == WORD
				&& current->prev->token == REDIR_APPEND)
				current->token = FD;
			else if (current->prev->token == HEREDOC)
				current->token = DELIM;
			else if (current->prev->token == REDIR_IN)
				current->token = FD;
			else if(current->token == WORD && current->prev->token == DELIM)
				current->token = FD;
			else if (current->token == WORD && (current->prev->token != PIPE))
				current->token = ARG;
		}
		if (current->next != NULL)
		{
			if (current->token == WORD && current->next->token == REDIR_IN)
				current->token = FD;
		}
		current = current->next;
	}
}
void	sintax_list(t_list **list)
{
	t_list			*current;
	t_list			*temp;
	t_token_type	type;

	current = *list;
	while (current)
	{
		temp = current;
		type = temp->token;
		if (type == CMD && sintax_cmd(type, temp) == -1)
		{
			fun_error_sintax("Error in sintax_cmd", list);
		}
		if (type == BUILTIN && sintax_builting(type, temp) == -1)
		{
			fun_error_sintax("Error int sintax_builting", list);
		}
		if (type == ARG && sintax_arg(type, temp) == -1)
		{
			fun_error_sintax("Error in sintax_arg", list);
		}
		if (type == PIPE && sintax_pipe(type, temp) == -1)
		{
			fun_error_sintax("Error in sintax_pipe", list);
		}
		if ((type == REDIR_OUT || type == REDIR_APPEND)
			&& sintax_redirs_out(type, temp) == -1)
		{
			fun_error_sintax("Error in sintax_redirs_out", list);
		}
		if (type == REDIR_IN && sintax_redir_in(type, temp) == -1)
		{
			fun_error_sintax("Error in sintax_redir_in", list);
		}
		if (type == HEREDOC && sintax_heredoc(type, temp) == -1)
		{
			fun_error_sintax("Error in sintax_heredoc", list);
		}
		if (type == ENV_VAR && sintax_env_var(type, temp) == -1)
		{
			fun_error_sintax("Error in sintax_env_var", list);
		}
		if (type == DOLLAR_EXIT && sintax_dollar_exit(type, temp) == -1)
		{
			fun_error_sintax("Error in sintax_dollar_exit", list);
		}
		if (type == FD && sintax_fd(type, temp) == -1)
		{
			fun_error_sintax("Error in sintax_fd", list);
		}
		current = current->next;
	}
}
