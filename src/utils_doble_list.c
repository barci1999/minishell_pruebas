/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_doble_list,c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-16 12:39:07 by pablalva          #+#    #+#             */
/*   Updated: 2025-03-16 12:39:07 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pruebas.h"

t_list	*new_doble_node(t_token_type type, char *token)
{
	t_list	*new_node;

	new_node = malloc(1 * sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = ft_strdup(token);
	if (!new_node)
	{
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->token = type;
	return (new_node);
}

int	node_to_end(t_list **list, t_list *insert)
{
	t_list	*temp;

	if (!insert)
		return (-1);
	if (*list == NULL)
	{
		*list = insert;
		insert->next = NULL;
		insert->prev = NULL;
	}
	else
	{
		temp = *list;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = insert;
		insert->next = NULL;
		insert->prev = temp;
	}
	return (1);
}

void	free_list(t_list **list)
{
	t_list	*temp;

	while (list)
	{
		temp = *list;
		*list = (*list)->next;
		free(temp);
	}
	*list = NULL;
}

void	print_list(t_list *list)
{
	t_list	*now;

	now = list;
	while (now)
	{
		printf("%s   %i\n", now->content, now->token);
		now = now->next;
	}
}
void	change_word(t_list **list)
{
	t_list	*current;

	current = *list;
	while (current)
	{
		if (current->prev != NULL)
		{
			if (current->token == WORD && current->prev->token == CMD)
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
