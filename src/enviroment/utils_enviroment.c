/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_enviroment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:13:25 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/09 18:32:16 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*create_env_node(char *var, char *value)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	ft_memset(new, 0, sizeof(t_list));
	new->variable = ft_strdup(var);
	if (value)
		new->content = ft_strdup(value);
	else
		new->content = NULL;
	return (new);
}

void	add_env_var(t_mini *mini, char *var, char *value)
{
	t_list	*new;
	t_list	*temp;

	new = create_env_node(var, value);
	if (!new)
		return ;
	if (!mini->first_node)
		mini->first_node = new;
	else
	{
		temp = mini->first_node;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
		new->prev = temp;
	}
	mini->total_nodes++;
}

void	init_minim_env(t_mini *mini)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		add_env_var(mini, ft_strdup("PWD"), cwd);
		free(cwd);
	}
	add_env_var(mini, ft_strdup("SHLVL"), ft_strdup("1"));
	add_env_var(mini, ft_strdup("_"), ft_strdup("/usr/bin/env"));
}

void	init_env_list(t_mini *mini, char **envp)
{
	int		i;
	char	*equal;
	char	*key;
	char	*value;

	if (!envp || !envp[0])
		init_minim_env(mini);
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
