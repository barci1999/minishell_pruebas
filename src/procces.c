/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procces.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:41:33 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/05 15:00:48 by pablalva         ###   ########.fr       */
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

int	**gen_pipes_array(size_t n_cmd)
{
	int		**array;
	size_t	i;

	if (n_cmd < 2)
		return (NULL);
	array = malloc((n_cmd - 1) * sizeof(int *));
	if (!array)
		return (NULL);
	i = 0;
	while (i++ < (n_cmd - 1))
	{
		array[i] = malloc(2 * sizeof(int));
		if (!array[i])
		{
			ft_free_mat_int(array, i);
			return (NULL);
		}
		if (pipe(array[i]) == -1)
		{
			free(array[i]);
			ft_free_mat_int(array, i);
			return (NULL);
		}
	}
	return (array);
}

void	close_all_pipes(int total_cmds, t_general *general)
{
	int	k;

	k = 0;
	while (k < total_cmds - 1)
	{
		close(general->pipes[k][0]);
		close(general->pipes[k][1]);
		k++;
	}
}

void	wait_all_procces(t_general *general, int i)
{
	int	j;
	int	status;

	j = 0;
	while (j < i)
	{
		waitpid(general->pids[j], &status, 0);
		if (j == i - 1)
			general->last_exit_code = WEXITSTATUS(status);
		j++;
	}
}
