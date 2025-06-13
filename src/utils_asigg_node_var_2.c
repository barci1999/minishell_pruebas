/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_asigg_node_var_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:11:10 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/13 20:17:13 by ksudyn           ###   ########.fr       */
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
