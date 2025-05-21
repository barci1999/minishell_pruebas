/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_enviroment_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:08:00 by pablalva          #+#    #+#             */
/*   Updated: 2025/05/21 20:39:17 by ksudyn           ###   ########.fr       */
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
