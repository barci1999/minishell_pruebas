/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 09:47:20 by pablalva          #+#    #+#             */
/*   Updated: 2024/10/03 15:51:11 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	j;
	size_t	i;

	i = 0;
	j = 0;
	while (src[i] != '\0')
		i++;
	if (size > 0)
	{
		while (j < size - 1 && src[j] != '\0')
		{
			dst[j] = src[j];
			j++;
		}
		dst[j] = 0;
	}
	return (i);
}
/*int     main(void)
{
	const char src[] = "Hello, World!";
	char dst[6];
	size_t len = ft_strlcpy(dst, src, sizeof(dst));
	return (0);
}*/
