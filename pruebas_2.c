/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pruebas_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:49:59 by pablalva          #+#    #+#             */
/*   Updated: 2025/04/16 15:17:50 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pruebas.h"

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
			return (ft_free_matrix(paths), 0);
		cmd_path = ft_get_strjoin(temp, comprove);
		if (!cmd_path)
			return (ft_free_matrix(paths), 0);
		if (access(cmd_path, X_OK) == 0)
			return (ft_free_matrix(paths), 1);
		free(cmd_path);
		i++;
	}
	return (ft_free_matrix(paths), 0);
}
char	*take_cmd_path(char *comprove, t_general *data_gen)
{
	char	*temp;
	int		i;
	char	*cmd_path;
	char	**paths;

	temp = NULL;
	i = 0;
	cmd_path = NULL;
	if (ft_strchr(comprove, '/'))
		return (comprove);
	paths = take_paths_env(data_gen->my_env);
	while (paths[i] != NULL)
	{
		temp = ft_get_strjoin(paths[i], "/");
		if (!temp)
			return (ft_free_matrix(paths), NULL);
		cmd_path = ft_get_strjoin(temp, comprove);
		if (!cmd_path)
			return (ft_free_matrix(paths), NULL);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (ft_free_matrix(paths), NULL);
}

char	*asig_cmd_path(char **matrix_content, t_general *data_gen)
{
	int		i;
	char	*result;
	char	*temp;
	char	*temp_2;

	i = -1;
	temp_2 = NULL;
	while (matrix_content[++i])
	{
		if (is_cmd(matrix_content[i], data_gen) == 1)
		{
			temp = take_cmd_path(matrix_content[i], data_gen);
			result = ft_strdup(temp);
			if (ft_strrchr(matrix_content[i], '/') != NULL)
			{
				temp_2 = ft_strdup(ft_strrchr(matrix_content[i], '/') + 1);
				if (!temp_2)
					return (free(result), free(temp), NULL);
				matrix_content[i] = temp_2;
			}
			return (free(temp), result);
		}
	}
	return (NULL);
}
char	**assig_cmd_args(char *cmd_name, char **matrix_content)
{
	int		i;
	int		m;
	char	**result;

	i = 0;
	m = 0;
	result = NULL;
	if (!cmd_name)
		return (NULL);
	while (ft_strcmp(matrix_content[i], cmd_name) != 0)
		i++;
	if (!matrix_content[i])
		return (NULL);
	result = malloc(((ft_matrixlen(matrix_content) - i) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (matrix_content[i])
	{
		result[m] = ft_strdup(matrix_content[i]);
		if (!result)
			return (ft_free_matrix(result), NULL);
		i++;
		m++;
	}
	return (result[m] = NULL, result);
}
static char	*asigg_cmd_name(char *cmd_path)
{
	char	*result;

	result = NULL;
	if (ft_strrchr(cmd_path, '/') != NULL)
	{
		result = ft_strdup(ft_strrchr(cmd_path, '/') + 1);
		if (!result)
			return (free(cmd_path), NULL);
		return (result);
	}
	else
		return (NULL);
}
t_list	*asigg_cont_list(t_list *list, t_general *data_gen)
{
	t_list	*current;
	char	**matrix_content;

	current = list;
	current->cmd_path = NULL;
	current->cmd_arg = NULL;
	current->cmd_name = NULL;
	while (current)
	{
		matrix_content = ft_split_quotes(current->content,' ');
		if (!matrix_content)
			return (ft_free_matrix(matrix_content), NULL);
		current->cmd_path = asig_cmd_path(matrix_content, data_gen);
		current->cmd_name = asigg_cmd_name(current->cmd_path);
		current->cmd_arg = assig_cmd_args(current->cmd_name, matrix_content);
		current = current->next;
	}
	return (list);
}
