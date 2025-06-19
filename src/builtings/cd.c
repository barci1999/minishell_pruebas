/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:16:14 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/19 20:09:38 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_argument(char *path, t_mini *mini)
{
	if (chdir(path) == -1)
	{
		perror("minishell: cd");
		return (1);
	}
	previous_pwd(mini);
	new_pwd(getcwd(NULL, 0), mini);
	return (0);
}

// Esta función está diseñada para cambiar al directorio de inicio del usuario
// ($HOME).
static int	cd_home(t_mini *mini)
{
	char	*home;

	home = getenv("HOME");
	if (home && chdir(home) == -1)
	{
		perror("minishell: cd");
		return (1);
	}
	previous_pwd(mini);
	new_pwd(getcwd(NULL, 0), mini);
	return (0);
}

static int	cd_diferents_argument(char *arg, t_mini *mini)
{
	char	*oldpwd;

	if (strcmp(arg, "-") == 0)
	{
		oldpwd = getenv("OLDPWD");
		if (!oldpwd)
		{
			printf("minishell: cd: OLDPWD not set\n");
			return (1);
		}
		printf("%s\n", oldpwd);
		previous_pwd(mini);
		if (chdir(oldpwd) != 0)
		{
			perror("cd");
			return (1);
		}
		new_pwd(NULL, mini);
	}
	else
	{
		if (cd_argument(arg, mini) != 0)
			return (1);
	}
	return (0);
}

int	ft_cd(char **args, t_mini *mini)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	if (i > 2)
	{
		printf("minishell: cd: too many arguments\n");
		return (1);
	}
	if (i == 1)
	{
		if (cd_home(mini) != 0)
			return (0);
	}
	else
	{
		if (cd_diferents_argument(args[1], mini) == 0)
			return (0);
		else
			return (1);
	}
	return (0);
}
