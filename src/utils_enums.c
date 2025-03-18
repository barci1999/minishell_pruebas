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
			if (current->token == WORD && (current->prev->token == CMD || current->prev->token == BUILTIN))
				current->token = ARG;
			else if (current->token == WORD
				&& current->prev->token == REDIR_OUT)
				current->token = OUTFILE;
			else if (current->token == WORD
				&& current->prev->token == REDIR_APPEND)
				current->token = OUTFILE_APPEND;
		}
		if (current->next != NULL)
		{
			if (current->token == WORD && current->next->token == REDIR_IN)
				current->token = INFILE;
		}
		current = current->next;
	}
}
void	sintax_list(t_list **list)
{
	t_list *current;
	current = *list;
	while (current)
	{
		if(current->token == CMD || current->token == BUILTIN)
			sintax_cmd;
		else if(current->token == )
	}
	

}