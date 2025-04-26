/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_mat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:52:19 by pablalva          #+#    #+#             */
/*   Updated: 2025/04/11 12:22:39 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_dup_mat(char **src)
{
	int		i;
	char	**res;

	i = 0;
	res = malloc((ft_matlen(src) + 1) * sizeof(char *));
	while (src[i])
	{
		res[i] = ft_strdup(src[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}
