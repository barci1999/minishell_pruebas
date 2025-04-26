/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_asigg_node_var.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:49:59 by pablalva          #+#    #+#             */
/*   Updated: 2025/04/26 21:23:45 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pruebas.h"


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

char	*asig_cmd_path(char **mat_content, t_general *data_gen,
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
char	**assig_cmd_args(char *cmd_name, char **mat, t_list *list)
{
	char	**res;
	int		i;
	size_t	m;
	size_t	arg_count;
	(void)list;

	i = 0;
	m = -1;
	arg_count = 0;
	if (!cmd_name)
		return (NULL);
	while (mat[i] && ft_strcmp(mat[i], cmd_name) != 0)
		i++;
	if (!mat[i])
		return (NULL);
	arg_count = i;
	while (mat[arg_count] && !is_redirec(mat[arg_count]))
		arg_count++;
	res = malloc((arg_count + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (mat[i] && !is_redirec(mat[i]))
	{
		
		res[++m] = ft_strdup(mat[i++]);
		if (!res[m])
			return (ft_free_mat(res), NULL);
	}
	return (res[++m] = NULL, res);
}
char	*asigg_cmd_name(char *cmd_path, t_list *list)
{
	char	*result;

	(void)list;
	result = NULL;
	if (is_builting(cmd_path))
	{
		result = ft_strdup(cmd_path);
		if (!result)
			return (NULL);
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
static int analize_quote(char *src)
{
	int i = -1;
	if(!src)
		return(0);
	while (src[++i])
	{
		if(src[i] == '\'' || src[i] == '\"')
			return(1);
	}
	return(0);
	
}
static size_t number_of_cmd_arg(char *src)
{
	int i = 0;
	size_t result = 0;
	while (src[i])
	{
		if(!is_space(src[i]) && src[i] != '\'' && src[i] != '\"')
		{
			while(!is_space(src[i]) && src[i])
			{
				i++;
			}
			result++;
		}
		if(src[i] == '\'')
		{
			i++;
			while (src[i] != '\'' && src[i])
				i++;
			result++;		
		}
		else if(src[i] == '\"')
		{
			i++;
			while (src[i] != '\"' && src[i])
				i++;
			result++;		
		}
		i++;
	}
	printf("%zu\n",result);
	return(result);
	
}
static char **take_the_arg(char *src)
{
	//int i = 0;
	char **result;
	int r = 0;
	int i = 0;
	int j = 0;
	char quote;
	if(analize_quote(src) == 0)
	{
		result = ft_split_quotes(src,' ');
		return(result);
	}
	else
	{
		result = malloc((number_of_cmd_arg(src)+1) * sizeof(char *));
		while(src[i])
		{
			if(!is_space(src[i]) && src[i] != '\'' && src[i] != '\"')
			{
				while(src[i] && !is_space(src[i]))
					i++;
				result[r] = ft_substr(src,j,(i-j));
				r++;
				j = i;
			}
			else if(src[i] == '\'' || src[i] == '\"')
			{
				quote = src[i];
				i++;
				j = i;
				while(src[i] != quote && src[i])
					i++;
				result[r] = ft_strtrim(ft_substr(src,j ,(i - j)), " \t\v\n\r\b\f");
				r++;
				j = i;
			}
			i++;
		}
	}
	result[r] = NULL;
	return(result);
}
t_list	*asigg_cont_list(t_list *list, t_general *data_gen)
{
	t_list	*current;
	char	**mat_content;

	current = list;
	data_gen->tem_heredoc = 0;
	while (current)
	{
		// mat_content = ft_split_quotes(current->content, ' ');
		mat_content = take_the_arg(current->content); 
		if (!mat_content)
			return (ft_free_mat(mat_content), NULL);
		current->cmd_path = asig_cmd_path(mat_content, data_gen, list);
		current->cmd_name = asigg_cmd_name(current->cmd_path, list);
		current->cmd_arg = assig_cmd_args(current->cmd_name, mat_content, list);
		current->delim = assig_delim(mat_content, list);
		current->redirecc = assig_redirecc(mat_content, list);
		current->fd = assig_fd(mat_content, data_gen, list);
		current = current->next;
	}
	return (list);
}
