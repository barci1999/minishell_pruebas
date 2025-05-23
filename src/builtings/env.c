/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:03:39 by pablalva          #+#    #+#             */
/*   Updated: 2025/05/23 18:28:53 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pruebas.h"

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
	printf("se ha usado mi env\n");
	return (0);
}
