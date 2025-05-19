/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:09:34 by pablalva          #+#    #+#             */
/*   Updated: 2025/05/19 18:10:21 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pruebas.h"

void	previous_pwd(void)
{
	char	*oldpwd;

	;
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

void	ft_pwd(void)
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
		}
		else
		{
			perror("pwd");
		}
	}
	else
	{
		printf("%s\n", cwd);
		free(cwd);
	}
	printf("se ha usado mi pwd\n");
}