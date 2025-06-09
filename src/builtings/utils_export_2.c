/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:40:20 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/09 20:38:10 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_variable_export(char *var)
{
	int	i;

	if (!var || !var[0])
		return (0);
	if (!var || (!ft_isalpha(var[0]) && var[0] != '_'))
		return (0);
	i = 1;
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	print_single_export(t_list *node)
{
	if (ft_strlen(node->variable) == 1 && node->variable[0] == '_')
		return (0);
	if (node->content)
		printf("declare -x %s=\"%s\"\n", node->variable, node->content);
	else
		printf("declare -x %s\n", node->variable);
	return (1);
}
