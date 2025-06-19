/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:09:34 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/19 20:09:46 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	previous_pwd(t_mini *mini)
{
	char	*oldpwd;

	oldpwd = get_env_value(mini, "PWD");
	if (oldpwd)
		add_or_update_variable(mini, "OLDPWD", oldpwd);
}

void	new_pwd(char *new_path, t_mini *mini)
{
	if (!new_path)
		new_path = getcwd(NULL, 0);
	if (!new_path)
	{
		perror("getcwd");
		return ;
	}
	add_or_update_variable(mini, "PWD", new_path);
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
