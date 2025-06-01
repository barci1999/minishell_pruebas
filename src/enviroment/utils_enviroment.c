/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_enviroment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:13:25 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/01 19:00:41 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pruebas.h"

t_list	*create_env_node(char *var, char *value)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	ft_memset(new, 0, sizeof(t_list));
	new->variable = ft_strdup(var);
	new->content = ft_strdup(value);
	return (new);
}

void	add_env_var(t_mini *mini, char *var, char *value)
{
	t_list	*new;
	t_list	*temp;

	new = create_env_node(var, value);
	temp = mini->first_node;
	if (!new)
		return ;
	if (!mini->first_node)
		mini->first_node = new;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new;
		new->prev = temp;
	}
	mini->total_nodes++;
}

void	init_env_list(t_mini *mini, char **envp)
{
	int		i;
	char	*equal;
	char	*key;
	char	*value;

	i = 0;
	while (envp[i])
	{
		equal = ft_strchr(envp[i], '=');
		if (equal)
		{
			key = ft_strndup(envp[i], equal - envp[i]);
			value = ft_strdup(equal + 1);
			add_env_var(mini, key, value);
			free(key);
			free(value);
		}
		i++;
	}
}

void	free_env_list(t_mini *mini)
{
	t_list	*current;
	t_list	*tmp;

	current = mini->first_node;
	while (current)
	{
		tmp = current->next;
		free(current->variable);
		free(current->content);
		free(current);
		current = tmp;
	}
	mini->first_node = NULL;
	mini->total_nodes = 0;
}
char	**env_list_to_array(t_mini *mini)
{
	char	**envp;
	t_list	*current;
	int		i;

	i = 0;
	current = mini->first_node;
	envp = malloc(sizeof(char *) * (mini->total_nodes + 1));
	if (!envp)
		return (NULL);
	while (current)
	{
		envp[i] = build_env_string(current);
		if (!envp[i])
		{
			while (i > 0)
				free(envp[--i]);
			free(envp);
			return (NULL);
		}
		current = current->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
