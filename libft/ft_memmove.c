/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:01:51 by pablalva          #+#    #+#             */
/*   Updated: 2024/10/02 11:35:27 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if ((dest == NULL) && (src == NULL))
		return (NULL);
	if (d < s || d >= s + n)
	{
		while (n--)
			*d++ = *s++;
	}
	else
	{
		d = d + n;
		s = s + n;
		while (n--)
		{
			*(--d) = *(--s);
		}
	}
	return (dest);
}
/*int	main(void)
{
	char	src[]= "helloworld";
	char	dest[50]= "helloworld";
	int	n = 5;
		printf("%s\n",(char *)ft_memmove(dest,src+3,n));
		printf("%s\n",(char *)memmove(dest,src+3,n));
}*/
