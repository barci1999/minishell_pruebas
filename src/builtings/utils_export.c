/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:09:06 by pablalva          #+#    #+#             */
/*   Updated: 2025/05/19 18:01:46 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pruebas.h"

void	add_or_update_variable(t_mini *mini, char *var, char *value)
{
	t_list	*node;
	t_list	*new_node;

	node = mini->first_node;
	while (node != NULL)
	{
		if (ft_strcmp(node->variable, var) == 0)
		{
			free(node->content);
			if (value)
			{
				node->content = ft_strdup(value);
			}
			else
				node->content = NULL;
			return ;
		}
		node = node->next;
	}
	new_node = new_node_export(var, value);
	if (!new_node)
		return ;
	node_to_end(&mini->first_node, new_node);
}

void	nodes_order(t_mini *mini)
{
	t_list	*node;
	t_list	*next_node;
	int		order;

	node = mini->first_node;
	while (node != NULL)
	{
		order = 0;
		next_node = mini->first_node;
		while (next_node)
		{
			if (ft_strcmp(node->variable, next_node->variable) > 0)
				order++;
			next_node = next_node->next;
		}
		node->order = order;
		node = node->next;
	}
}


int	print_single_export(t_list *node)
{
	if (ft_strlen(node->variable) == 1 && node->variable[0] == '_')
		return (0);
	if (node->content)
		printf("declare -x %s=\"%s\"\n", node->variable, node->content);
	else
		printf("declare -x %s\n", node->variable);
	return (1);
}

int	export_args(char **args, t_mini *mini)
{
	int		i;
	int		exit_status;
	char	*var_name;
	char	*value;

	i = 0;
	exit_status = 0;
	while (args[++i])
	{
		var_name = ft_strdup(args[i]);
		if (!var_name)
			return (1);
		value = ft_strchr(var_name, '=');
		if (value)
			*value++ = '\0';
		if (is_valid_variable_export(var_name))
			add_or_update_variable(mini, var_name, value);
		else
		{
			printf("minishell: export: `%s': not a valid identifier\n", var_name);
			exit_status = 1;
		}
		free(var_name);
	}
	return (exit_status);
}
t_list	*new_node_export(char *var, char *value)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->cmd_arg = NULL;
	new_node->cmd_name = NULL;
	new_node->cmd_path = NULL;
	new_node->variable = ft_strdup(var);
	if (value)
		new_node->content = ft_strdup(value);
	else
		new_node->content = NULL;
	new_node->order = 0;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}