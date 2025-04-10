/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_doble_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 12:39:07 by pablalva          #+#    #+#             */
/*   Updated: 2025/04/10 18:52:48 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pruebas.h"

t_list	*new_doble_node(t_token_type type, char *token)
{
	t_list	*new_node;

	new_node = malloc(1 * sizeof(t_list));
	if (!new_node)
	{
		free(token);
		return (NULL);
	}
	new_node->content = ft_strdup(token);
	if (!new_node->content)
	{
		free(new_node);
		free(token);
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
	while ((*list)->next != NULL)
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
		printf("%s   %u\n", now->content, now->token);
		now = now->next;
	}
}

