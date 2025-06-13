/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_asigg_node_var_3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 20:16:04 by ksudyn            #+#    #+#             */
/*   Updated: 2025/06/13 20:17:23 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	count_here_docs(char **mat)
{
	size_t	count;
	int		i;

	count = 0;
	i = 0;
	while (mat[i])
	{
		if (ft_strcmp(mat[i], "<<") == 0)
			count++;
		i++;
	}
	return (count);
}

static void	fill_here_docs(char **result, char **mat)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
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
}

char	**assig_delim(char **mat, t_list *list)
{
	char	**result;
	size_t	nb_here;

	(void)list;
	nb_here = count_here_docs(mat);
	result = malloc((nb_here + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	fill_here_docs(result, mat);
	return (result);
}

static char	*get_fd_redirection(char **mat, int *i, t_general *data)
{
	char	*fd;
	char	*temp;

	if (ft_strcmp(mat[*i], "<<") == 0)
	{
		temp = ft_itoa(data->tem_heredoc);
		if (!temp)
			return (NULL);
		fd = ft_strjoin("temp_here_", temp);
		free(temp);
		data->tem_heredoc++;
	}
	else if (mat[*i + 1])
		fd = ft_strdup(mat[*i + 1]);
	else
		fd = NULL;
	return (fd);
}

char	**assig_fd(char **mat, t_general *data_gen, t_list *list)
{
	int		i;
	int		r;
	char	**result;
	char	*fd;

	i = -1;
	r = -1;
	result = malloc((nb_redirrec(mat) + 1) * sizeof(char *));
	if (!result)
		return (ft_free_mat(mat), free_list(&list), NULL);
	while (mat[++i])
	{
		if (ft_strcmp(mat[i], ">") == 0 || ft_strcmp(mat[i], ">>") == 0
			|| ft_strcmp(mat[i], "<") == 0 || ft_strcmp(mat[i], "<<") == 0)
		{
			fd = get_fd_redirection(mat, &i, data_gen);
			if (!fd)
				return (ft_free_mat(mat), ft_free_mat(result), free_list(&list),
					NULL);
			result[++r] = fd;
		}
	}
	result[++r] = NULL;
	return (result);
}
