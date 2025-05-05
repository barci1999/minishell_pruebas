/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detectors_and_counters.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:27:21 by pablalva          #+#    #+#             */
/*   Updated: 2025/05/05 17:35:48 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pruebas.h"

int	is_redirec(char *str)
{
	if (ft_strcmp(str, "<") == 0)
		return (1);
	else if (ft_strcmp(str, "<<") == 0)
		return (1);
	else if (ft_strcmp(str, ">") == 0)
		return (1);
	else if (ft_strcmp(str, ">>") == 0)
		return (1);
	else
		return (0);
}
size_t	nb_redirrec(char **mat)
{
	int		i;
	size_t	result;

	i = -1;
	result = 0;
	while (mat[++i])
	{
		if (ft_strcmp(mat[i], ">") == 0 || ft_strcmp(mat[i], ">>") == 0
			|| ft_strcmp(mat[i], "<") == 0 || ft_strcmp(mat[i], "<<") == 0)
			result++;
	}
	return (result);
}
int	is_builting(char *token)
{
	if (!token)
		return (0);
	else if (ft_strcmp(token, "echo") == 0)
		return (1);
	else if (ft_strcmp(token, "cd") == 0)
		return (1);
	else if (ft_strcmp(token, "pwd") == 0)
		return (1);
	else if (ft_strcmp(token, "export") == 0)
		return (1);
	else if (ft_strcmp(token, "unset") == 0)
		return (1);
	else if (ft_strcmp(token, "env") == 0)
		return (1);
	else if (ft_strcmp(token, "exit") == 0)
		return (1);
	return (0);
}
size_t	num_pipes(char *input, char c)
{
	size_t	count;
	char	quote;
	int		i;

	count = 0;
	quote = 0;
	i = 0;
	while (input[i])
	{
		if ((input[i] == '\'' || input[i] == '\"'))
		{
			if (!quote)
				quote = input[i];
			else if (quote == input[i])
				quote = 0;
		}
		else if (input[i] == c && !quote)
			count++;
		i++;
	}
	return (count);
}
int	is_cmd(char *comprove, t_general *data_gen)
{
	struct stat	sb;
	char		**paths;
	char		*temp;
	char		*cmd_path;
	int			i;

	i = 0;
	temp = NULL;
	if (ft_strchr(comprove, '/'))
	{
		if (access(comprove, X_OK) == 0 && stat(comprove, &sb) == 0
			&& S_ISREG(sb.st_mode))
			return (1);
		return (0);
	}
	paths = take_paths_env(data_gen->my_env);
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
			return (ft_free_mat(paths), 0);
		cmd_path = ft_get_strjoin(temp, comprove);
		if (!cmd_path)
			return (ft_free_mat(paths), 0);
		if (access(cmd_path, X_OK) == 0)
			return (ft_free_mat(paths),free(cmd_path), 1);
		free(cmd_path);
		i++;
	}
	return (ft_free_mat(paths),0);
}
