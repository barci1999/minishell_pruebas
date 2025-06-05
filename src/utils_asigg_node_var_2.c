/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_asigg_node_var_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:11:10 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/05 15:33:09 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**assig_redirecc(char **mat, t_list *list)
{
	int		i;
	int		r;
	char	**result;

	(void)list;
	i = -1;
	r = -1;
	result = malloc((nb_redirrec(mat) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (mat[++i])
	{
		if (ft_strcmp(mat[i], ">") == 0 || ft_strcmp(mat[i], ">>") == 0
			|| ft_strcmp(mat[i], "<") == 0 || ft_strcmp(mat[i], "<<") == 0)
		{
			result[++r] = ft_strdup(mat[i]);
			if (!result)
				return (ft_free_mat(result), NULL);
		}
	}
	return (result[++r] = NULL, result);
}

char	**assig_delim(char **mat, t_list *list)
{
	int		i;
	size_t	nb_here;
	char	**result;
	int		r;

	r = 0;
	nb_here = 0;
	i = 0;
	(void)list;
	while (mat[i])
	{
		if (ft_strcmp(mat[i], "<<") == 0)
			nb_here++;
		i++;
	}
	result = malloc((nb_here + 1) * sizeof(char *));
	if (!result)
	{
	}
	i = 0;
	while (mat[i])
	{
		if (ft_strcmp(mat[i], "<<") == 0)
		{
			result[r] = ft_strdup(mat[i + 1]);
			r++;
		}
		i++;
	}
	result[r] = NULL;
	return (result);
}

char	**assig_fd(char **mat, t_general *data_gen, t_list *list)
{
	int		i;
	char	**result;
	int		r;

	r = -1;
	i = -1;
	result = malloc((nb_redirrec(mat) + 1) * sizeof(char *));
	if (!result)
		return (ft_free_mat(mat), free_list(&list), NULL);
	while (mat[++i])
	{
		if (ft_strcmp(mat[i], ">") == 0 || ft_strcmp(mat[i], ">>") == 0
			|| ft_strcmp(mat[i], "<") == 0)
		{
			if (mat[i + 1])
			{
				result[++r] = ft_strdup(mat[i + 1]);
				if (!result[r])
					return (ft_free_mat(mat), ft_free_mat(result),
						free_list(&list), NULL);
			}
		}
		if (ft_strcmp(mat[i], "<<") == 0)
		{
			result[++r] = ft_strjoin("temp_here_",
					ft_itoa(data_gen->tem_heredoc));
			if (!result[r])
				return (ft_free_mat(mat), ft_free_mat(result), free_list(&list),
					NULL);
			data_gen->tem_heredoc++;
		}
	}
	return (result[++r] = NULL, result);
}
