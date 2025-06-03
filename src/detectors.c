/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detectors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 13:07:13 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/03 14:13:24 by pablalva         ###   ########.fr       */
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
	if (is_builting(comprove))
		return (1);
	if (ft_strchr(comprove, '/'))
	{
		if (access(comprove, X_OK) == 0 && stat(comprove, &sb) == 0
			&& S_ISREG(sb.st_mode))
			return (1);
		return (0);
	}
	paths = take_paths_env(data_gen->my_env);
	if(!paths)
		return(0);
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
			return (ft_free_mat(paths), 0);
		cmd_path = ft_get_strjoin(temp, comprove);
		if (!cmd_path)
			return (ft_free_mat(paths), 0);
		if (access(cmd_path, X_OK) == 0)
			return (ft_free_mat(paths), free(cmd_path), 1);
		free(cmd_path);
		i++;
	}
	return (ft_free_mat(paths), 0);
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
int	is_redirec(char *str)
{
	if (ft_strncmp(str, "<",1) == 0)
		return (1);
	else if (ft_strncmp(str, "<<",2) == 0)
		return (1);
	else if (ft_strncmp(str, ">",1) == 0)
		return (1);
	else if (ft_strncmp(str, ">>",2) == 0)
		return (1);
	else
		return (0);
}
int	have_a_heredoc(t_list *node)
{
	int i = 0;
	if(!node->redirecc)
		return(0);
	while (node->redirecc[i])
	{
		if (ft_strcmp(node->redirecc[i], "<<") == 0)
			return (1);
		i++;
	}
	return (0);
}
int is_operator_char(char c)
{
	return (c == '>' || c == '<');
}
