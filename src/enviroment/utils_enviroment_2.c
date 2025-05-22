/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_enviroment_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:08:00 by pablalva          #+#    #+#             */
/*   Updated: 2025/05/22 15:52:50 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pruebas.h"
char	*build_env_string(t_list *node)
{
	char	*env_string;
	int		len;

	if (!node || !node->variable || !node->content)
		return (NULL);
	len = strlen(node->variable) + strlen(node->content) + 2;
	env_string = malloc(len);
	if (!env_string)
		return (NULL);
	snprintf(env_string, len, "%s=%s", node->variable, node->content);
	return (env_string);
}

void	free_env_array(char **envp)
{
	int i;
	
	i = 0;
	if (!envp)
		return;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}


int count_nodes(t_mini *mini)
{
    int count = 0;
    t_list *node = mini->first_node;
    while (node)
    {
        count++;
        node = node->next;
    }
    return count;
}
//La uso en cada lugar donde se modifique total_nodes
//para comprobar si se actualiza el contador de total_nodes y si están sincronizados
