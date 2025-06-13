/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:03:39 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/05 18:23:27 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **args, t_mini *mini)
{
	t_list	*temp;

	if (args[1])
	{
		printf("minishell: env: Args not allowed\n");
		return (1);
	}
	temp = mini->first_node;
	while (temp)
	{
		if (temp->variable && temp->content)
		{
			printf("%s=%s\n", temp->variable, temp->content);
		}
		temp = temp->next;
	}
	return (0);
}
