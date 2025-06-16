/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_asigg_node_var.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:49:59 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/16 20:27:54 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*take_cmd_path(char *comprove, t_general *data_gen)
{
	char	*temp;
	int		i;
	char	*cmd_path;
	char	**paths;

	temp = NULL;
	i = 0;
	cmd_path = NULL;
	if(*comprove == '\0')
		return(NULL);
	if (comprove[0] == '/' || comprove[0] == '.')
		return (ft_strdup(comprove));
	paths = take_paths_env(data_gen->my_env);
	while (paths[i] != NULL)
	{
		printf("cocacola\n");
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
			return (ft_free_mat(paths), NULL);
		cmd_path = ft_get_strjoin(temp, comprove);
		if (!cmd_path)
			return (ft_free_mat(paths), NULL);
		if (access(cmd_path, X_OK) == 0)
			return (ft_free_mat(paths), cmd_path);
		free(cmd_path);
		i++;
	}
	return (ft_free_mat(paths), NULL);
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
			return (free(cmd_path), NULL);
		return (result);
	}
	if (ft_strrchr(cmd_path, '/') != NULL)
	{
		result = ft_strdup((ft_strrchr(cmd_path, '/') + 1));
		if (!result)
			return (free(cmd_path), NULL);
		return (result);
	}
	else
		return (NULL);
}

int	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

size_t	number_of_cmd_arg(const char *src)
{
	int		i;
	size_t	count;
	char	quote;

	i = 0;
	count = 0;
	while (src[i])
	{
		while (src[i] && ft_is_space(src[i]))
			i++;
		if (!src[i])
			break ;
		if (is_quote(src[i]))
		{
			quote = src[i++];
			while (src[i] && src[i] != quote)
				i++;
			if (src[i] == quote)
				i++;
			count++;
		}
		else if (is_operator_char(src[i]))
		{
			if ((src[i] == '>' && src[i + 1] == '>') || (src[i] == '<'
					&& src[i + 1] == '<'))
				i += 2;
			else
				i += 1;
			count++;
		}
		else
		{
			while (src[i] && !ft_is_space(src[i]) && !is_quote(src[i])
				&& !is_operator_char(src[i]))
				i++;
			count++;
		}
	}
	return (count);
}


t_list	*asigg_cont_list(t_list *list, t_general *data_gen, t_mini *mini)
{
	t_list	*current;
	char	**mat_content;

	mat_content = NULL;
	current = list;
	data_gen->tem_heredoc = 0;
	data_gen->my_env = env_list_to_array(mini);
	while (current)
	{
		mat_content = fukking_quotes(current->content, mini);
		if (!mat_content)
			return (ft_free_mat(mat_content), NULL);
		if (assig_var_node(mat_content, current, data_gen) != 0)
		{
			ft_free_mat(mat_content);
			free_list(&list);
			return (NULL);
		}
		ft_free_mat(mat_content);
		current = current->next;
	}
	return (list);
}
