/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assig_nodes_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:24:26 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/19 18:55:12 by ksudyn           ###   ########.fr       */
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

t_status_type	mod_cmd_and_args(t_list *list, char **cont,
		t_varnodes *var_nodes, t_general *data_gen)
{
	if (is_builting(cont[var_nodes->i]))
		list->cmd_path = ft_strdup(cont[var_nodes->i]);
	else
	{
		list->cmd_path = take_cmd_path(cont[var_nodes->i], data_gen);
		if (!list->cmd_path && !*cont[var_nodes->i])
			return (OK);
	}
	list->cmd_arg = add_str_to_mat(list->cmd_arg, cont[var_nodes->i]);
	if (!list->cmd_arg)
		return (MALLOC_ERROR);
	if (!list->cmd_path)
		return (OK);
	list->cmd_name = asigg_cmd_name(list->cmd_path, list);
	if (!list->cmd_name)
		return (MALLOC_ERROR);
	(var_nodes->i)++;
	while (cont[var_nodes->i] && up_stat(cont, var_nodes, data_gen) != REDIREC)
	{
		list->cmd_arg = add_str_to_mat(list->cmd_arg, cont[var_nodes->i]);
		if (!list->cmd_arg)
			return (MALLOC_ERROR);
		(var_nodes->i)++;
	}
	return (OK);
}

int	assig_var_node(char **c, t_list *l, t_general *g)
{
	t_varnodes	v;
	int			prev_i;

	init_varnodes(&v);
	while (c[v.i])
	{
		prev_i = v.i;
		v.type = up_stat(c, &v, g);
		if (process_node_cases(c, l, &v, g))
			return (1);
		if (prev_i == v.i)
			v.i++;
	}
	return (0);
}
