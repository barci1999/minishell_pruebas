/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_enums.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-18 18:47:09 by pablalva          #+#    #+#             */
/*   Updated: 2025-03-18 18:47:09 by pablalva         ###   ########.fr       */
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
			if (current->token == WORD && (current->prev->token == CMD
					|| current->prev->token == BUILTIN))
				current->token = ARG;
			else if (current->token == WORD
				&& current->prev->token == REDIR_OUT)
				current->token = FD;
			else if (current->token == WORD
				&& current->prev->token == REDIR_APPEND)
				current->token = FD;
			else if (current->prev->token == HEREDOC)
				current->token = DELIM;
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
	t_list	*current;
	t_list *temp;
	current = *list;
	t_builtin_type type;
	while (current)
	{
		temp = current;
		type = temp->token;
		if (sintax_cmd(type,temp) == -1)
			fun_error_sintax("Error in sintax_cmd \n",&list);
		else if(sintax_builting(type,temp) == -1)
			fun_error_sintax("Error int sintax_builting \n",&list);
		else if(sintax_arg(type,temp) == -1)
			fun_error_sintax("Error in sintax_arg \n",&list);
		else if(sintax_pipe(type,temp) == -1)
			fun_error_sintax("Error in sintax_pipe \n",&list);
		else if (sintax_redirs_out(type,temp) == -1)
			fun_error_sintax("Error in sintax_redirs_out\n",&list);
		else if (sintax_redir_in(type,temp) == -1)
			fun_error_sintax("Error in sintax_redir_in\n",&list);
		else if (sintax_heredoc(type,temp) == -1)
			fun_error_sintax("Error in sintax_heredoc\n",&list);
		else if (sintax_env_var(type,temp) == -1)
			fun_error_sintax("Error in sintax_env_var\n",&list);
		else if (sintax_dollar_exit(type,temp) == -1)
			fun_error_sintax("Error in sintax_dollar_exit\n",&list);
		else if (sintax_fd(type,temp) == -1)
			fun_error_sintax("Error in sintax_fd\n",&list);
		free(temp);
		free(type);
		current = current->next;
	}
}
