/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:44:27 by pablalva          #+#    #+#             */
/*   Updated: 2025/05/21 20:48:00 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pruebas.h"

int	ft_unset_env(t_mini *mini, char *variable)
{
	t_list	*node;

	node = mini->first_node;
	while (node)
	{
		if (ft_strcmp(node->variable, variable) == 0)
		{
			printf("%s\n",node->variable);
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

int	process_unset_argument(t_mini *mini, char *arg)
{
	char	*var_name;

	if (ft_strchr(arg, '='))
	{
		var_name = ft_strndup(arg, ft_strchr(arg, '=') - arg);
		if (var_name)
		{
			ft_unset_env(mini, var_name);
			free(var_name);
		}
	}
	else if (ft_strcmp(arg, "_") != 0 && ft_strcmp(arg, "?") != 0)
	{
		ft_unset_env(mini, arg);
	}
	return (0);
}

int	ft_unset(char **args,t_mini *mini)
{
	int	i;

	i = 1;
	if (!args[1])
		return (0);
	while (args[i])
	{
		process_unset_argument(mini, args[i]);
		i++;
	}
	printf("se ha usado mi unset\n");
	return (0);
}