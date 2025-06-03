/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_doble_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 12:39:07 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/02 22:07:08 by pablalva         ###   ########.fr       */
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
	new_node->order = 0;
	new_node->variable = NULL; 
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
	t_list	*next;

	if (!list || !*list)
		return;
	
	temp = *list;
	while (temp)
	{
		next = temp->next;

		free(temp->cmd_name);
		free(temp->cmd_path);
		free(temp->content);
		ft_free_mat(temp->delim);
		ft_free_mat(temp->cmd_arg);
		ft_free_mat(temp->redirecc);
		ft_free_mat(temp->fd);

		free(temp);
		temp = next;
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
	ft_free_mat(mat);
	return (list);
}
size_t	list_size(t_list **list)
{
	size_t	result;
	t_list	*current;

	if (!*list)
		return (0);
	result = 0;
	current = *list;
	while (current)
	{
		result++;
		current = current->next;
	}
	return (result);
}
