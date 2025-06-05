/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assig_nodes_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:24:26 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/05 15:04:40 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pruebas.h"

char	*take_the_redir(char **str)
{
	int		i;
	char	*temp;
	char	*result;

	result = NULL;
	i = 0;
	while (str[0][i] && (str[0][i] == '<' || str[0][i] == '>'))
		i++;
	temp = ft_substr(str[0], i, (int)ft_strlen(str[0]) - i);
	if (ft_strncmp(str[0], "<<", 2) == 0)
		result = ft_strdup("<<");
	else if (ft_strncmp(str[0], ">>", 2) == 0)
		result = ft_strdup(">>");
	else if (ft_strncmp(str[0], ">", 1) == 0)
		result = ft_strdup(">");
	else if (ft_strncmp(str[0], "<", 1) == 0)
		result = ft_strdup("<");
	if (str[0])
		free(str[0]);
	str[0] = ft_strdup(temp);
	free(temp);
	return (result);
}

char	**add_str_to_mat(char **src, char *to_add)
{
	char	**result;
	int		i;

	i = 0;
	result = malloc((ft_matlen(src) + 2) * sizeof(char *));
	if (!result)
		return (ft_free_mat(src), NULL);
	while (src && src[i])
	{
		result[i] = ft_strdup(src[i]);
		if (!result[i])
			return (ft_free_mat(result), ft_free_mat(src), NULL);
		i++;
	}
	result[i] = ft_strdup(to_add);
	if (!result[i])
		return (ft_free_mat(result), ft_free_mat(src), NULL);
	result[i + 1] = NULL;
	return (ft_free_mat(src), result);
}

t_status_type	mod_cmd_and_args(t_list *list, char **math_content, int *i,
		t_general *data_gen)
{
	if (is_builting(math_content[*i]))
		list->cmd_path = ft_strdup(math_content[*i]);
	else
		list->cmd_path = take_cmd_path(math_content[*i], data_gen);
	list->cmd_arg = add_str_to_mat(list->cmd_arg, math_content[*i]);
	if (!list->cmd_arg)
		return (MALLOC_ERROR);
	if (!list->cmd_path)
		return (MALLOC_ERROR);
	list->cmd_name = asigg_cmd_name(list->cmd_path, list);
	if (!list->cmd_name)
		return (MALLOC_ERROR);
	(*i)++;
	while (math_content[*i] && update_status(math_content, i,
			data_gen) != REDIREC)
	{
		list->cmd_arg = add_str_to_mat(list->cmd_arg, math_content[*i]);
		if (!list->cmd_arg)
			return (MALLOC_ERROR);
		(*i)++;
	}
	return (OK);
}

t_status_type	safe_add_str(char ***mat, char *str)
{
	*mat = add_str_to_mat(*mat, str);
	if (!*mat)
		return (MALLOC_ERROR);
	return (OK);
}

void	assig_var_node(char **math_content, t_list *list, t_general *data_gen)
{
	t_status_type	flag;
	int				i;

	i = 0;
	flag = OK;
	while (math_content[i])
	{
		if (update_status(math_content, &i, data_gen) == CMD)
			flag = mod_cmd_and_args(list, math_content, &i, data_gen);
		else if (update_status(math_content, &i, data_gen) == REDIREC)
			flag = mod_redir_and_fd(list, math_content, &i, data_gen);
		else
		{
			printf("error en word\n");
			exit(1);
		}
		if (flag != OK)
		{
			printf("error en las funciones\n");
			exit(1);
		}
	}
}
