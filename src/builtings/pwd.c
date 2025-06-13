/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:09:34 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/05 18:33:13 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	previous_pwd(void)
{
	char	*oldpwd;

	oldpwd = getenv("PWD");
	if (oldpwd)
		setenv("OLDPWD", oldpwd, 1);
}

void	new_pwd(char *new_path)
{
	if (!new_path)
		new_path = getcwd(NULL, 0);
	if (!new_path)
	{
		perror("getcwd");
		return ;
	}
	setenv("PWD", new_path, 1);
	free(new_path);
}

int	ft_pwd(void)
{
	char		*cwd;
	const char	*pwd_env;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		pwd_env = getenv("PWD");
		if (pwd_env)
		{
			printf("%s\n", pwd_env);
			return (0);
		}
		else
		{
			perror("pwd");
			return (1);
		}
	}
	else
	{
		printf("%s\n", cwd);
		free(cwd);
		return (0);
	}
}
