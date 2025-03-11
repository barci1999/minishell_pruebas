/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:48:27 by pablalva          #+#    #+#             */
/*   Updated: 2024/10/02 19:15:54 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	src_len = ft_strlen(src);
	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (dst[i])
		i++;
	while (i + 1 < dstsize && *src)
	{
		dst[i] = *src;
		i++;
		src++;
	}
	dst[i] = '\0';
	if (src_len + i >= dstsize && i < dstsize)
		return (i + ft_strlen(src));
	else if (i >= dstsize)
		return (dstsize + ft_strlen(src));
	else
		return (ft_strlen(dst));
}
/*int     main(void)
{
		size_t size = 11;
		char dst[9]= "cocacola";
		const char src[8]= "periplo";
		printf("%zu\n",ft_strlcat(dst,src,size));
	printf("%s", dst);
}*/
