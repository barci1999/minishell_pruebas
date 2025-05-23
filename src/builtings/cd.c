/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:16:14 by pablalva          #+#    #+#             */
/*   Updated: 2025/05/23 16:34:39 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pruebas.h"

static int	cd_argument(char *path)
{
	previous_pwd();
	if (chdir(path) == -1)
	{
		perror("minishell: cd");
		return (1);
	}
	new_pwd(getcwd(NULL, 0));
	return (0);
}

// Esta función está diseñada para cambiar al directorio de inicio del usuario ($HOME).
static int	cd_home(void)
{
	char	*home;

	home = getenv("HOME");
	if (home && chdir(home) == -1)
	{
		perror("minishell: cd");
		return (1);
	}
	previous_pwd();
	new_pwd(getcwd(NULL, 0));
	return (0);
}

static void	cd_diferents_argument(char *arg)
{
	char	*oldpwd;

	if (strcmp(arg, "-") == 0)
	{
		oldpwd = getenv("OLDPWD");
		if (!oldpwd)
		{
			printf("minishell: cd: OLDPWD not set\n");
			return ;
		}
		printf("%s\n", oldpwd);
		previous_pwd();
		if (chdir(oldpwd) != 0)
		{
			perror("cd");
			return ;
		}
		new_pwd(NULL);
	}
	else
	{
		if (cd_argument(arg) != 0)
			return ;
	}
}

void	ft_cd(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	if (i > 2)
	{
		printf("minishell: cd: too many arguments\n");
		return ;
	}
	if (i == 1)
	{
		if (cd_home() != 0)
			return ;
	}
	else
	{
		cd_diferents_argument(args[1]);
	}
	printf("se ha usado mi cd\n");
}
