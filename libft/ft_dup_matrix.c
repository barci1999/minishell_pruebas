/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:52:19 by pablalva          #+#    #+#             */
/*   Updated: 2025/04/11 12:22:39 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_dup_matrix(char **src)
{
	int		i;
	char	**result;

	i = 0;
	result = malloc((ft_matrixlen(src) + 1) * sizeof(char *));
	while (src[i])
	{
		result[i] = ft_strdup(src[i]);
		i++;
	}
	result[i] = NULL;
	return (result);
}
