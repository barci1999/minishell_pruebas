/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assig_nodes_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:24:26 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/18 17:58:53 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_status_type	mod_cmd_and_args(t_list *list, char **math_content, int *i,
		t_general *data_gen)
{
	if (is_builting(math_content[*i]))
		list->cmd_path = ft_strdup(math_content[*i]);
	else
	{
		list->cmd_path = take_cmd_path(math_content[*i], data_gen);
		if (!list->cmd_path && !*math_content[*i])
		{
			return (OK);
		}
	}
	list->cmd_arg = add_str_to_mat(list->cmd_arg, math_content[*i]);
	if (!list->cmd_arg)
	{
		return (MALLOC_ERROR);
	}
	if (!list->cmd_path)
	{
		return (OK);
	}
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

int	assig_var_node(char **mat_content, t_list *list, t_general *data_gen)
{
	t_status_type	type;
	bool			cmd_started;
	int				i;

	cmd_started = false;
	i = 0;
	while (mat_content[i])
	{
		type = update_status(mat_content, &i, data_gen);
		if (!cmd_started && (type == CMD || type == WORD))
		{
			if (mod_cmd_and_args(list, mat_content, &i, data_gen) != OK)
			{
				print_cmd_error(mat_content[i], "command not found", 127);
				return (1);
			}
			cmd_started = true;
		}
		else if (cmd_started && type == WORD)
		{
			list->cmd_arg = add_str_to_mat(list->cmd_arg, mat_content[i]);
			if (!list->cmd_arg)
			{
				print_cmd_error("malloc", "memory allocation failed", 1);
				return (1);
			}
			i++;
		}
		else if (type == REDIREC)
		{
			if (mod_redir_and_fd(list, mat_content, &i, data_gen) != OK)
			{
				print_cmd_error(mat_content[i], "redirection error", 2);
				return (2);
			}
		}
		else
		{
			if (*mat_content[i] == '\0')
				return (0);
			print_cmd_error(mat_content[i], "syntax error", 2);
			return (1);
		}
	}
	return (0);
}
