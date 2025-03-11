/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-31 14:56:16 by pablalva          #+#    #+#             */
/*   Updated: 2025-01-31 14:56:16 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (matrix == NULL)
	{
		return ;
	}
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}
