/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_asigg_node_var.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:49:59 by pablalva          #+#    #+#             */
/*   Updated: 2025/04/24 15:08:00 by pablalva         ###   ########.fr       */
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
			return (ft_free_mat(paths), 0);
		cmd_path = ft_get_strjoin(temp, comprove);
		if (!cmd_path)
			return (ft_free_mat(paths), 0);
		if (access(cmd_path, X_OK) == 0)
			return (ft_free_mat(paths), 1);
		free(cmd_path);
		i++;
	}
	return (ft_free_mat(paths), 0);
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
			return (ft_free_mat(paths), NULL);
		cmd_path = ft_get_strjoin(temp, comprove);
		if (!cmd_path)
			return (ft_free_mat(paths), NULL);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (ft_free_mat(paths), NULL);
}

static char	*asig_cmd_path(char **mat_content, t_general *data_gen,
		t_list *list)
{
	int		i;
	char	*result;
	char	*temp;
	char	*temp_2;

	(void)list;
	i = -1;
	temp_2 = NULL;
	while (mat_content[++i])
	{
		if (is_cmd(mat_content[i], data_gen) == 1)
		{
			if (is_builting(mat_content[i]))
			{
				result = ft_strdup(mat_content[i]);
				if (!result)
					return (ft_free_mat(mat_content), free_list(&list), NULL);
				return (result);
			}
			temp = take_cmd_path(mat_content[i], data_gen);
			result = ft_strdup(temp);
			if (ft_strrchr(mat_content[i], '/') != NULL)
			{
				temp_2 = ft_strdup(ft_strrchr(mat_content[i], '/') + 1);
				if (!temp_2)
					return (free(result), free(temp), NULL);
				mat_content[i] = temp_2;
			}
			return (free(temp), result);
		}
	}
	return (NULL);
}
static int	is_redirec(char *str)
{
	if (ft_strcmp(str, "<") == 0)
		return (0);
	else if (ft_strcmp(str, "<<") == 0)
		return (0);
	else if (ft_strcmp(str, ">") == 0)
		return (0);
	else if (ft_strcmp(str, ">>") == 0)
		return (0);
	else
		return (1);
}
static char	**assig_cmd_args(char *cmd_name, char **mat, t_list *list)
{
	char	**res;
	int		i;
	size_t	m;
	size_t	arg_count;

	i = 0;
	m = -1;
	arg_count = 0;
	if (!cmd_name)
		return (ft_free_mat(mat), free_list(&list), NULL);
	while (mat[i] && ft_strcmp(mat[i], cmd_name) != 0)
		i++;
	if (!mat[i])
		return (NULL);
	arg_count = i;
	while (mat[arg_count] && is_redirec(mat[arg_count]))
		arg_count++;
	res = malloc((arg_count + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (mat[i] && is_redirec(mat[i]))
	{
		res[++m] = ft_strdup(mat[i++]);
		if (!res[m])
			return (ft_free_mat(res), NULL);
	}
	return (res[++m] = NULL, res);
}
static char	*asigg_cmd_name(char *cmd_path, t_list *list)
{
	char	*result;

	(void)list;
	result = NULL;
	if (is_builting(cmd_path))
	{
		result = ft_strdup(cmd_path);
		if (!result)
			return (free_list(&list), NULL);
		return (result);
	}
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
static char	*assig_delim(char **mat, t_list *list)
{
	int	i;

	(void)list;
	i = -1;
	while (mat[++i])
	{
		if (ft_strcmp(mat[i], "<<") == 0)
		{
			if (mat[i + 1])
				return (mat[i + 1]);
			else
				return (NULL);
		}
	}
	return (NULL);
}
static size_t	nb_redirrec(char **mat)
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
static char	**assig_fd(char **mat, t_general *data_gen, t_list *list)
{
	int		i;
	char	**result;
	int		r;

	r = -1;
	i = -1;
	result = malloc((nb_redirrec(mat) + 1) * sizeof(char *));
	if (!result)
		return (ft_free_mat(mat), free_list(&list), NULL);
	while (mat[++i])
	{
		if (ft_strcmp(mat[i], ">") == 0 || ft_strcmp(mat[i], ">>") == 0
			|| ft_strcmp(mat[i], "<") == 0)
		{
			if (mat[i + 1])
			{
				result[++r] = ft_strdup(mat[i + 1]);
				if (!result[r])
					return (ft_free_mat(mat), ft_free_mat(result),
						free_list(&list), NULL);
			}
		}
		if (ft_strcmp(mat[i], "<<") == 0)
		{
			result[++r] = ft_strjoin("temp_here_",
					ft_itoa(data_gen->tem_heredoc));
			if (!result[r])
				return (ft_free_mat(mat), ft_free_mat(result), free_list(&list),
					NULL);
			data_gen->tem_heredoc++;
		}
	}
	return (result[++r] = NULL, result);
}

static char	**assig_redirecc(char **mat, t_list *list)
{
	int		i;
	int		r;
	char	**result;

	(void)list;
	i = -1;
	r = -1;
	result = malloc((nb_redirrec(mat) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (mat[++i])
	{
		if (ft_strcmp(mat[i], ">") == 0 || ft_strcmp(mat[i], ">>") == 0
			|| ft_strcmp(mat[i], "<") == 0 || ft_strcmp(mat[i], "<<") == 0)
		{
			result[++r] = ft_strdup(mat[i]);
			if (!result)
				return (ft_free_mat(result), NULL);
		}
	}
	return (result[++r] = NULL, result);
}
t_list	*asigg_cont_list(t_list *list, t_general *data_gen)
{
	t_list	*current;
	char	**mat_content;

	current = list;
	data_gen->tem_heredoc = 0;
	while (current)
	{
		mat_content = ft_split_quotes(current->content, ' ');
		if (!mat_content)
			return (ft_free_mat(mat_content), NULL);
		current->cmd_path = asig_cmd_path(mat_content, data_gen, list);
		current->cmd_name = asigg_cmd_name(current->cmd_path, list);
		current->delim = assig_delim(mat_content, list);
		current->cmd_arg = assig_cmd_args(current->cmd_name, mat_content, list);
		current->redirecc = assig_redirecc(mat_content, list);
		current->fd = assig_fd(mat_content, data_gen, list);
		current = current->next;
	}
	return (list);
}
