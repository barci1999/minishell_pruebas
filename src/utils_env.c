/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:06:44 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/16 20:27:20 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**take_paths_env(char **envp)
{
	int		i;
	char	*path_env;
	char	**paths;

	i = 0;
	paths = NULL;
	path_env = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_env = envp[i] + 5;
			break ;
		}
		i++;
	}
	paths = ft_split(path_env, ':');
	if (paths == NULL)
	{
		return (NULL);
	}
	return (paths);
}
