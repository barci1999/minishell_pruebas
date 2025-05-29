/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   estados.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:24:26 by pablalva          #+#    #+#             */
/*   Updated: 2025/05/29 18:57:11 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pruebas.h"

char	*take_the_redir(char **str)
{
	int		i;
	char	*temp;
	char	*result;

	i = 0;
	while (str[0][i] && (str[0][i] == '<' || str[0][i] == '>'))
		i++;
	temp = ft_substr(str[0][i], i, (int)ft_strlen(str[0][i]) - i);
	if (ft_strncmp(str, "<<", 2) == 0)
		result = "<<";
	else if (ft_strncmp(str, ">>", 2) == 0)
		result = ">>";
	else if (ft_strncmp(str, ">", 1) == 0)
		result = ">";
	else if (ft_strncmp(str, "<", 1) == 0)
		result = "<";
	free(str[0][i]);
	str[0][i] = ft_strdup(temp);
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
t_status_type	update_status(char **math_content, int *i, t_general *data_gen)
{
	if (is_redirec(math_content[*i]))
		return (REDIREC);
	else if (is_cmd(math_content[*i], &data_gen) == 1)
		return (CMD);
	else
		return (WORD);
}
void	mod_cmd_and_args(t_list *list, char **math_content, int *i,
		t_general *data_gen)
{
	if (update_status(math_content, i, &data_gen) == CMD)
	{
		list->cmd_arg = add_str_to_mat(list->cmd_arg, math_content[*i]);
		/*
			gestion leaks
		*/
		list->cmd_path = take_cmd_path(math_content[*i], &data_gen);
		/*
			gestion leaks
		*/
		list->cmd_name = asigg_cmd_name(list->cmd_path, &list);
		/*
			gestion leaks
		*/
		(*i)++;
		while (update_status(math_content, &i, &data_gen) == WORD
			&& math_content[*i])
		{
			add_str_to_mat(list->cmd_arg, math_content[*i]);
			/*
				gestion leaks
			*/
			(*i)++;
		}
	}
}
void	mod_redir_and_fd(t_list *list, char **mat_content, int *i,
		t_general *data_gen)
{
	char	*temp;

	if (update_status(mat_content, *i, &data_gen) == REDIREC)
	{
		if (ft_strcmp(mat_content[*i], "<<") == 0 || ft_strcmp(mat_content[*i],
				"<") == 0 || ft_strcmp(mat_content[*i], ">") == 0
			|| ft_strcmp(mat_content[*i], "<<") == 0)
		{
			list->redirecc = add_str_to_mat(list->redirecc, mat_content[*i]);
			/* gestion de leaks*/
		}
		else
		{
			list->redirecc = add_str_to_mat(list->redirecc,
					take_the_redir(&mat_content[*i]));
			list->fd = add_str_to_mat(list->fd, mat_content[*i]);
		}
	}
}

void	assig_var_node(char **math_content, t_list *list, t_general *data_gen,
		t_mini *mini)
{
	int i;
	i = 0;
	while (math_content[i])
	{
		if (update_status(math_content, &i, &data_gen) == CMD)
		{
			mod_cmd_and_args(&list, math_content, &i, &data_gen);
		}
		else if (update_status(math_content, &i, data_gen) == REDIREC)
		{
			mod_redir_and_fd(&list, math_content, &i, &data_gen);
		}
		i++;
	}
}