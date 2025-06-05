/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:44:27 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/05 19:29:41 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset_env(t_mini *mini, char *variable)
{
	t_list	*node;

	node = mini->first_node;
	while (node)
	{
		if (node->variable && ft_strcmp(node->variable, variable) == 0)
		{
			printf("%s\n", node->variable);
			if (node->prev == NULL)
				mini->first_node = node->next;
			else
				node->prev->next = node->next;
			if (node->next)
				node->next->prev = node->prev;
			free(node->variable);
			free(node->content);
			free(node);
			mini->total_nodes--;
			return (0);
		}
		node = node->next;
	}
	return (1);
}
// se cambia el if (ft_strcmp(node->variable, variable) == 0)
// por si es NULL y podria dar un error.

int	process_unset_argument(t_mini *mini, char *arg)
{
	if (ft_strchr(arg, '='))
	{
		return (0);
	}
	if (ft_strcmp(arg, "_") != 0 && ft_strcmp(arg, "?") != 0)
	{
		ft_unset_env(mini, arg);
	}
	return (0);
}

int	ft_unset(char **args, t_mini *mini)
{
	int	i;
	int	exit_status;

	i = 1;
	exit_status = 0;
	if (!args[1])
		return (0);
	while (args[i])
	{
		if (process_unset_argument(mini, args[i]))
			exit_status = 1;
		i++;
	}
	if (mini->total_nodes != count_nodes(mini))
		printf("Unset ha fallado\n");
	return (exit_status);
}
// se añade ese if al final para una mejor gestion de errores