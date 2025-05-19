/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:08:47 by pablalva          #+#    #+#             */
/*   Updated: 2025/05/19 16:37:13 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pruebas.h"

static void	print_export_list(t_mini *mini)
{
	t_list	*node;
	int		printed;
	int		total;
	int		current_order;

	printed = 0;
	total = list_size(&mini->first_node);
	nodes_order(mini);
	current_order = 0; // Asigna el "order" a cada nodo
	while (printed < total)
	{
		node = mini->first_node;
		while (node)
		{
			if (node->order == current_order)
			{
				print_single_export(node);
				printed++;
				// Avanza al siguiente "order"
				break ;
			}
			node = node->next;
		}
		current_order++;
	}
}
int	ft_export(char **args, t_mini *mini)
{
	if (!args[1])
	{
		mini->total_nodes = list_size(&mini->first_node);
		nodes_order(mini);
		print_export_list(mini);
		return (0);
	}
	printf("se ha usado mi export\n");
	return (export_args(args, mini));
}