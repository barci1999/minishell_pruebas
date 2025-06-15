/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_mat_int.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:08:10 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/15 22:13:31 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_mat_void(void **matrix, size_t len)
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
