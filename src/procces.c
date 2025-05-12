/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procces.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:41:33 by pablalva          #+#    #+#             */
/*   Updated: 2025/05/12 20:59:18 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pruebas.h"

pid_t	*gen_pid_array(size_t nbr_proces)
{
	pid_t *array_pids;
	if(nbr_proces == 0)
		return(NULL);
	array_pids = malloc(nbr_proces * sizeof(pid_t));
	if (!array_pids)
		return (NULL);
	return (array_pids);
}
