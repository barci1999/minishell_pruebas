/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:06:44 by pablalva          #+#    #+#             */
/*   Updated: 2025/04/15 17:06:49 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pruebas.h"

char	**take_paths_env(char **envp)
{
	int		i;
	char	*path_env;
	char	**paths;

	i = 0;
	paths = NULL;
	path_env = NULL;
	while (*envp)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_env = envp[i] + 5;
			break ;
		}
		envp++;
	}
	paths = ft_split(path_env, ':');
	if (paths == NULL)
	{
		perror("Error");
		exit(1);
	}
	return (paths);
}