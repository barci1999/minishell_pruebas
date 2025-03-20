/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sintax3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-19 22:25:25 by pablalva          #+#    #+#             */
/*   Updated: 2025-03-19 22:25:25 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pruebas.h"

void	fun_error_sintax(char *error,t_list **list)
{
	free_list(list);
	ft_putendl_fd(error, 2);
	exit(2);
}
int	sintax_builting(t_token_type type, t_list *comprove)
{
	if (type == BUILTIN)
	{
		if (comprove->prev == NULL || comprove->prev->token == PIPE)
		{
			if (comprove->next != NULL)
			{
				if (comprove->next->token == ARG
					|| comprove->next->token == REDIR_OUT
					|| comprove->next->token == HEREDOC
					|| comprove->next->token == PIPE)
					return (1);
			}
			else
				return (1);
		}
	}
	return (-1);
}
