/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pruebas_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:49:59 by pablalva          #+#    #+#             */
/*   Updated: 2025/04/15 18:33:59 by pablalva         ###   ########.fr       */
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

	paths = NULL;
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
	int	i;

	i = 0;
	while (matrix_content[i])
	{
		if (is_cmd(matrix_content[i], data_gen) == 1)
		{
			return (take_cmd_path(matrix_content[i], data_gen));
		}
		i++;
	}
	return (NULL);
}
// static char	**asigg_cmd_args(char **matrix_content,t_general *data_gen)
// {
// 	int i = 0;
// }
// static char	*asigg_cmd_name(char **matrix_content,t_general *data_gen)
// {
// 	int i = 0;
// }
t_list	*asigg_cont_list(t_list *list, t_general *data_gen)
{
	t_list	*current;
	char	*cmd_path;
	char	**cmd_arg;
	char	*cmd_name;
	char	**matrix_content;

	current = list;
	cmd_path = NULL;
	cmd_arg = NULL;
	cmd_name = NULL;
	while (current)
	{
		matrix_content = ft_split(current->content, ' ');
		if (!matrix_content)
			return (ft_free_matrix(matrix_content), NULL);
		current->cmd_path = asig_cmd_path(matrix_content, data_gen);
		// current->cmd_arg = assig_cmd_args(matrix_content,data_gen);
		// current->cmd_name = assig_cmd_name(matrix_content,data_gen);
		current = current->next;
	}
	return (list);
}
