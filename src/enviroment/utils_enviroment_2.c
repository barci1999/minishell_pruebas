/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_enviroment_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:08:00 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/05 14:16:24 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pruebas.h"

char	*build_env_string(t_list *node)
{
	char	*env_string;
	int		var_len;
	int		content_len;
	int		len;

	if (!node || !node->variable || !node->content)
		return (NULL);
	var_len = ft_strlen(node->variable);
	content_len = ft_strlen(node->content);
	len = var_len + content_len + 2;
	env_string = malloc(len);
	if (!env_string)
		return (NULL);
	ft_memcpy(env_string, node->variable, var_len);
	env_string[var_len] = '=';
	ft_memcpy(env_string + var_len + 1, node->content, content_len);
	env_string[len - 1] = '\0';
	return (env_string);
}

void	free_env_array(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

int	count_nodes(t_mini *mini)
{
	int		count;
	t_list	*node;

	count = 0;
	node = mini->first_node;
	while (node)
	{
		count++;
		node = node->next;
	}
	return (count);
}
// La uso en cada lugar donde se modifique total_nodes
// para comprobar si se actualiza el contador de total_nodes y si están
// sincronizados
