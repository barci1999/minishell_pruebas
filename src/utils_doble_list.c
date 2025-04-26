/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_doble_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 12:39:07 by pablalva          #+#    #+#             */
/*   Updated: 2025/04/26 14:03:56 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pruebas.h"

t_list	*new_doble_node(char *token)
{
	t_list	*new_node;

	new_node = malloc(1 * sizeof(t_list));
	if (!new_node)
		return (free(token), NULL);
	new_node->cmd_arg = NULL;
	new_node->cmd_name = NULL;
	new_node->cmd_path = NULL;
	new_node->fd = NULL;
	new_node->redirecc = NULL;
	new_node->delim = NULL;
	new_node->content = ft_strtrim(token, " \t\v\n\r\b\f");
	if (!new_node->content)
		return (free(new_node), free(token), NULL);
	return (new_node->next = NULL, new_node->prev = NULL, new_node);
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

t_list	*mat_to_list(char **mat)
{
	t_list	*list;
	int		i;

	list = NULL;
	i = -1;
	while (mat[++i])
	{
		if (node_to_end(&list, new_doble_node(mat[i])) == -1)
			return (free_list(&list), ft_free_mat(mat), NULL);
	}
	return (list);
}
