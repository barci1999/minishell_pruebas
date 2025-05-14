/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procces.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:41:33 by pablalva          #+#    #+#             */
/*   Updated: 2025/05/14 18:44:21 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pruebas.h"

pid_t	*gen_pid_array(size_t nbr_proces)
{
	pid_t	*array_pids;

	if (nbr_proces == 0)
		return (NULL);
	array_pids = malloc(nbr_proces * sizeof(pid_t));
	if (!array_pids)
		return (NULL);
	return (array_pids);
}
void	free_int_matrix(int **matrix, size_t len)
{
	size_t	i;

	i = 0;
	if (!matrix)
		return ;
	while (i < len)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}
int	**gen_pipes_array(size_t n_cmd)
{
	int		**array;
	size_t	i;

	i = 0;
	array = malloc((n_cmd - 1) * sizeof(int *));
	if (!array)
	{
		return (NULL);
	}
	while (i < (n_cmd - 1))
	{
		array[i] = malloc(2 * sizeof(int));
		if (!array[i])
		{
			free_int_matrix(array, (n_cmd - 1));
			return (NULL);
		}
		if (pipe(array[i]) == -1)
		{
			free_int_matrix(array, (n_cmd - 1));
			return (NULL);
		}
		i++;
	}
	return (array);
}
