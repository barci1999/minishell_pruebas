/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:38:39 by pablalva          #+#    #+#             */
/*   Updated: 2025/05/12 12:54:39 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pruebas.h"

t_token_type identify_reddir_in(t_list *node)
{
	int i = 0;
	t_token_type result;
	result = STD_IN;
	while (node->redirecc[i])
	{
		if(ft_strcmp(node->redirecc[i],"<<") == 0)
			result = HEREDOC;
		else if(ft_strcmp(node->redirecc[i],"<") == 0)
			result = FD;
		i++;
	}
	if(result == STD_IN && node->prev)
		result = PIPE;
	return(result);
}
t_token_type identify_reddir_out(t_list *node)
{
	int i = 0;
	t_token_type result;
	result = STD_OUT;
	while (node->redirecc[i])
	{
		if(ft_strcmp(node->redirecc[i],">") == 0)
			result = FD;
		else if (ft_strcmp(node->redirecc[i],">>") == 0)
			result = FD_APPEND;
		i++;
	}
	if(result == STD_OUT && node->next)
		result = PIPE;
	return(result);
	
}
void execute_list(t_list *list)
{
	t_list *current;
	t_token_type redireccion_salida;
	current = list;
	identify_reddir_in(current);
	while (current)
	{
		redireccion_salida = identify_reddir_out(current);
		if(redireccion_salida == PIPE)
			printf("PIPE\n");
		else if(redireccion_salida == FD)
			printf("FD\n");
		else if(redireccion_salida == STD_OUT)
			printf("STD_out\n");
		else if(redireccion_salida == FD_APPEND)
			printf("fd_append\n");
		current = current->next;
	}
	
}