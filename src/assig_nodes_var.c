/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assig_nodes_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:24:26 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/18 19:50:25 by pablalva         ###   ########.fr       */
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

t_status_type	mod_cmd_and_args(t_list *list, char **content,t_varnodes *var_nodes,
		t_general *data_gen)
{
	if (is_builting(content[var_nodes->i]))
		list->cmd_path = ft_strdup(content[var_nodes->i]);
	else
	{
		list->cmd_path = take_cmd_path(content[var_nodes->i], data_gen);
		if (!list->cmd_path && !*content[var_nodes->i])
			return (OK);
	}
	list->cmd_arg = add_str_to_mat(list->cmd_arg, content[var_nodes->i]);
	if (!list->cmd_arg)
		return (MALLOC_ERROR);
	if (!list->cmd_path)
		return (OK);
	list->cmd_name = asigg_cmd_name(list->cmd_path, list);
	if (!list->cmd_name)
		return (MALLOC_ERROR);
	(var_nodes->i)++;
	while (content[var_nodes->i] && up_stat(content,var_nodes, data_gen) != REDIREC)
	{
		list->cmd_arg = add_str_to_mat(list->cmd_arg, content[var_nodes->i]);
		if (!list->cmd_arg)
			return (MALLOC_ERROR);
		(var_nodes->i)++;
	}
	return (OK);
}

int	assig_var_node(char **content, t_list *list, t_general *data_gen)
{
	t_varnodes var_nodes;

	var_nodes.start = false;
	var_nodes.i = 0;
	while (content[var_nodes.i])
	{
		var_nodes.type = up_stat(content,&var_nodes, data_gen);
		if (!var_nodes.start && (var_nodes.type == CMD || var_nodes.type == WORD))
		{
			if (mod_cmd_and_args(list, content,&var_nodes, data_gen) != OK)
				return (print_error(content[var_nodes.i], "command not found", 127),1);
			var_nodes.start = true;
		}
		else if (var_nodes.start && up_stat(content,&var_nodes, data_gen) == WORD)
		{
			list->cmd_arg = add_str_to_mat(list->cmd_arg, content[var_nodes.i]);
			if (!list->cmd_arg)
				return (print_error("malloc", "memory allocation failed", 1),1);
			var_nodes.i++;
		}
		else if (up_stat(content, &var_nodes, data_gen) == REDIREC)
		{
			if (mod_redir_and_fd(list, content, &var_nodes, data_gen) != OK)
				return (print_error(content[var_nodes.i], "redirection error", 2),1);
		}
		else
		{
			if (*content[var_nodes.i] == '\0')
				return (0);
			print_error(content[var_nodes.i], "syntax error", 2);
			return (1);
		}
	}
	return (0);
}


